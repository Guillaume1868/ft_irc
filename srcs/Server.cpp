#include "Server.hpp"

Server::Server(std::string host, std::string port, std::string pass) : _host(host), _port(port), _pass(pass)
{
	listen();
	//pollLoop(); testing
}

Server::~Server(void)
{
}

void Server::listen()
{
	addrinfo hints, *servinfo;
	std::memset(&hints, 0, sizeof(addrinfo));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_CANONNAME;
	const int enable = 1;	
	if (getaddrinfo(_host.c_str(), _port.c_str(), &hints, &servinfo) != 0)
	{
		std::cout << "Error: getaddrinfo failed" << std::endl;
		//kill server function;
	}
	if ((_socket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
	{
		std::cout << "Error: socket failed" << std::endl;
		//kill server function;
	}
	else if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
	{
		close(_socket);
		freeaddrinfo(servinfo);
		std::cout << "Error: setsockopt failed" << std::endl;
		//kill server function;
	}
	else if (bind(_socket, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		close(_socket);
		freeaddrinfo(servinfo);
		std::cout << "Error: binding failed" << std::endl;
		//kill server function;
	}
	freeaddrinfo(servinfo);
	if (::listen(_socket, SOMAXCONN) == -1)
		std::cout << "Error: listening failed" << std::endl;
	std::cout << "Server is listening on port " << _port << std::endl;
}

void	Server::pollLoop()
{
	struct pollfd fds[200];
	int				rc;
	int				nfds = 1;
	std::string		buffer[4096];
	memset(fds, 0 , sizeof(fds));
	fds[0].fd = _socket;
	fds[0].events = POLLIN;
	int	timeout = (3 * 60 * 1000);
	while (1)
	{
		rc = poll(fds, 1, timeout);
		for (int i = 0; i < (int)(sizeof(fds)); i++)
		{
				//std::cout << "----------------------------\n";
				//std::cout << fds[i].fd << std::endl;
				//std::cout << _socket << std::endl;
				//std::cout << "----------------------------\n";
			if (fds[i].revents == 0)
			{
				//std::cout << "continue\n";
				continue;
			}
			if (fds[i].fd == _socket)
			{
				int	new_sd = accept(_socket, NULL, NULL);
				fds[nfds].fd = new_sd;
				fds[nfds].events = POLLIN;
				nfds++;
			}
			else
			{
				std::cout << "Read\n\n";
				rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
				send(fds[i].fd, buffer, rc, 0);
			}
		}
	}
}
