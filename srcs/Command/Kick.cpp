#include "Kick.hpp"
#include "../Server.hpp"

extern Display display;

Kick::Kick(Server *serv) : ACommand(serv)
{
}

Kick::~Kick()
{
}

int Kick::execute(User &user, std::vector<std::string> args)
{
	std::vector<std::string> targets;
	std::string tmp;
	size_t pos = 0;
	while ((pos = args[2].find(",")) != std::string::npos)
	{
		tmp = args[2].substr(0, pos);
		targets.push_back(tmp);
		args[2].erase(0, pos + 1);
	}
	targets.push_back(args[2]);
	if (!_serv->findChannel(args[1]))
	{
		user.sendMsg(":0 403 " + args[1] + " :No such channel\r\n");
		return 1;
	}
	if (_serv->findChannel(args[1])->getUserByNick(user.getNickname()) != 0)
	{
		user.sendMsg(":0 442 " + args[1] + " :You're not on that channel\r\n");
		return 1;
	}
	if (args.size() < 3)
	{
		user.sendMsg(":0 461 " + args[0] + " :Not enough parameters\r\n");
		return 1;
	}
	if (_serv->findChannel(args[1])->isOp(user.getNickname()))
	{
		user.sendMsg(":0 482 " + args[1] + " :You're not channel operator");
		return 1;
	}

	for (std::vector<std::string>::iterator i = targets.begin(); i != targets.end(); i++)
	{
		_serv->findChannel(args[1])->delUser(_serv->getUserByNick(*i)->getUsername());
		std::string msg = ":" + user.getNickname() + " KICK " + args[1] + " " + (*i);
		if (args.size() == 4)
			msg += " " + args[3];
		else
			msg += " :" + user.getNickname();
		msg += "\r\n";
		_serv->findChannel(args[1])->msgToAllUsers(msg);
	}
	display.update();
	return (0);
}
