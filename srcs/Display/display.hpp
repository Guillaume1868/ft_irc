#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <vector>
#include <string>
#include <map>

class Display {
    public:
        Display(std::map<std::string, std::string> *pChanPtr, std::map<std::string, std::string> *pUsrPtr);
        ~Display();
        void    update();
        void    addMessage(std::string msg);

    private:
        std::string    trunc(std::string str, int len);
        std::vector<std::string> _messages;
        std::map<std::string, std::string> *_users;
        std::map<std::string, std::string> *_channels;

};

#endif