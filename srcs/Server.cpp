#include "Server.hpp"
#include "User.hpp"

#include <vector>

Server::Server(std::string host, std::string port, std::string pass) : _host(host), _port(port), _pass(pass)
{
	display.setup(&_channels, &_users);
	display.update();
	listen();
	pollLoop(); //testing
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
		display.addError("Error: getaddrinfo failed");
		//kill server function;
	}
	if ((_socket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
	{
		display.addError("Error: socket failed");
		//kill server function;
	}
	else if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
	{
		close(_socket);
		freeaddrinfo(servinfo);
		display.addError("Error: setsockopt failed");
		//kill server function;
	}
	else if (bind(_socket, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		close(_socket);
		freeaddrinfo(servinfo);
		display.addError("Error: binding failed");
		//kill server function;
	}
	int flags = fcntl(_socket, F_GETFL, 0);
    	fcntl(_socket, F_SETFL, flags | O_NONBLOCK);
	freeaddrinfo(servinfo);
	if (::listen(_socket, SOMAXCONN) == -1)
		display.addError("Error: listening failed");
	display.addMessage( display.color(0,255,0) + "Server is listening on port " + _port);
}

void	Server::pollLoop()
{
	pollfd pfd = {.fd = _socket, .events = POLLIN, .revents = 0};
	_pfds.push_back(pfd);
	while (1)
	{
		if (poll(_pfds.data(), _pfds.size(), -1) == -1)
		{
			display.addError("Error: poll");
			//kill server function;
		}
		for (size_t i = 0; i < _pfds.size(); i++)
		{
			if (_pfds[i].revents & POLLIN)
			{
				if (_pfds[i].fd == _socket)
				{
					int new_fd;
					if ((new_fd = accept(_socket, NULL, NULL)) == -1)
						throw std::runtime_error("error: accept");
					_users.push_back(*(new User(new_fd)));
					pollfd pfd = {.fd = new_fd, .events = POLLIN, .revents = 0};
					_pfds.push_back(pfd);
				}
				else if (i > 0)
				{
					char buffer[4096];
					int n;
					int end = -1;

					memset(buffer, '\0', sizeof(buffer));
					n = read(_users[i - 1].getFd(), buffer, sizeof(buffer));
					if (n > 0)
						_users[i - 1]._msgBuffer += buffer;
 	      				while(_users[i - 1]._msgBuffer[++end])
            					;
    					if (_users[i - 1]._msgBuffer[end - 1] == '\n')
					{
						if ((_users[i - 1]._msgBuffer).find("\r\n", 0) != std::string::npos)
						{
							display.addMessage("Message:" + _users[i - 1]._msgBuffer);
							(_users[i - 1]._msgBuffer).clear();
						}
						else
						{
							display.addMessage("Message from NC:" + _users[i - 1]._msgBuffer);
							(_users[i - 1]._msgBuffer).clear();
						}
					}
				}
			}
		}
	}
}

std::vector<std::string>	Server::parser(std::string input, std::string delimiter)
{
	size_t pos = 0;
	std::string token;
	std::vector<std::string> tmp;
	while ((pos = input.find(delimiter)) != std::string::npos) {
		token = input.substr(0, pos);
		input.erase(0, pos + 1);
		tmp.push_back(token);
	}
	tmp.push_back(input);
	return (tmp);
}
