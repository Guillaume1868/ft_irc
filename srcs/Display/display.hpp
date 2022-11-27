#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <vector>
#include <string>

class Display {
    public:
        void    update();
        void    addMessage(std::string msg);

    private:
        std::vector<std::string> messages;
};

#endif