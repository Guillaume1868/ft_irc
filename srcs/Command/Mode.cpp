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
	int	mode = 42;
	if (args.size() != 4)
	{
		user.sendMsg(":0 461 Mode :Number of params invalid\r\n");
		return (1);
	}
	display.addError("1");
	if (_serv->findChannel(args[1])->isOp(user.getNickname()) == 1)
		user.sendMsg(":0 482 " + args[1] + " :You're not channel operator");
	display.addError("2");
	if (args[2].front() == '+')
		mode = 0;
	else if (args[2].front() == '-')
		mode = 1;
	display.addError("3");

	if (_serv->findChannel(args[1]) == 0)
	{
		user.sendMsg(":0 401 " + args[1] + " :No such nick/channel");
		return (1);
	}
	display.addError("4");
	if (args[2].find('k') != std::string::npos || args[2].find('l') != std::string::npos)
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
	else
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
			{
				(_serv->findChannel(args[1]))->addOpUser(args[3]);
			}
			else if (mode == 1)
			{
				(_serv->findChannel(args[1]))->delOpUser(args[3]);
			}	
		}
		_serv->findChannel(args[1])->msgToAllUsers(":" + user.getNickname() + " MODE " + args[3] + " " + args[2] + "\r\n");
	}
	return 0;
}
