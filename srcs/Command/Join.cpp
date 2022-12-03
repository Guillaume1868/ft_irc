#include "Join.hpp"
#include "../Server.hpp"

extern Display display;

Join::Join(Server *serv): ACommand(serv)
{
}

Join::~Join()
{
}

int	Join::execute(User &user, std::vector<std::string> args)
{
	if (args[1].find_first_not_of("abcdefghijklmnopqrstuvwxyz1234567890", 0) != std::string::npos)
	{
		user.sendMsg(":0 403 " + user.getNickname() + " " + args[1] + " :No such channel\n");
		return 1;
	}
	if (args.size() < 2)
	{
		user.sendMsg(":0 461 JOIN :Not enough parameters");
	}

	Channel *chan = (_serv->findChannel(args[1]));
	if (chan == 0)
	{
		(_serv->addChannel(args[1]));
		chan = (_serv->findChannel(args[1]));
		if (chan->chanIsFull() == 0)
		{
			user.sendMsg(":0  471 " + args[1] + " :Cannot join channel (+l)");
			return 1;
		}
		chan->addOpUser(user.getNickname());
		if (args.size() == 3)
			chan->setPassword(args[2]);
	}
	if ((args.size() == 3 && chan->passIsValid(args[2])) || args.size() == 2)
	{
		if (chan->chanIsFull() == 0)
		{
			user.sendMsg(":0  471 " + args[1] + " :Cannot join channel (+l)");
			return 1;
		}
		if (chan->isBanned(user.getNickname()) == 0)
		{
			user.sendMsg(":0 474 " + args[1] + " :Cannot join channel (+b)");
		}
		chan->joinChannel(&user);
		chan->msgToAllUsers(":" + user.getNickname() + " JOIN :" + chan->getChanName() + "\r\n");
		user.sendMsg(":0 331 " + chan->getChanName() + " :No topic is set\r\n");
		user.sendMsg(":0 353 " + user.getNickname() + " = " + chan->getChanName() + " :" + chan->getUserList() + "\r\n");
		user.sendMsg(":0 366 " + user.getNickname() + " " + chan->getChanName() + " :End of NAMES list\r\n");
	}
	return 0;
}
