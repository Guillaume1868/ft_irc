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
	Channel *chan = (_serv->findChannel(args[1]));
	if (chan == 0)
	{
		(_serv->addChannel(args[1]));
		chan = (_serv->findChannel(args[1]));
		chan->addOpUser(user.getNickname());
		if (args.size() == 3)
			chan->setPassword(args[2]);
	}
	if ((args.size() == 3 && chan->passIsValid(args[2])) || args.size() == 2)
	{
		chan->joinChannel(&user);
		chan->msgToAllUsers(":" + user.getNickname() + " JOIN :" + chan->getChanName() + "\r\n");
		user.sendMsg(":0 331 " + chan->getChanName() + " :No topic is set\r\n");
		user.sendMsg(":0 353 " + user.getNickname() + " = " + chan->getChanName() + " :" + chan->getUserList() + "\r\n");
		user.sendMsg(":0 366 " + user.getNickname() + " " + chan->getChanName() + " :End of NAMES list\r\n");
	}
	return 0;
}
