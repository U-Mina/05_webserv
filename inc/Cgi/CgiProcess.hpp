/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiProcess.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:11:21 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/05/25 10:55:31 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPROCESS_HPP
# define CGIPROCESS_HPP

#include "webserv.hpp"
#include "Client.hpp"

class Client;

enum cgiState
{
	UNINITIALIZED,
	READING_CGI,
	READ_CGI,
	WRITING_CGI //POST
};

class CgiProcess
{
private:
	Client				*_client;
	int					_pipFromCgi;
	int					_pipToCgi;
	int					_cgiPid;
	std::vector<char>	_cgiBuffer;
	bool				_cgiActive;
	cgiState			_state;
	bool				_headers_sent;
	std::string			_script_path;
	char				**_envp;

	void				_createEnv(HttpRequest& httpReq);
	void				_convertToEnvp(std::vector<std::string>& envStr);
	void				_cleanEnvp(void);
	void				_cleanupCgiPipe(int *pipFromCgi, int *pipToCgi);
	void				_appendCgiOutputBuff(std::vector<char> &buffer, size_t bytes);
	void				_cgiHeadersToResponse();
	void				_addHeaderToResponse(const std::string& line, HttpResponse& response);
	void				_checkChunkedTransfer(HttpResponse &response);
	bool				_checkHeaderCompletion();
	std::string			_getExtSysPath(Client* client);
	std::string			_getScriptDir(std::string path);
	
	public:
	CgiProcess(Client *client);
	~CgiProcess();

	//setters
	void				setActive(bool active);
	void				setState(cgiState state);

	//getters
	Client				*getClient();
	int					getFromCgi();
	int					getToCgi();
	int					getCgiPid();
	bool				isActive();
	cgiState			getState();
	std::string			getStateString(cgiState state);
	bool				getHeadersSent();
	std::string			getScriptPath();


	//methods
	bool				initCgi();
	void				readCgiOutput();
	bool				writeToCgi();
	void				cleanCloseCgi();
};

#endif