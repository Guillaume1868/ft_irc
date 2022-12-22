#include "Server.hpp"
#include "Command/Ping.hpp"
#include "Command/Pass.hpp"
#include "Command/Mode.hpp"
#include "Command/Nick.hpp"
#include "Command/UserCmd.hpp"
#include "Command/Join.hpp"
#include "Command/Privmsg.hpp"
#include "Command/Notice.hpp"
#include "Command/Quit.hpp"
#include "Command/Kick.hpp"
#include "Command/Part.hpp"

#include <vector>

extern Display display;

Server::Server(std::string host, std::string port, std::string pass) : _host(host), _pass(pass), _port(port)
{
	display.setup(&_channels, &_users);
	display.update();
	listen();
	_commands["PING"] = new Ping(this);
	_commands["PASS"] = new Pass(this);
	_commands["MODE"] = new Mode(this);
	_commands["NICK"] = new Nick(this);
	_commands["USER"] = new UserCmd(this);
	_commands["JOIN"] = new Join(this);
	_commands["QUIT"] = new Quit(this);
	_commands["KICK"] = new Kick(this);
	_commands["PRIVMSG"] = new Privmsg(this);
	_commands["NOTICE"] = new Notice(this);
	_commands["PART"] = new Part(this);
	pollLoop();
}

Server::~Server(void)
{
	/*for (std::map<std::string, ACommand*>::iterator i = _commands.end(); i != _commands.begin(); i--)
	{
		delete(*i->second);
	}*/
	
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
		exit(1);
	}
	if ((_socket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
	{
		display.addError("Error: socket failed");
		exit(1);
	}
	else if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
	{
		close(_socket);
		freeaddrinfo(servinfo);
		display.addError("Error: setsockopt failed");
		exit(1);
	}
	else if (bind(_socket, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		close(_socket);
		freeaddrinfo(servinfo);
		display.addError("Error: binding failed");
		exit(1);
	}
	int flags = fcntl(_socket, F_GETFL, 0);
    	fcntl(_socket, F_SETFL, flags | O_NONBLOCK);
	freeaddrinfo(servinfo);
	if (::listen(_socket, SOMAXCONN) == -1)
	{
		display.addError("Error: listening failed");
		exit(1);
	}
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
			exit(1);
		}
		for (size_t i = 0; i < _pfds.size(); i++)
		{
			if (_pfds[i].revents & POLLIN)
			{
				if (_pfds[i].fd == _socket)
				{
					int new_fd;
					if ((new_fd = accept(_socket, NULL, NULL)) == -1)
						display.addError("Error: accept");
					_users.push_back(new User(new_fd, this));
					pollfd pfd = {.fd = new_fd, .events = POLLIN, .revents = 0};
					_pfds.push_back(pfd);
				}
				else if (i > 0)
				{
					char buffer[4096];
					int n;
					int end = -1;

					memset(buffer, '\0', sizeof(buffer));
					n = read(_users[i - 1]->getFd(), buffer, sizeof(buffer));
					if (n > 0)
						_users[i - 1]->_msgBuffer += buffer;
					else if (n == 0)
					{
						delUser(_users[i - 1]->getNickname());
						display.update();
					}
 	      				while(_users[i - 1]->_msgBuffer[++end])
            					;
    					if (_users[i - 1]->_msgBuffer[end - 1] == '\n')
					{
						if ((_users[i - 1]->_msgBuffer).find("\r\n", 0) != std::string::npos)
						{
							display.addMessage(" > " + _users[i - 1]->_msgBuffer);
							std::vector<std::string> parsed = parser(_users[i - 1]->_msgBuffer, " ");
							findCommand(parsed, i);
							(_users[i - 1]->_msgBuffer).clear();
						}
						else
						{
							display.addMessage(display.color(0,0,255) + " > " + display.color(255,255,255) + _users[i - 1]->_msgBuffer);
							std::vector<std::string> parsed = parser(_users[i - 1]->_msgBuffer, " ");
							findCommand(parsed, i);
							(_users[i - 1]->_msgBuffer).clear();
						}
					}
				}
			}
		}
	}
}

