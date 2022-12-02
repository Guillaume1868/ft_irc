#ifndef PASS_HPP
#define PASS_HPP
#include "../ACommand.hpp"

class Pass : public ACommand
{
    public:
        Pass(Server *serv);
        ~Pass();
        int     execute(User &user, std::vector<std::string> args);
};
#endif