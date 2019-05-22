#ifndef MAIN_HPP
#define MAIN_HPP
#include "Main.hpp"
#endif

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();
	static LRESULT CALLBACK handleMessage(HWND, UINT, WPARAM, LPARAM);
private:

};