#include "Pass.hpp"
#include "../Server.hpp"

extern Display display;

Pass::Pass(Server *serv): ACommand(serv)
{
}

Pass::~Pass()
{
}

//<command> :Not enough parameters
int	Pass::execute(User &user, std::vector<std::string> args)
{
	user.sendMsg("nique");
	if (user.getIsAuth())
		user.sendMsg(":You may not reregister");
	if (args.size() < 2)
		user.sendMsg("PASS :Not enough parameters");
	user.setPassword(args[1]);
    return 0;
}
