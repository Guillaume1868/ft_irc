#ifndef JOIN_HPP
#define JOIN_HPP
#include "../ACommand.hpp"

class Join : public ACommand
{
	public:
		Join(Server *serv);
		~Join();
		int execute(User &user, std::vector<std::string> args);
};
#endif
