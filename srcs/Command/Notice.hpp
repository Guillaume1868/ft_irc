#ifndef NOTICE_HPP
#define NOTICE_HPP
#include "../ACommand.hpp"

class Notice : public ACommand
{
	public:
		Notice(Server *serv);
		~Notice();
		int execute(User &user, std::vector<std::string> args);
		std::string concatMsg(std::vector<std::string> args);
};
#endif
