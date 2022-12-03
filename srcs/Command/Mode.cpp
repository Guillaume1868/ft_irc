#include "Mode.hpp"
#include "../Server.hpp"

extern Display display;

Mode::Mode(Server *serv): ACommand(serv)
{
}

Mode::~Mode()
{
}

int	Mode::execute(User &user, std::vector<std::string> args)
{
	(void)user;
	int	mode = 42;
	if (args.size() != 3)
		return (1);
	if (args[2].front() == '+')
		mode = 0;
	else if (args[2].front() == '-')
		mode = 1;
	else
		//error args

	if (args[1].front() == '#') // = channel
	{
		if (args[2].find('k') != std::string::npos) // password channel
		{
			if (mode == 0)
				(_serv->findChannel(args[1]))->setPassword(args[3]);
			else if (mode == 1)
				(_serv->findChannel(args[1]))->setPassword("");
		}
		if (args[2].find('l') != std::string::npos) // max name
		{
			if (mode == 0)
				(_serv->findChannel(args[1]))->setMaxUsers(atoi(args[3].c_str()));
			else if (mode == 1)
				(_serv->findChannel(args[1]))->setMaxUsers(100);
		}
			
	}
	else // = user
	{
		if (args[2].find('b') != std::string::npos) // banned
		{
			if (mode == 0)
				(_serv->findChannel(args[1]))->addBannedUser(args[3]);
			else if (mode == 1)
				(_serv->findChannel(args[1]))->delBannedUser(args[3]);
				
		}
		if (args[2].find('o') != std::string::npos) // operator
		{
			if (mode == 0)
				(_serv->findChannel(args[1]))->addOpUser(args[3]);
			else if (mode == 1)
				(_serv->findChannel(args[1]))->delOpUser(args[3]);
				
		}
		
	}
	return 0;
}
