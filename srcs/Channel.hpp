#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User.hpp"
#include "Server.hpp"

#include <vector>

class User;
class Server;

class Channel
{
	private:
		int							_maxUsers;
		Server						*_serv;
		std::string					_chanName;
		std::string					_pass;
		std::vector<std::string>	_bannedUsers;
		std::vector<std::string>	_opUsers;
		std::vector<User *>			_connectedUsers;
	public:
		Channel(std::string name, Server *serv);
		Channel(std::string name, std::string password, Server *serv);
		~Channel();
		bool		chanIsFull();
		bool		isBanned(std::string name);
		bool		isOp(std::string name);
		bool		passIsValid(std::string password);
		int			getMaxUsers();
		int			getUserSize();
		std::string	getChanName();
		std::string	getPassword();
		std::string	getUserList();
		User		*getUserByNick(std::string nick);
		User		*getUserByUsername(std::string username);
		void		addBannedUser(std::string name);
		void		addOpUser(std::string name);
		void		delBannedUser(std::string name);
		void		delOpUser(std::string name);
		void		delUser(std::string name);
		void		joinChannel(User *user);
		void		msgToAllUsers(std::string msg);
		void		privmsgToAllUsers(User &user, std::string msg);
		void		setMaxUsers(int x);
		void		setPassword(std::string password);
};

#endif
