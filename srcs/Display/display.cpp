#include <vector>
#include <string>
#include <iostream>
#include "display.hpp"
#include "colors.hpp"
#include <unistd.h>

void    Display::update()
{
    //Clear terminal
    std::cout << "\033[H\033[2J\033[3J" ;
    std::cout << GRN << "______________________ .______________________  "      << RES << std::endl;
    std::cout << GRN << "\\_   _____/\\__    ___/ |   \\______   \\_   ___ \\ " << RES << std::endl;
    std::cout << GRN << " |    __)    |    |    |   ||       _/    \\  \\/ "    << RES << std::endl;
    std::cout << GRN << " |     \\     |    |    |   ||    |   \\     \\____"   << RES << std::endl;
    std::cout << GRN << " \\___  /     |____|____|___||____|_  /\\______  /"    << RES << std::endl;
    std::cout << GRN << "     \\/          /_____/           \\/        \\/ "   << RES << std::endl;



    //Display message list
    for(std::vector<std::string>::iterator it = messages.begin(); it != messages.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

void    Display::addMessage(std::string msg)
{
    if (messages.size() == 3)
    {
        messages.erase(messages.begin());
    }
    messages.push_back(msg);
    this->update();
}

int main()
{
    Display disp;

    disp.addMessage("1");
    usleep(100000);
    disp.addMessage("2");
    usleep(100000);
    disp.addMessage("3");
    usleep(100000);
    disp.addMessage("4");
    usleep(100000);
    disp.addMessage("5");
    usleep(100000);
    disp.addMessage("6");
    usleep(100000);
    disp.addMessage("7");
    usleep(100000);
    disp.addMessage("8");
}