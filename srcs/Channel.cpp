#include "Channel.hpp"
#include "User.hpp"

Channel::Channel(std::string name) : _chanName(name)
{

}

Channel::Channel(std::string name, std::string password) : _chanName(name), _pass(password)
{

}

Channel::~Channel(void)
{
}

void	Channel::joinChannel(User *user)
{
	_connectedUsers.push_back(user);
	std::cout << "User: " << user->getNickname() << " Joined: " << this->getChanName() << std::endl;
}

User	*Channel::getUserByNick(std::string nick)
{
	for (std::vector<User *>::iterator i = _usersChan.begin(); i != _connectedUsers.end(); i++)
	{
		if ((*i)->getNickname() == nick)
			return (*i);
	}
	return NULL;
}

User	*Channel::getUserByUsername(std::string username)
{
	for (std::vector<User *>::iterator i = _usersChan.begin(); i != _connectedUsers.end(); i++)
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
