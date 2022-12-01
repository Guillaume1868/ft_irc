#include "../ACommand.hpp"
#include "../Channel.hpp"

class PING : public ACommand
{
    public:
        PING(Server *serv);
        ~PING();
        int     execute(Client &clicli, std::vector<std::string> args);
};
