#include "Ping.hpp"
#include "../Server.hpp"

Ping::Ping(Server *serv): ACommand(serv)
{
}

Ping::~Ping()
{
}

int	Ping::execute(User &user, std::vector<std::string> args)
{
	std::string	pong = ":0 PONG";
	for (unsigned long i = 1; i < args.size(); i++)
		pong += (" " + args[i]);
	//send to user;
    return 0;
}
