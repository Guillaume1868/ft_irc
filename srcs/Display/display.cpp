#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include "display.hpp"
#include "colors.hpp"
#include <unistd.h>

std::string    Display::trunc(std::string str, int len)
{
    if ((int)(str.length()) > len)
    {
        str.erase(len - 1, str.length() - (len - 1));
        str.append(".");
    }

    return (str);
}

void    Display::update()
{
    //Clear terminal
    std::cout << "\033[H\033[2J\033[3J" ;
    //Hide cursor
    std::cout << "\033[?25l";
    std::cout << GRN << "______________________ .______________________  "      << RES << std::endl;
    std::cout << GRN << "\\_   _____/\\__    ___/ |   \\______   \\_   ___ \\ " << RES << std::endl;
    std::cout << GRN << " |    __)    |    |    |   ||       _/    \\  \\/ "    << RES << std::endl;
    std::cout << GRN << " |     \\     |    |    |   ||    |   \\     \\____"   << RES << std::endl;
    std::cout << GRN << " \\___  /     |____|____|___||____|_  /\\______  /"    << RES << std::endl;
    std::cout << GRN << "     \\/          /_____/           \\/        \\/ "   << RES << std::endl;




    //Display channel list
    //Put cursor topright (col 50)
    std::cout << "\033[1;50H" << "Channels :" << std::endl;
    for(std::map<std::string, std::string>::iterator it = _channels->begin(); it != _channels->end(); ++it)
    {
        if (std::distance(_channels->begin(), it) >= 4)
        {
            std::cout << "\033[6;50H" << std::distance(it, _channels->end()) << " more" << std::endl;
            break;
        }
        std::cout << "\033[" << std::distance(_channels->begin(), it) + 2 << ";50H" << trunc((*it).first, 14) << std::endl;
    }

    //Display user list
    //Put cursor topright (col 65)
    std::cout << "\033[1;65H" << "Users :" << std::endl;
    for(std::map<std::string, std::string>::iterator it = _users->begin(); it != _users->end(); ++it)
    {
        if (std::distance(_users->begin(), it) >= 4)
        {
            std::cout << "\033[6;65H" << std::distance(it, _users->end()) << " more" << std::endl;
            break;
        }
        std::cout << "\033[" << std::distance(_users->begin(), it) + 2 << ";65H" << trunc((*it).first, 14) << std::endl;
    }

    //Display message list
    //Put cursor to correct line
    std::cout << "\033[6;1H" << std::endl;
    for(std::vector<std::string>::iterator it = _messages.begin(); it != _messages.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

void    Display::addMessage(std::string msg)
{
    if (_messages.size() == 20)
    {
        _messages.erase(_messages.begin());
    }
    _messages.push_back(msg);
    this->update();
}

Display::Display(std::map<std::string, std::string> *pChanPtr, std::map<std::string, std::string> *pUsrPtr)
{
    this->_channels = pChanPtr;
    this->_users = pUsrPtr;
}

Display::~Display()
{
    //Display cursor
    std::cout << "\033[?25h" << std::flush;
}

int main()
{
    std::map<std::string, std::string> _users;
    std::map<std::string, std::string> _channels;
    Display disp(&_channels,&_users);

    _channels.insert(std::pair<std::string, std::string>("chan", "chan"));
    _users.insert(std::pair<std::string, std::string>("Gaubert", "Guillaume"));
    disp.addMessage("1");
    usleep(500000);
    _channels.insert(std::pair<std::string, std::string>("4aaaaaaaaaaaaaaaa", "4"));
    _users.insert(std::pair<std::string, std::string>("1aaaaaaaaaaaaaaa", "1"));
    _users.insert(std::pair<std::string, std::string>("2", "2"));
    disp.addMessage("2");
    usleep(500000);
    _channels.insert(std::pair<std::string, std::string>("5", "5"));
    _channels.insert(std::pair<std::string, std::string>("3", "3"));
    disp.addMessage("3");
    usleep(500000);
    _users.insert(std::pair<std::string, std::string>("3", "3"));
    _users.insert(std::pair<std::string, std::string>("4", "4"));
    disp.addMessage("4");
    usleep(500000);
    _channels.insert(std::pair<std::string, std::string>("2", "2"));
    disp.addMessage("5");
    usleep(500000);
    _channels.insert(std::pair<std::string, std::string>("1", "1"));
    _users.insert(std::pair<std::string, std::string>("5", "5"));
    _users.insert(std::pair<std::string, std::string>("6", "6"));
    disp.addMessage("6");
    usleep(500000);
    disp.addMessage("7");
    usleep(500000);
    _channels.insert(std::pair<std::string, std::string>("6", "6"));
    disp.addMessage("8");
}