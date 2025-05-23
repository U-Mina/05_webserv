/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:30:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/05/24 11:07:14 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
# define HEADER_HPP

# include "webserv.hpp"
# include <map>

struct CaseInsensitiveCompare {
	bool 																operator()(const std::string& a, const std::string& b) const;
};

class Header
{
private:
	std::map<std::string, std::string, CaseInsensitiveCompare>			_fields;

public:
	Header();
	Header(const Header& other);
	Header	&operator=(const Header &other);
	~Header();

	void set(const std::string &name, const std::string &value);
	std::string getVal(const std::string &name) const;
	const std::map<std::string, std::string, CaseInsensitiveCompare>& getAll() const;

	bool check_exist(const std::string& name) const;
	void remove(const std::string& name);

	// Parse headers from a string (for request parsing)
	// bool parse(const std::string& headerStr);
	std::string toString() const;
};

#endif

//implement correctly in cpp file instead!?!
// struct CaseInsensitiveCompare {
// 	bool operator()(const std::string& a, const std::string& b) const;
// };
// Parse headers from a string (for request parsing)
// bool parse(const std::string& headerStr);