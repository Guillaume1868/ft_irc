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
	std::string			_host;
	std::string			_servername;
	std::string			_port;
	std::string			_pass;
	std::vector<pollfd>		_pfds;
	std::vector<User*>		_users;
	std::map<std::string, Channel>	_channels;
	std::map<std::string, ACommand*>	_commands;
  public:
	Server(std::string host, std::string port, std::string password);
	~Server();
	void		listen();
	void		pollLoop();
	int		_socket;
	int				findFdByNickname(std::string name);
	User*			getUserByNick(std::string nick);
	int				findFdByUsername(std::string name);
	void				sendMsg(User *user, std::string msg);
	void				sendMsg(std::string name, std::string msg);
	void				findCommand(std::vector<std::string> args, size_t user_i);
	std::vector<std::string>	parser(std::string input, std::string delimiter);
	std::string			getPassword();
	Channel				*findChannel(std::string name);
	void				addChannel(std::string name);
	void				delUser(std::string name);
};

#endif
