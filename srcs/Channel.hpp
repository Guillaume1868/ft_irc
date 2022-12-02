#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User.hpp"

#include <vector>

class User;

class Channel
{
  private:
	std::string		_chanName;
	std::string		_pass;
	std::vector<User *>	_connectedUsers;
  public:
	Channel(std::string name);
	Channel(std::string name, std::string password);
	~Channel();
	void		joinChannel(User *user);
	User		*getUserByNick(std::string nick);
	User		*getUserByUsername(std::string username);
	bool		passIsValid(std::string password);
	std::string	getChanName();
};

#endif
