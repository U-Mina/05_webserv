/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:35:42 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/05/24 17:13:05 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP

# define LOGGER_HPP

# include "webserv.hpp"

enum LogLevel
{
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	FATAL
};

class Logger
{
private:
	static LogLevel			_level;
	static std::ofstream	_log_file;
	static std::string		_file_path;
	static bool				_console_output;
	static bool				_append;

	static std::string		_getTimestamp();
	static std::string		_levelToString(LogLevel level);
	static void				_log(LogLevel level, const std::string& msg);

public:
	~Logger();

	static Logger&			getInstance();
	static void				init(LogLevel level, const std::string& log_file_path, bool console_output, bool append);
	static void				debug(const std::string& msg);
	static void				info(const std::string& msg);
	static void				warning(const std::string& msg);
	static void				error(const std::string& msg);
	static void				fatal(const std::string& msg);
	static void				cleanup();
};

#define LOG_INIT(level, log_file_path, console_output, append) Logger::getInstance().init(level, log_file_path, console_output, append)
#define LOG_DEBUG(msg) Logger::getInstance().debug(msg)
#define LOG_INFO(msg) Logger::getInstance().info(msg)
#define LOG_WARN(msg) Logger::getInstance().warning(msg)
#define LOG_ERR(msg) Logger::getInstance().error(msg)
#define LOG_FATAL(msg) Logger::getInstance().fatal(msg)
#define LOG_CLEANUP() Logger::getInstance().cleanup()

#endif