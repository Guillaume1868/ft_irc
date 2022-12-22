#ifndef PING_HPP
#define PING_HPP
#include "../ACommand.hpp"

class Ping : public ACommand
{
	public:
		Ping(Server *serv);
		~Ping();
		int execute(User &user, std::vector<std::string> args);
};
#endif