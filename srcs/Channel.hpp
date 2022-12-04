#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User.hpp"

#include <vector>

class User;

class Channel
{
  private:
	std::string			_chanName;
	std::string			_pass;
	std::vector<User *>		_connectedUsers;
	std::vector<std::string>	_bannedUsers;
	std::vector<std::string>	_opUsers;
	int				_maxUsers;
  public:
	Channel(std::string name);
	Channel(std::string name, std::string password);
	~Channel();
	void		joinChannel(User *user);
	void		delUser(std::string name);
	User		*getUserByNick(std::string nick);
	User		*getUserByUsername(std::string username);
	bool		passIsValid(std::string password);
	std::string	getChanName();
	void		setPassword(std::string password);
	std::string     getPassword();
	void		setMaxUsers(int x);
	int		getMaxUsers();
	void		addBannedUser(std::string name);
	void            delBannedUser(std::string name);
	bool		isBanned(std::string name);
	void            addOpUser(std::string name);
	void            delOpUser(std::string name);
	bool            isOp(std::string name);
	void		msgToAllUsers(std::string msg);
	void            privmsgToAllUsers(User &user, std::string msg);
	std::string     getUserList();
	bool		chanIsFull();
};

#endif