void	Server::findCommand(std::vector<std::string> args, size_t user_i)
{
	std::map<std::string, ACommand*>::iterator i = _commands.find(args.front());
	if (i != _commands.end())
	{
		ACommand *command = i->second;
		command->execute(*_users[user_i - 1], args);
	}
}

std::vector<std::string>	Server::parser(std::string input, std::string delimiter)
{
	size_t pos = 0;
	std::string token;
	std::vector<std::string> tmp;
	while ((pos = input.find(delimiter)) != std::string::npos)
	{
		token = input.substr(0, pos);
		input.erase(0, pos + 1);
		tmp.push_back(token);
	}
	input.erase(input.length() - 1, 1);
	if (input.find('\r') != std::string::npos)
		input.erase(input.length() - 1, 1);
	tmp.push_back(input);
	return (tmp);
}

int	Server::findFdByNickname(std::string name)
{
	for (std::vector<User *>::iterator i = _users.begin(); i != _users.end(); i++)
	{
		if ((*i)->getNickname() == name)
			return ((*i)->getFd());
	}
	return 0;
}

User*	Server::getUserByNick(std::string nick)
{
	for (std::vector<User *>::iterator i = _users.begin(); i != _users.end(); i++)
		{
			if ((*i)->getNickname() == nick)
				return *i;
		}
	return 0;
}

int	Server::findFdByUsername(std::string name)
{
	for (std::vector<User *>::iterator i = _users.begin(); i != _users.end(); i++)
	{
		if ((*i)->getUsername() == name)
			return ((*i)->getFd());
	}
	return 0;
}

void	Server::sendMsg(std::string name, std::string msg)
{
	int b_sent = 0;
	int total_b_sent = 0;
	while (total_b_sent != (int)msg.size())
	{
		b_sent = send(findFdByNickname(name), &msg[b_sent], msg.size() - total_b_sent, 0);
		total_b_sent += b_sent;
	}
	display.addMessage(" < " + msg);
}

void	Server::sendMsg(User *user, std::string msg)
{
	int b_sent = 0;
	int total_b_sent = 0;
	while (total_b_sent != (int)msg.size())
	{
		b_sent = send(user->getFd(), &msg[b_sent], msg.size() - total_b_sent, 0);
		total_b_sent += b_sent;
	}
	display.addMessage(" < " + msg);
}

std::string	Server::getPassword()
{
	return (_pass);
}

Channel	*Server::findChannel(std::string name)
{
	for (std::map<std::string, Channel>::iterator i = _channels.begin(); i != _channels.end(); i++)
	{
		if ((*i).second.getChanName() == name)
			return (&(*i).second);
	}
	return 0;
}

void    Server::addChannel(std::string name)
{
	_channels.insert(std::make_pair(name, Channel(name, this)));
}

void	Server::delUser(std::string name)
{
	// Delete user from all channels
	for (std::map<std::string, Channel>::iterator i = _channels.begin(); i != _channels.end(); ++i)
	{
		(*i).second.delUser(name);
	}
	int fdTmp = findFdByNickname(name);
	// Erase user
	for (std::vector<User *>::iterator i = _users.begin(); i != _users.end(); ++i)
	{
		if ((*i)->getNickname() == name)
		{
			display.addMessage("User on FD " + std::to_string((*i)->getFd()) + " closed the connexion\r\n");
			delete (*i);
			_users.erase(i);
			break ;
		}
	}
	// Erase _pfds
	for (std::vector<pollfd>::iterator i = _pfds.begin(); i != _pfds.end(); ++i)
	{
		if ((*i).fd == fdTmp)
		{
			_pfds.erase(i);
			break ;
		}
	}
}

void	Server::delChanIfEmpty(std::string name)
{
	for (std::map<std::string, Channel>::iterator i = _channels.begin(); i != _channels.end();)
	{
		if ((*i).second.getUserSize() == 0 && (*i).second.getChanName() == name)
		{
			_channels.erase(i++);
		}
		else
			i++;
	}

}
