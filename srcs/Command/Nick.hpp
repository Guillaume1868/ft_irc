#ifndef NICK_HPP
#define NICK_HPP
#include "../ACommand.hpp"

class Nick : public ACommand
{
public:
	Nick(Server *serv);
	~Nick();
	int execute(User &user, std::vector<std::string> args);
};
#endif