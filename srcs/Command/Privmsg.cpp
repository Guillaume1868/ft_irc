#include "Privmsg.hpp"
#include "../Server.hpp"

extern Display display;

Privmsg::Privmsg(Server *serv): ACommand(serv)
{
}

Privmsg::~Privmsg()
{
}

std::string	concatMsg(std::vector<std::string> args)
{
	std::string fullMsg;
	for(std::vector<std::string>::iterator i = args.begin()+2; i != args.end(); i++)
	{
		fullMsg += (*i);
		fullMsg += " ";
	}
	return (fullMsg);
}

int	Privmsg::execute(User &user, std::vector<std::string> args)
{
	if (args.size() < 3) {
		user.sendMsg(" 461 PRIVMSG :Not enough parameters\r\n");
		return 1;
	}
	std::string msg = concatMsg(args);
	if (args[1].front() == '#') // = channel
	{
		Channel *chan = _serv->findChannel(args[1]);
		if (!chan)
		{
			user.sendMsg(" 404 " + args[1] + " :Cannot send to channel\r\n");
			return 1;
		}
		chan->privmsgToAllUsers(user, msg);
	}
	else
	{
		User *target = _serv->getUserByNick(args[1]);
		if (!target)
		{
			user.sendMsg(" 401 " + args[1] + " :No such nick/channel\r\n");
			return 1;
		}
		target->sendMsg(":" + user.getNickname() + " PRIVMSG " + args[1] + " " + msg + "\r\n");
	}
	return 0;
}
