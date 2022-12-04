#include "Channel.hpp"
#include "User.hpp"

extern Display display;

Channel::Channel(std::string name) : _chanName(name), _maxUsers(100)
{

}

Channel::Channel(std::string name, std::string password) : _chanName(name), _pass(password), _maxUsers(100)
{

}

Channel::~Channel(void)
{
}

void	Channel::joinChannel(User *user)
{
	_connectedUsers.push_back(user);
}

void	Channel::delUser(std::string name)
{
	for (std::vector<User *>::iterator i = _connectedUsers.begin(); i != _connectedUsers.end(); ++i)
	{
		if ((*i)->getNickname() == name)
		{
			_connectedUsers.erase(i);
			break;
		}
	}
}

User	*Channel::getUserByNick(std::string nick)
{
	for (std::vector<User *>::iterator i = _connectedUsers.begin(); i != _connectedUsers.end(); i++)
	{
		if ((*i)->getNickname() == nick)
			return (*i);
	}
	return NULL;
}

User	*Channel::getUserByUsername(std::string username)
{
	for (std::vector<User *>::iterator i = _connectedUsers.begin(); i != _connectedUsers.end(); i++)
	{
		if ((*i)->getUsername() == username)
			return (*i);
	}
	return NULL;
}

bool	Channel::passIsValid(std::string password)
{
	if (_pass.compare(password) == 0)
		return (0);
	return (1);
}

std::string	Channel::getChanName()
{
	return(_chanName);
}

void		Channel::setPassword(std::string password)
{
	_pass = password;
}

std::string	Channel::getPassword()
{
	return (_pass);
}

void		Channel::setMaxUsers(int x)
{
	_maxUsers = x;
}

int		Channel::getMaxUsers()
{
	return(_maxUsers);
}

void            Channel::addBannedUser(std::string name)
{
	_bannedUsers.push_back(name);
}

void            Channel::delBannedUser(std::string name)
{
	for (std::vector<std::string>::iterator i = _bannedUsers.begin(); i != _bannedUsers.end(); i++)
	{
		if((*i) == name)
			_bannedUsers.erase(i);
	}
}

bool            Channel::isBanned(std::string name)
{
	for(std::vector<std::string>::iterator i = _bannedUsers.begin(); i != _bannedUsers.end(); i++)
	{
		if ((*i) == name)
			return(0);
	}
	return(1);
}

void            Channel::addOpUser(std::string name)
{
	_opUsers.push_back(name);
}

void            Channel::delOpUser(std::string name)
{
	for (std::vector<std::string>::iterator i = _opUsers.begin(); i != _opUsers.end(); i++)
	{
		if ((*i) == name)
			_opUsers.erase(i);
	}
}

bool            Channel::isOp(std::string name)
{
	for(std::vector<std::string>::iterator i = _opUsers.begin(); i != _opUsers.end(); i++)
	{
		if ((*i) == name)
			return(0);
	}
	return(1);
}

void		Channel::msgToAllUsers(std::string msg)
{
	for (std::vector<User *>::iterator i = _connectedUsers.begin(); i != _connectedUsers.end(); i++)
	{
		(*i)->sendMsg(msg);
	}
}

void		Channel::privmsgToAllUsers(User &user, std::string msg)
{
	for (std::vector<User *>::iterator i = _connectedUsers.begin(); i != _connectedUsers.end(); i++)
	{
		(*i)->sendMsg(":" + user.getNickname() + " PRIVMSG " + (*i)->getNickname() + " :" + msg);
	}
}

std::string	Channel::getUserList()
{
	std::string answer;
	for (std::vector<User *>::iterator i = _connectedUsers.begin(); i != _connectedUsers.end(); i++)
	{
		if (isOp((*i)->getNickname()) == 0)
			answer += "@";
		answer += ((*i)->getNickname());
		answer += " ";
	}
	return (answer);
}

bool	Channel::chanIsFull()
{
	if (_connectedUsers.size() >= (unsigned long)_maxUsers)
		return 0;
	return 1;
}
