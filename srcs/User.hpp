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
		bool		_isAuth;
		int			_fd;
		std::string	_host;
		std::string	_nickname;
		std::string	_password;	
		std::string	_username;
	public:
		User(int &fd, Server *serv);
		~User();
		bool		getIsAuth();
		int			getFd();
		std::string	_msgBuffer;
		std::string	getHost();
		std::string	getNickname();
		std::string	getPassword();
		std::string	getUsername();
		void		sendMsg(std::string msg);
		void		setAuth();
		void		setHost(std::string host);
		void		setNickname(std::string nickname);
		void		setPassword(std::string password);
		void		setUsername(std::string username);
};

#endif
