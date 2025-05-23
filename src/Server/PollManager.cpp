/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:51:27 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/05/24 09:18:57 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MultiServer.hpp"


/*-------------METHODS--------------------------------------------------------*/

void	MultiServer::_newFdsToPoll(Client *client)
{
	//push GET file fds to poll
	int	file_fd = client->getFileFd();
	if (file_fd != -1) {
		LOG_INFO("Input file " + std::to_string(file_fd) + " has been linked with client at socket " + std::to_string(client->getSocket()));
		_poll.push_back((struct pollfd) {file_fd, POLLIN, 0});
	}

	//push POST file fds to poll
	for (auto it = client->getPostFdMap().begin(); it != client->getPostFdMap().end(); ++it) {
		file_fd = it->first;
		LOG_INFO("Output file " + std::to_string(file_fd) + " has been linked with client at socket " + std::to_string(client->getSocket()));
		_poll.push_back((struct pollfd) {file_fd, POLLOUT, 0});
	}

	//push cgi_fds to _poll
	if (client->getCgiProcess()){
		if (client->getCgiProcess()->getToCgi()!= -1) {
			int to_cgi = client->getCgiProcess()->getToCgi();
			LOG_INFO("Writing pipe end with fd " + std::to_string(to_cgi) + " has been linked with client at socket " + std::to_string(client->getSocket()));
			_poll.push_back((struct pollfd) { to_cgi, POLLOUT, 0 });
		}
		if (client->getCgiProcess()->getFromCgi()!= -1) {
			int from_cgi = client->getCgiProcess()->getFromCgi();
			LOG_INFO("Reading pipe end with fd " + std::to_string(from_cgi) + " has been linked with client at socket " + std::to_string(client->getSocket()));
			_poll.push_back((struct pollfd) { from_cgi, POLLIN, 0 });
		}
	}
}

void	MultiServer::_eraseFromPoll(int fd)
{
	for (int i = _poll.size() - 1; i > 0; i--) {
		if (_poll.data()[i].fd == fd) {
			_poll.erase(_poll.begin() + i);
			return ;
		}
	}
}

void	MultiServer::_handlePollErr(int fd, int i)
{
	std::map<int, Client*>::iterator it_c;

	if (_poll[i].revents & POLLHUP) {
		for (it_c = _clients.begin(); it_c != _clients.end(); ++it_c) {
			if (it_c->second->getCgiProcess() && it_c->second->getCgiProcess()->getFromCgi() == fd) {
				LOG_DEBUG("CGI pipe end at " + std::to_string(fd) + " closed (POLLHUP)");
				if (it_c->second->getCgiProcess()->getState() == READING_CGI)
					it_c->second->getCgiProcess()->readCgiOutput();
				if (it_c->second->getCgiProcess()->isActive() == false)
					_eraseFromPoll(fd);
				return ;
			}
		}
		LOG_INFO("Client at socket " + std::to_string(fd) + " disconnected");
	} else
		LOG_ERR("Error on socket " + std::to_string(fd));
	if (std::map<int, ListenSocket*>::iterator it_s = _sockets.find(fd); it_s != _sockets.end()) {
		_closeListeningSocket(it_s->second);
		return ;
	} else if (it_c = _clients.find(fd); it_c != _clients.end()){
		it_c->second->setState(CONNECTION_CLOSED);
		return ;
	} else if (fd != -1) {
		close(fd);
	}
	_eraseFromPoll(fd);
}