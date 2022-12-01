#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <string>

#include <sys/socket.h>

class User
{
  private:
	int		_fd;
	std::string	_username;
	std::string	_nickname;
	std::string	_password;	
	bool		_isAuth;
  public:
	User(int &fd);
	~User();
	std::string	_msgBuffer;
	void		setUsername(std::string username);
	void		setNickname(std::string nickname);
	void		setPassword(std::string password);
	void		setAuth();
	int		getFd();
	std::string	getUsername();
	std::string	getNickname();
	std::string	getPassword();
	bool		getIsAuth();
};

#endif
