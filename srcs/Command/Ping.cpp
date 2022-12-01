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
	(void)user;
	std::string	pong = ":0 PONG";
	for (unsigned long i = 1; i < args.size(); i++)
		pong += (" " + args[i]);
	std::cout << "Ping/Pong\n";
	//send to user;
    return 0;
}
