#ifndef KICK_HPP
#define KICK_HPP
#include "../ACommand.hpp"

class Kick : public ACommand
{
    public:
        Kick(Server *serv);
        ~Kick();
        int     execute(User &user, std::vector<std::string> args);
};
#endif
