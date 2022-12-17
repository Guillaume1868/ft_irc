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
		display.addError("Sending message to chan");
		Channel *chan = _serv->findChannel(args[1]);
		chan->privmsgToAllUsers(user, msg);
	}
	else
	{
		_serv->getUserByNick(args[1])->sendMsg(":" + user.getNickname() + " PRIVMSG " + args[1] + " :" + msg + "\r\n");
		display.addError("User : " + args[1]);
	}
	return 0;
}
