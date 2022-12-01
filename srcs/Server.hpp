#ifndef SERVER_H
#define SERVER_H

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
#include "Command/Ping.hpp"
#include "Command/Pass.hpp"

class ACommand;

class Server
{
  private:
	std::string			_host;
	std::string			_servername;
	std::string			_port;
	std::string			_pass;
	std::vector<pollfd>		_pfds;
	std::vector<User>		_users;
	std::map<std::string, Channel>	_channels;
	std::map<std::string, ACommand*>	_commands;
  public:
	Server(std::string host, std::string port, std::string password);
	~Server();
	void		listen();
	void		pollLoop();
	int		_socket;
	int				findFdByNickname(std::string name);
	int				findFdByUsername(std::string name);
	void				sendMsg(User *user, std::string msg);
	void				sendMsg(std::string name, std::string msg);
	void				findCommand(std::vector<std::string> args, size_t user_i);
	std::vector<std::string>	parser(std::string input, std::string delimiter);
};

#endif
