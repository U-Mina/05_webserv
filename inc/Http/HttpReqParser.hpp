/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpReqParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:32:41 by ewu               #+#    #+#             */
/*   Updated: 2025/05/21 13:37:42 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQPARSE_HPP
#define HTTPREQPARSE_HPP

#include "webserv.hpp"
#include "HttpRequest.hpp"

class Client;

enum reqStage {
	REQ_LINE,
	HEADERS,
	BODY,
	FINISH,
	PARSE_ERROR
};

class HttpReqParser {
private:
	reqStage							_stage;
	ssize_t								_bodyLength;
	std::vector<char>					_buffer;
	bool								_header_complete;
	bool								_chunked;
	bool								_chunk_complete;
	size_t								_chunk_size;
	HttpRequest							&_httpReq;

	bool								_isPathSafe(std::string normalizedUri, const std::string &docRoot);
	bool								_singleHeaderLine(HttpRequest& request, const std::string& curLine);
	bool								_parseChunkSize(Client &client);
	void								_parseReqLine(HttpRequest& request);
	void								_parseHeader(HttpRequest& request, Client &client);
	void								_parseBody(HttpRequest& request, Client &client);
	void								_parseChunk(HttpRequest &request);
	void								_checkHeaderCompletion();
	void								_checkChunkCompletion();
	void								_setRequestConf(HttpRequest &request, Client &client);
	void								_prepareBodyParsing(HttpRequest &request, Client &client);
	size_t								_countCgiEnd(const std::string& uri);
	std::string							_takeLine();
	std::string							_mapSysPathFromUri(Client &client);
	std::string							_normalizeUriPath(std::string rawUri);
	std::string							_mapUploadPath(Client &client);
	std::vector<char>::const_iterator	_findEndOfLine();

public:
	HttpReqParser(HttpRequest &request);
	~HttpReqParser();
	
	void								reset();
	bool								checkFinish();
	bool								httpParse(Client &client);
	void								appendBuffer(const std::vector<char> &new_data);
	HttpRequest							getHttpRequest() const;
};

#endif
// methodType& getMethd();
// std::string& getVersion();
// std::string& getPath(); //url
//setter
// bool _setFinish(bool _flag);
// void setMethd(std::string& s); //set as methodType type
// void setUrl(std::string& s);
// void setVersion(std::string& s); //return version like '/1.1', check validity