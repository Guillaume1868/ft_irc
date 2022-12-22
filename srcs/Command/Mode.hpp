#pragma once
#include "../ACommand.hpp"

class Mode : public ACommand
{
	public:
		Mode(Server *serv);
		~Mode();
		int execute(User &user, std::vector<std::string> args);
		bool detectTargetType(std::string target);
};
