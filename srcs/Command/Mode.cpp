#include "Mode.hpp"
#include "../Server.hpp"

Mode::Mode(Server *serv): ACommand(serv)
{
}

Mode::~Mode()
{
}

int	Mode::execute(User &user, std::vector<std::string> args)
{
	(void)user;
	detectTargetType(args[1]);
	return 0;
}

bool	Mode::detectTargetType(std::string target)
{
	(void)target;
	std::cout << "Debug : " << target;
	//if (target.front() == '#')
	//{
		std::cout << "Channel";
		return(0);
	//}
	//else
	//{
		std::cout << "User";
		return(1);
	//}
}
