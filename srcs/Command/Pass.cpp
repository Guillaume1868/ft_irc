#include "Pass.hpp"
#include "../Server.hpp"

extern Display display;

Pass::Pass(Server *serv): ACommand(serv)
{
}

Pass::~Pass()
{
}

int	Pass::execute(User &user, std::vector<std::string> args)
{
	if (user.getIsAuth())
		user.sendMsg(":You may not reregister\r\n");
	if (args.size() < 2)
		user.sendMsg("PASS :Not enough parameters\r\n");
	user.setPassword(args[1]);
    return 0;
}
