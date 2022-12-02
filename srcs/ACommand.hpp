#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP
#include "Channel.hpp"
#include "User.hpp"
#include "Server.hpp"

class Server;
class User;
class ACommand
{
	protected:
		Server *                _serv;

	public:
		ACommand(Server *serv);
		virtual ~ACommand();
		virtual int             execute(User& user, std::vector<std::string> args) = 0;
};
#endif