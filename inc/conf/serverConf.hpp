/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConf.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:53:13 by ewu               #+#    #+#             */
/*   Updated: 2025/04/16 16:02:05 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCONF_HPP
#define SERVERCONF_HPP

#define MAX_BODY 1048576
#include "webserv.hpp"
class locationConf;

//setter for varible, set val to an instance of server
class ServerConf
{
private:
	int _port;
	std::string _server_name;
	std::string _root_dir;
	std::string _host;
	std::map<int, std::string> _error_page; //err_code, url
	size_t _max_body_size; //max body size (required by subject)
	std::vector<locationConf> _locs; //a set of location_blocks in server_configuration
	// [...] other var to add later
	
public:
	ServerConf(); //init instance
	ServerConf(int _port, const std::string& _servname, const std::string& _root);
	~ServerConf();
	// ServerConf(const ServerConf& other);
	// ServerConf& operator=(const ServerConf& other);
	
	//setters, pass 'const std::string& s' or pass COPY???
	void setPort(std::string s);
	void setHost(std::string s);
	void setSrvName(std::string s);
	void setHost(std::string s);
	void setRoot(std::string s);
	void setIndex(std::string s);
	void setErr(std::string s); //return std::map<> pair??
	void parseLocation(locationConf _location); //todo: setter for var in this class
	
	//getters
	int& getPort() const;
	std::string& getHost() const; //at socket binding part, use getaddrindo() to resolve!
	std::string& getSrvName() const;
	std::string& getRoot() const;
	int& getIndex() const;
	std::vector<locationConf>& getLocation() const;
	std::map<int, std::string>& getErrPage() const;
	//[...]
	
};

/**
 * Response Codes:
	2xx: Success (200 OK, 201 Created)
	4xx: Client errors (400 Bad Request, 401 Unauthorized, 403 Forbidden)
	5xx: Server errors (500 Internal Server Error)
 */
/** clear explanation of static and CGI
 * STATIC: no database interact, no backend processing, al-read-made
 * 		- like the cake in the fridge
 * 		- blogs (without comment ft), portofolis web; 'About Us' page
 * CGI: web generate on the fly (on demand) using script
 * 		- can read, process data
 * 		- return customize HTML
 * 		- login sys, search feature in WEB, contact form in WEB
 */
#endif