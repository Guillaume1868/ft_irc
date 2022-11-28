#include <string>
#include <iostream>
#include "Server.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: ./irc <port> <password>" << std::endl;
		return 1;
	}
	std::string port = argv[1];
	for (std::string::iterator i = port.begin(); i != port.end(); i++)
	{
		if (isdigit(*i) == 0)
		{
			std::cout << "Error: Port must be a number" << std::endl;
			return 1;
		}
	}
	if (atoi(argv[1]) > 65535)
	{
		std::cout << "Error: Max port is 65535" << std::endl;
		return 1;
	}
	Server	serv("0.0.0.0", argv[1], argv[2]);
}
