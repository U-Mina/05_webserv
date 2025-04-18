/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:26 by ewu               #+#    #+#             */
/*   Updated: 2025/04/18 12:34:07 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

// Client::Client()
// {
// 	//create a new socket?!?!
// }

Client::Client(int socket)
	:_socket(socket), _state(NEW_REQUEST), _file_fd(-1), _bytes_sent(0), _empty_buffer(true)
{
	//_request
	//_response
}

HttpRequest		&Client::getRequest(void)
{
	return (_request);
}

clientState	Client::getState(void)
{
	return (_state);
}

bool	Client::getEmptyBuffer(void)
{
	return (_empty_buffer);
}

void	Client::setEmptyBuffer(bool value)
{
	_empty_buffer = value;
}

void	Client::setState(clientState state)
{
	_state = state;
}

void	Client::setResponse(HttpResponse response)
{
	_response = response;
}

void	Client::setFileFd(int file_fd)
{
	_file_fd = file_fd;
}

void	Client::setBuffer(char *buffer, size_t bytesRead)
{
	_response_buffer.assign(buffer, bytesRead);
}

bool	Client::sendResponseChunk(void)
{
	if (_bytes_sent == 0)
	{
		std::string	status = _response.statusToString();
		std::string	headers = _response.headersToString();

		size_t sent = send(_socket, status.c_str(), status.length(), 0);
		if (sent < 0)
			return false;
		_bytes_sent = sent;
		sent = send(_socket, headers.c_str(), headers.length(), 0);
		if (sent < 0)
			return false;
		_bytes_sent += sent;
		return true; //return true to indicate correctly sent or that everything has been sent!??
	}
	if (_response.getBodyPresence() == true)
	{
		if (!_empty_buffer)
		{
			size_t sent = send(_socket, _response_buffer.c_str(), _response_buffer.length(), 0);
			if (sent < 0)
				return false;
			_empty_buffer = true;
			_bytes_sent += sent;
			return true;
		}
		if (_empty_buffer && _file_fd == -1 && _response.getState() != READ) //or handle the case where there was a fd and is already sent!
		{
			std::string	body = _response.bodyToString();
			size_t	sent = send(_socket, body.c_str(), body.length(), 0);
			if (sent < 0)
				return false;
			_bytes_sent += sent;
			return true;
		}
	}
	return false; //!?!?!?
	//else set it as already sent
}
