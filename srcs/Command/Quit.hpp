#ifndef QUIT_HPP
#define QUIT_HPP
#include "../ACommand.hpp"

class Quit : public ACommand
{
    public:
        Quit(Server *serv);
        ~Quit();
        int     execute(User &user, std::vector<std::string> args);
};
#endif
