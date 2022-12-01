#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <vector>
#include <string>
#include <map>

class Display
{
public:
	Display(std::map<std::string, std::string> *pChanPtr, std::map<std::string, std::string> *pUsrPtr);
	Display();
	~Display();
	void update();
	void addMessage(std::string msg);
	void addError(std::string msg);
	std::string color(uint8_t r, uint8_t g, uint8_t b);
	std::string color();

private:
	bool _fancyMode;
	std::string trunc(std::string str, int len);
	std::vector<std::string> _messages;
	std::map<std::string, std::string> *_users;
	std::map<std::string, std::string> *_channels;
};
#endif