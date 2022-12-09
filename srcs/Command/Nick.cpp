#include "Nick.hpp"
#include "../Server.hpp"

extern Display display;

Nick::Nick(Server *serv): ACommand(serv)
{
}

Nick::~Nick()
{
}

int	Nick::execute(User &user, std::vector<std::string> args)
{
	if (args.size() < 2)
		user.sendMsg(":" + user.getHost() + "431" + ":No nickname given\r\n");
	else if (_serv->findFdByNickname(args[1]) != 0)
		user.sendMsg(":" + user.getHost() + "433" + args[1] + " :Nickname is already in use\r\n");
	else
	{
		std::string oldNick = user.getNickname();
		user.setNickname(args[1]);
		user.sendMsg(":" + oldNick + " NICK " + args[1] + "\r\n"); // TODO:all users
	}
	return 0;
}
