#include <string>
#include <iostream>
#include "Server.hpp"
#include "Display/Display.hpp"


int	main(int argc, char **argv)
{
	Display display;
	if (argc != 3)
	{
		display.addError("Usage: ./irc <port> <password>");
		return 1;
	}
	std::string port = argv[1];
	for (std::string::iterator i = port.begin(); i != port.end(); i++)
	{
		if (isdigit(*i) == 0)
		{
			display.addError("Error: Port must be a number");
			return 1;
		}
	}
	if (atoi(argv[1]) > 65535)
	{
		display.addError("Error: Max port is 65535");
		return 1;
	}
	Server	serv("0.0.0.0", argv[1], argv[2]);
	return 0;
}
