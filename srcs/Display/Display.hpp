#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <vector>
#include <string>
#include <map>
#include "../Channel.hpp"

class Display
{
public:
	Display();
	~Display();
	void update();
	void setup(std::map<std::string, Channel> *pChanPtr, std::vector<User> *pUsrPtr);
	void addMessage(std::string msg);
	void addError(std::string msg);
	std::string color(uint8_t r, uint8_t g, uint8_t b);
	std::string color();

private:
	bool _fancyMode;
	std::string trunc(std::string str, int len);
	std::vector<std::string> _messages;
	std::vector<User> *_users;
	std::map<std::string, Channel> *_channels;
};
#endif
