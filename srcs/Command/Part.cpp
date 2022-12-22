#include "Part.hpp"
#include "../Server.hpp"

extern Display display;

Part::Part(Server *serv): ACommand(serv)
{
}

Part::~Part()
{
}

std::string fullArg(std::vector<std::string> args)
{
	std::string fullMsg;
	for(std::vector<std::string>::iterator i = args.begin()+2; i != args.end(); i++)
	{
			fullMsg += (*i);
			fullMsg += " ";
	}
	fullMsg.erase(fullMsg.end() - 1, fullMsg.end());

	return (fullMsg);
}

int	Part::execute(User &user, std::vector<std::string> args)
{
	if (args.size() > 2 && args[2].front() == ':')
	{
		if (_serv->findChannel(args[1]) == 0)
		{
			user.sendMsg(":0 403 " + args[1] + " :No such channel\r\n");
			return (1);
		}
		if (_serv->findChannel(args[1])->getUserByNick(user.getNickname()) == NULL)
		{
			user.sendMsg(":0 442 " + args[1] + " :You're not on that channel\r\n");
			return (1);
		}
	}
	else
	{
		user.sendMsg(":0 461 PART :Not enough parameters\r\n");
		return (1);
	}
	
	std::string fullMsg = fullArg(args);
	_serv->findChannel(args[1])->msgToAllUsers(":" + user.getNickname() + " PART " + args[1] + " " + fullMsg + "\r\n");
	_serv->findChannel(args[1])->delUser(user.getNickname());
	return (0);
}
