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

class Server
{
  private:
	std::string _host;
	std::string _servername;
	std::string _port;
	std::string _pass;
//	int			_pfds[500];

  public:
	Server(std::string host, std::string port, std::string password);
	~Server();
	void	listen();
	void	pollLoop();
	int                 _socket;
};

#endif
