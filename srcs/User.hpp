#ifndef USER_HPP
#define USER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "Server.hpp"

#include <sys/socket.h>

class Server;

class User
{
	protected:
		Server *	_serv;
  private:
	int		_fd;
	std::string	_username;
	std::string	_nickname;
	std::string	_password;	
	std::string	_host;
	bool		_isAuth;
  public:
	User(int &fd, Server *serv, int fdFix);
	~User();
	std::string	_msgBuffer;
	void		setUsername(std::string username);
	void		setNickname(std::string nickname);
	void		setPassword(std::string password);
	void		setHost(std::string host);
	void		setAuth();
	int		getFd();
	std::string	getUsername();
	std::string	getNickname();
	std::string	getPassword();
	std::string	getHost();
	bool		getIsAuth();
	void		sendMsg(std::string msg);
	int		_fdFix;
};

#endif
