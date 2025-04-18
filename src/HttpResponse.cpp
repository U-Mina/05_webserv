/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:30:26 by ewu               #+#    #+#             */
/*   Updated: 2025/04/18 13:04:51 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpResponse.hpp"

HttpResponse::HttpResponse()
	:_body_presence(true), _body(nullptr), _state(READING)
{
}

HttpResponse::HttpResponse(Status &status, Header &header)
	:_body_presence(true), _body(nullptr), _state(READING)
{
	_status = Status(status);
	_header = Header(header);
}

HttpResponse::HttpResponse(Status &status, Header &header, std::string body)
	:_body_presence(true), _body(body), _state(READING)
{
	_status = Status(status);
	_header = Header(header);
}

HttpResponse::HttpResponse(const HttpResponse &other)s
{
	*this = other;
}

HttpResponse	&HttpResponse::operator=(const HttpResponse &other)
{
	if (this != &other)
	{
		delete _header;
		delete _status;
		new Header(other._header);
		new Status(other._status);
		_body = other._body;
	}
	return *this;
}

HttpResponse::~HttpResponse()
{
	delete _status;
	delete _header;
}

//correctly implemented!?!?
void	HttpResponse::setStatus(Status &status)
{
	delete _status;
	_status = new Status(status);
}

void	HttpResponse::setStatusCode(int code)
{
	delete _status;
	_status = new Status(code);
	if (code == 204 || code == 304)
		_body_presence = false;
}

//correctly implemented!?!?
void	HttpResponse::setHeader(Header &header)
{
	delete _header;
	_header = new Header(header);
}

void	HttpResponse::addHeaderField(const std::string& name, const std::string& value)
{
	_headers.set(name, value);
}

void	HttpResponse::setBody(std::string &body)
{
	_body = body;
	_header.set("Content-Length", _body.size());
}

std::string HttpResponse::getHeader(const std::string& name)
{
	return _headers.get(name);
}

responseState HttpResponse::getState(void) const
{
	return _state;
}

std::string	HttpResponse::toString() const
{
	std::stringstream	response;

	response << _status.toString() << _header.toString() << "\r\n";
	if (!_body.empty())
		response << _body;
	return response.str();
}

std::string	HttpResponse::bodyToString() const
{
	if (!_body.empty())
		return _body.str();
}

std::string	HttpResponse::statusToString() const
{
	return _status.toString();
}

std::string	HttpResponse::headersToString() const
{
	std::stringstream	header;

	header << _header.toString() << "\r\n";
	return header.str();
}

bool	HttpResponse::getBodyPresence(void) const
{
	return _body_presence;
}

//https://www.rfc-editor.org/rfc/rfc9110#media.type
//give somehow the path and not the body!?!?
//use switch or something more elegant!?!?
//where to include this function!!????
std::string		getMediaType(const std::string& path)
{
	std::string extension = path.substr(path.find_last_of('.') + 1);
	
	if (extension == "html" || extension == "htm")
		return "text/html";
	else if (extension == "css")
		return "text/css";
	else if (extension == "js")
		return "application/javascript";
	else if (extension == "png")
		return "image/png";
	else if (extension == "jpg" || extension == "jpeg")
		return "image/jpeg";
	else if (extension == "gif")
		return "image/gif";
	else if (extension == "pdf")
		return "application/pdf";
	else if (extension == "txt")
		return "text/plain";
	// Add more types if needed

	return "application/octet-stream"; // Default binary type
}
