/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiChecker.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:35:28 by ewu               #+#    #+#             */
/*   Updated: 2025/05/22 12:59:14 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiChecker.hpp"
#include "LocationConf.hpp"
#include "Client.hpp"

bool CgiChecker::checkCGI(const LocationConf& loc)
{
	if (!_hasCgiPara(loc)) {
		throw std::runtime_error("Error: missing CGI parameter.");
		return false;
	}
	// if (!_validCgiIndex(loc)) {
	// 	throw std::runtime_error("Error: invalid cgi index page.");
	// 	return false;
	// }
	if (!_validCgiPath(loc.getCgiSysPath())) {
		throw std::runtime_error("Error: invalid cgi path."); //usr/bin/php
		return false;
	}
	if (!_validExtension(loc.getCgiExtension())) {
		throw std::runtime_error("Error: invalid cgi surffix.");
		return false;
	}
	if (!_matchSize(loc)) {
		throw std::runtime_error("Error: unmacth size of cig path with extension.");
		return false;
	}
	return true;
}

bool CgiChecker::_hasCgiPara(const LocationConf& loc)
{
	if (loc.getCgiExtension().empty() || loc.getCgiSysPath().empty()) {
		return false;
	}
	return true;
}

bool CgiChecker::_validCgiPath(const std::vector<std::string>& _cgipath)
{
	for (size_t i = 0; i < _cgipath.size(); ++i)
	{
		if (FileUtils::pathType(_cgipath[i]) == -1) {
			return false;
		}
	}
	return true;
}
bool CgiChecker::_validExtension(const std::vector<std::string>& _cgiextend)
{
	for (size_t i = 0; i < _cgiextend.size(); ++i) {
		if (_cgiextend[i] == ".php" || _cgiextend[i] == ".py" || _cgiextend[i] == ".sh") {
			return true;
		}
	}
	return false;
}

bool CgiChecker::_matchSize(const LocationConf& loc)
{
	if (loc.getCgiSysPath().size() == loc.getPathExMap().size()) {
		return true;
	}
	return false;
}

bool CgiChecker::validCgiScript(Client* client)
{
	std::string cgiScriptPath = client->getRequest().getPath();
	if (FileUtils::pathType(cgiScriptPath) == -1) {
		client->sendErrorResponse(404, "CGI path not found");
		LOG_ERR("\033[31mError in cgi script path type. Path is: " + cgiScriptPath + "\033[0m");
		return false;
	}
	if (FileUtils::isExec(cgiScriptPath) == -1) {
		client->sendErrorResponse(403, "CGI path is not executable");
		LOG_ERR("\033[31mErrror in cgi script path not excutable. Path is: " + cgiScriptPath + "\033[0m");
		return false;
	}
	return true;
}

// bool CgiChecker::_validCgiIndex(const LocationConf& loc)
// {
// 	std::vector<std::string> loc_index = loc.getLocIndex();
// 	for (size_t i = 0; i < loc_index.size(); ++i) {
// 		if (!loc_index[i].empty()) {
// 			std::string full_path = loc.getLocRoot() + loc.getLocPath() + "/" + loc_index[i];
// 			if (FileUtils::pathValid(loc_index[i], R_OK) == 0 &&
// 				FileUtils::pathType(loc_index[i]) == 2) {
// 					return true;
// 			} //if index is full path and works case
// 			if (FileUtils::pathValid(full_path, R_OK) == 0 &&
// 			FileUtils::pathType(full_path) == 2) {
// 				return true;
// 			} //if root+path+index is full path and works case
// 			char* tmpCwd = getcwd(NULL, 0);
// 			if (!tmpCwd) {
// 				return false;
// 			} //if non above work, use getcwd() to get CWD, and cate with path+index
// 			std::string cwd_path = std::string(tmpCwd) + loc.getLocPath() + "/" + loc_index[i];
// 			free(tmpCwd);
// 			return (FileUtils::pathValid(cwd_path, R_OK) == 0 &&
// 			FileUtils::pathType(cwd_path) == 2);
// 		}
// 		return true;
// 	}
// }
// bool CgiChecker::_mapPathExtension(const LocationConf& loc)
// {
// 	const std::vector<std::string>& _cgipath = loc.getCgiSysPath();
// 	const std::vector<std::string>& _cgiextend = loc.getCgiExtension();
// 	std::map<std::string, std::string> _path_extend;
// 	for (size_t i = 0; i < _cgiextend.size(); ++i) {
// 		const std::string& ext = _cgiextend[i];
// 		for (size_t j = 0; j < _cgipath.size(); ++j)
// 		{
// 			if ((ext == ".php" || ext == "*.php") && (_cgipath[j].find("php") != std::string::npos)) {
// 				_path_extend[".php"] = _cgipath[j];
// 			}
// 			else if ((ext == ".py" || ext == "*.py") && (_cgipath[j].find("py") != std::string::npos)) {
// 				_path_extend[".py"] = _cgipath[j];
// 			}
// 		}
// 	}
// 	loc.setPathExMap(_path_extend);//check this setter
// 	return !_path_extend.empty();
// }

//singularly check .php only
// bool CgiChecker::_mapPathExtension(LocationConf& loc)
// {
// 	const std::vector<std::string>& _cgipath = loc.getCgiSysPath();
// 	const std::vector<std::string>& _cgiextend = loc.getCgiExtension();
// 	std::map<std::string, std::string> _path_extend;
// 	for (size_t i = 0; i < _cgiextend.size(); ++i) {
// 		if (_cgiextend[i] == ".php" || _cgiextend[i] == "*.php") {
// 			for (size_t j = 0; j < _cgipath.size(); ++j) {
// 				if (_cgipath[j].find("php") != std::string::npos) {
// 					_path_extend[".php"] = _cgipath[j];
// 					break ;
// 				}
// 			}
// 		}
// 	}
// 	loc.setPathExMap(_path_extend);
// 	return !_path_extend.empty();
// }

//When is it used?!?!?!? Move to CgiChecker?!? Remove?!!?
