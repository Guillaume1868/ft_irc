#pragma once
#include "Channel.hpp"

class Server;

class ACommand
{
	protected:
		Server *                _serv;

	public:
		ACommand(Server *serv);
		virtual ~ACommand();
		virtual int             execute(User& user, std::vector<std::string> args) = 0;
};
