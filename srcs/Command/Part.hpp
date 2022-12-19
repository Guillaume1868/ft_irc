#ifndef PART_HPP
#define PART_HPP
#include "../ACommand.hpp"

class Part : public ACommand
{
    public:
        Part(Server *serv);
        ~Part();
        int     execute(User &user, std::vector<std::string> args);
};
#endif
