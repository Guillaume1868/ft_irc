#include "User.hpp"

#include <sstream>

extern Display display;

User::User(int &fd, Server *serv, int fdFix) : _serv(serv), _fd(fd), _fdFix(fdFix)
{
	std::string result;		//
	std::ostringstream convert;	// used to convert int to std::string
	convert << _fd;			// because std::to_string is cpp11
	result = convert.str();		//
	
	display.addMessage("New User on FD " + result);
	_isAuth = 0;
}

User::~User(void)
{
	close(_fd);
	_fd = -1;
}

void	User::setUsername(std::string username)
{
	this->_username = username;
	setAuth();
}

void	User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
	setAuth();
}

void	User::setPassword(std::string password)
{
	this->_password = password;
	setAuth();
}

void	User::setHost(std::string host)
{
	this->_host = host;
	setAuth();
}

void	User::setAuth()
{
	if (_username.length() > 0 && _nickname.length() > 0 && _password == _serv->getPassword() && _host.length() > 0)
	{
		_isAuth = 1;
		this->sendMsg(":0 001 " + this->getNickname() + " :Welcome to the Internet Relay Network, " + this->getNickname() + "\r\n");
	}
}

int	User::getFd()
{
	return (_fd);
}

std::string	User::getUsername()
{
	return (_username);
}

std::string	User::getNickname()
{
	return (_nickname);
}

std::string	User::getPassword()
{
	return (_password);
}

std::string	User::getHost()
{
	return (_host);
}

bool	User::getIsAuth()
{
	return (_isAuth);
}

void	User::sendMsg(std::string msg)
{
	_serv->sendMsg(this, msg);
}
