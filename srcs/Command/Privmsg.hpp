#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP
#include "../ACommand.hpp"

class Privmsg : public ACommand
{
	public:
		Privmsg(Server *serv);
		~Privmsg();
		int execute(User &user, std::vector<std::string> args);
	private:
		std::string	concatMsg(std::vector<std::string> args);
};
#endif
