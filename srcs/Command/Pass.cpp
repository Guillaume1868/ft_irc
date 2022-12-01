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
	display.addMessage(args[1]);
	user.setPassword(args[1]);
    return 0;
}
