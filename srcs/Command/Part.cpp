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
	if (args.size() > 2 && args[2].front() == ":")
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
	
	std::string fullMsg;
        for(std::vector<std::string>::iterator i = args.begin()+2; i != args.end(); i++)
        {
                fullMsg += (*i);
                fullMsg += " ";
        }
        return (fullMsg);

	_serv.findChannel(args[1]).msgToAllUsers(":" + user.getNickname() + " PART " + args[1] + ":" + args[2]);
	return (0);
}
