/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverConf.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:53:13 by ewu               #+#    #+#             */
/*   Updated: 2025/04/10 17:08:04 by ewu              ###   ########.fr       */
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
public:
	int port;
	std::string server_name;
	std::string root_dir;
	std::map<int, std::string> err_page; //err_code, url
	size_t max_body_size; //max body size (required by subject)
	std::vector<locationConf> locs; //a set of location_blocks in server_configuration
	// other var to add later
public:
	//init instance
	ServerConf();
	//pass para from usr.conf
	ServerConf(int _port, const std::string& _servname, const std::string& _root);
	~ServerConf();
	// ServerConf(const ServerConf& other);
	// ServerConf& operator=(const ServerConf& other);

	//getters and setters
};

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