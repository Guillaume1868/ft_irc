#include "UserCmd.hpp"
#include "../Server.hpp"

extern Display display;

UserCmd::UserCmd(Server *serv): ACommand(serv)
{
}

UserCmd::~UserCmd()
{
}

//USER 1<username> 2<hostname> 3<servername> 4:<realname>
int	UserCmd::execute(User &user, std::vector<std::string> args)
{
	if (args.size() < 5)
		user.sendMsg("USER :Not enough parameters\r\n");
	else if (user.getIsAuth())
		user.sendMsg(":You may not reregister");
	else
	{
		user.setNickname(args[1]);
		user.setHost(args[2]);
		user.setUsername(args[4].erase(0,1));
	}	
	return 0;
}
