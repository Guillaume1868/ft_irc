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
	std::string msg = concatMsg(args);
	if (args[1].front() == '#') // = channel
	{
		Channel *chan = _serv->findChannel(args[1]);
		chan->privmsgToAllUsers(user, msg);
	}
	else
	{
		user.sendMsg(":" + user.getNickname() + " PRIVMSG " + args[1] + " :" + msg);
	}
	return 0;
}
