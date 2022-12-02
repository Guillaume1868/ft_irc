#ifndef USERCMD_HPP
#define USERCMD_HPP
#include "../ACommand.hpp"

class UserCmd : public ACommand
{
    public:
        UserCmd(Server *serv);
        ~UserCmd();
        int     execute(User &user, std::vector<std::string> args);
};
#endif