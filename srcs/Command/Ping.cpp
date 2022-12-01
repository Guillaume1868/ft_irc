#include "PING.hpp"
#include "../Server.hpp"

PING::PING(Server *serv): ACommand(serv)
{
}

PING::~PING()
{
}

int	PING::execute(User &user, std::vector<std::string> args)
{
	std::string	pong = ":0 PONG";
	for (unsigned long i = 1; i < args.size(); i++)
		pong += (" " + args[i]);
	//send to user;
    }
    return 0;
}
