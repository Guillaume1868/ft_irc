#include "User.hpp"


User::User(int &fd, Server *serv) : _serv(serv), _fd(fd)
{
	std::cout << "New User on FD " << _fd << std::endl;
	_isAuth = 0;
}

User::~User(void)
{
	//close(_fd);
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
		this->sendMsg(":Welcome to the Internet Relay Network " + this->getNickname() + "!" + this->getUsername() + "@" + this->getHost() + "\n\r");
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