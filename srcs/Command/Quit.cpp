#include "Quit.hpp"
#include "../Server.hpp"

extern Display display;

Quit::Quit(Server *serv): ACommand(serv)
{
}

Quit::~Quit()
{
}

int	Quit::execute(User &user, std::vector<std::string> args)
{
	(void)args;
	_serv->delUser(user._fdFix);
	display.update();
	return (0);
}
