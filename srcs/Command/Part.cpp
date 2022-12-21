#include "Part.hpp"
#include "../Server.hpp"

extern Display display;

Part::Part(Server *serv): ACommand(serv)
{
}

Part::~Part()
{
}

int	Part::execute(User &user, std::vector<std::string> args)
{
	if (args.size() == 3 || args.size() == 4)
	{
		if (_serv.findChannel(args[1]) == 0)
		{
			user.sendMsg(":0 403 " + args[1] + " :No such channel\r\n");
			return (1);
		}
		if (getUserByNick(user.getNickname()) == NULL)
		{
			user.sendMsg(":0 442 " + args[1] + " :You're not on that channel\r\n");
			return (1);
		}
	}
	else
		user.sendMsg(":0 461 PART :Not enough parameters\r\n");
		
	if (args.size() == 2) // no message
	{
		_serv.findChannel(args[1]).msgToAllUsers(":" + user.getNickname() + " PART " + args[1]);
	}
	if (args.size() == 3) // with message
	{
		_serv.findChannel(args[1]).msgToAllUsers(":" + user.getNickname() + " PART " + args[1] + ":" + args[2]);
	}
	return (0);
}
