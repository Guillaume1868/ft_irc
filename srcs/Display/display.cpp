#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include "display.hpp"
#include <unistd.h>

std::string Display::trunc(std::string str, int len)
{
	if ((int)(str.length()) > len)
	{
		str.erase(len - 1, str.length() - (len - 1));
		str.append(".");
	}

	return (str);
}

std::string Display::color(uint8_t r, uint8_t g, uint8_t b)
{
	return "\033[38;2;" + std::to_string((int)r) + ";" + std::to_string((int)g) + ";" + std::to_string((int)b) + "m";
}

std::string Display::color()
{
	return "\033[39;49m";
}

void Display::update()
{
	if (_fancyMode)
	{
		// Clear terminal
		std::cout << "\033[H\033[2J\033[3J";
		// Hide cursor
		std::cout << "\033[?25l";
		std::cout << color(225, 110, 144) << "______________________ .______________________  " << color() << std::endl;
		std::cout << color(225, 110, 144) << "\\_   _____/\\__    ___/ |   \\______   \\_   ___ \\ " << color() << std::endl;
		std::cout << color(225, 110, 144) << " |    __)    |    |    |   ||       _/    \\  \\/ " << color() << std::endl;
		std::cout << color(225, 110, 144) << " |     \\     |    |    |   ||    |   \\     \\____" << color() << std::endl;
		std::cout << color(225, 110, 144) << " \\___  /     |____|____|___||____|_  /\\______  /" << color() << std::endl;
		std::cout << color(225, 110, 144) << "     \\/          /_____/           \\/        \\/ " << color() << std::endl;

		// Display channel list
		// Put cursor topright (col 50)
		std::cout << "\033[1;50H" << color(135, 109, 190) << "Channels :" << color() << std::endl;
		for (std::map<std::string, std::string>::iterator it = _channels->begin(); it != _channels->end(); ++it)
		{
			if (std::distance(_channels->begin(), it) >= 4)
			{
				std::cout << "\033[6;50H" << color(244, 202, 105) << std::distance(it, _channels->end()) << " more" << color() << std::endl;
				break;
			}
			std::cout << "\033[" << std::distance(_channels->begin(), it) + 2 << ";50H" << trunc((*it).first, 15) << std::endl;
		}
		// Display user list
		// Put cursor topright (col 66)
		std::cout << "\033[1;66H" << color(135, 109, 190) << "Users :" << color() << std::endl;
		for (std::map<std::string, std::string>::iterator it = _users->begin(); it != _users->end(); ++it)
		{
			if (std::distance(_users->begin(), it) >= 4)
			{
				std::cout << "\033[6;66H" << color(244, 202, 105) << std::distance(it, _users->end()) << " more" << color() << std::endl;
				break;
			}
			std::cout << "\033[" << std::distance(_users->begin(), it) + 2 << ";66H" << trunc((*it).first, 15) << std::endl;
		}

		// Display message list
		// Put cursor to correct line
		std::cout << "\033[6;1H" << std::endl;
		for (std::vector<std::string>::iterator it = _messages.begin(); it != _messages.end(); ++it)
		{
			std::cout << *it << std::endl;
		}
	}
}

void Display::addMessage(std::string msg)
{
	if (_fancyMode)
	{
		if (_messages.size() == 20)
		{
			_messages.erase(_messages.begin());
		}
		_messages.push_back(msg);
		this->update();
	}
	else
	{
		std::cout << msg << std::endl;
	}
}

Display::Display(std::map<std::string, std::string> *pChanPtr, std::map<std::string, std::string> *pUsrPtr)
{
	this->_channels = pChanPtr;
	this->_users = pUsrPtr;
	_fancyMode = 1;
}

Display::Display()
{
	_fancyMode = 0;
}
Display::~Display()
{
	// Display cursor
	std::cout << "\033[?25h" << std::flush;
}

int main()
{
	std::map<std::string, std::string> _users;
	std::map<std::string, std::string> _channels;
	Display disp(&_channels, &_users);
	// Display disp;
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