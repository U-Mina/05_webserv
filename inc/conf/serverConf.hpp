/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConf.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:53:13 by ewu               #+#    #+#             */
/*   Updated: 2025/04/19 16:13:25 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCONF_HPP
#define SERVERCONF_HPP

#define MAX_BODY 2*1024*1024 //2 megebyte, random set now
#include "webserv.hpp"
#include "LocationConf.hpp"
// class LocationConf;

//setter for varible, set val to an instance of server
class ServerConf
{
private:
	unsigned int _port;
	unsigned int _max_body_size;
	std::string _server_name;
	std::string _root_dir;
	std::string _host;
	std::string _index;
	std::map<int, std::string> _error_page; //err_code, url
	bool _srv_autoindex; //default as false in construtor
	std::map<std::string, LocationConf> _locations;
	// std::vector<LocationConf> _location; //a set of location_blocks in server_configuration
	
	// std::vector<std::string> _error_page;
	// [...] other var to add later
	
public:
	ServerConf(); //init instance
	ServerConf(int _port, const std::string& _servname, const std::string& _root);
	~ServerConf();
	// ServerConf(const ServerConf& other);
	// ServerConf& operator=(const ServerConf& other);
	
	//checker
	bool _allDigit(const std::string& s);
	static bool _hasSemicolon(const std::string& s);
	static std::string rmvSemicolon(const std::string& token);
	bool _codeRange(const std::string& errtoken);

	//setters, pass 'const std::string& s' or pass COPY???
	void setPort(std::string s);
	void setHost(std::string s);
	void setSrvName(std::string s);

	void setRoot(std::string s);
	void setCMBS(std::string s);
	void setIndex(std::string s);
	void setAutoIndex(bool _flag);
	void setErr(std::vector<std::string>& errTokens); //return std::map<> pair??
	void _addLocation(std::string& _path, std::vector<std::string>& loc_tokens); //todo: setter for var in this class
	
	//getters
	const int& getPort() const;
	int getCMBS() const;
	const bool getAutoIndex() const;
	const std::string& getRoot() const;
	const std::string& getHost() const; //at socket binding part, use getaddrindo() to resolve!
	const std::string& getIndex() const;
	const std::string& getSrvName() const;
	const std::map<int, std::string>& getErrPage() const;
	const std::map<std::string, LocationConf>& getLocation() const;
	// std::vector<std::string>& getErrPage() const;
	// std::vector<LocationConf>& getLocation() const;
	//[...]
	
	//map<string, function<void()>> parser list for location block
	void parseLocRoot(LocationConf& loc, const std::vector<std::string>& loc_tks, size_t& i);
	void parseMethod(LocationConf& loc, const std::vector<std::string>& loc_tks, size_t& i);
	void parseLocAuto(LocationConf& loc, const std::vector<std::string>& loc_tks, size_t& i);
	void parseLocIndex(LocationConf& loc, const std::vector<std::string>& loc_tks, size_t& i);
	void parseAlias(LocationConf& loc, const std::vector<std::string>& loc_tks, size_t& i);
	void parseLocCMBS(LocationConf& loc, const std::vector<std::string>& loc_tks, size_t& i);
	void parseCgiPath(LocationConf& loc, const std::vector<std::string>& loc_tks, size_t& i);
	void parseCgiExtension(LocationConf& loc, const std::vector<std::string>& loc_tks, size_t& i);
	void parseReturn(LocationConf& loc, const std::vector<std::string>& loc_tks, size_t& i);
	
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