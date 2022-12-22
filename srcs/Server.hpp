#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <fcntl.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>
#include <vector>
#include <map>

#include "User.hpp"
#include "Channel.hpp"
#include "Display/Display.hpp"
#include "ACommand.hpp"

class Channel;
class ACommand;

class Server
{
	private:
		std::map<std::string, ACommand*>	_commands;
		std::map<std::string, Channel>	_channels;
		std::string			_host;
		std::string			_pass;
		std::string			_port;
		std::string			_servername;
		std::vector<pollfd>		_pfds;
		std::vector<User*>		_users;
	public:
		Server(std::string host, std::string port, std::string password);
		~Server();
		Channel		*findChannel(std::string name);
		int			findFdByNickname(std::string name);
		int			findFdByUsername(std::string name);
		int			_socket;
		std::string					getPassword();
		std::vector<std::string>	parser(std::string input, std::string delimiter);
		User*		getUserByNick(std::string nick);
		void		addChannel(std::string name);
		void		delChanIfEmpty(std::string name);
		void		delUser(std::string name);
		void		findCommand(std::vector<std::string> args, size_t user_i);
		void		sendMsg(std::string name, std::string msg);
		void		sendMsg(User *user, std::string msg);
		void		listen();
		void		pollLoop();
};

#endif
