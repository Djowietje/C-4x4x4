#ifndef MAIN_HPP
#define MAIN_HPP
#include "Main.hpp"
#endif

#ifndef KEYHANDLER_HPP
#define KEYHANDLER_HPP
#include "KeyHandler.hpp"
#endif

#ifndef MOUSEHANDLER_HPP
#define MOUSEHANDLER_HPP
#include "MouseHandler.hpp"
#endif

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();
	static LRESULT CALLBACK handleMessage(HWND, UINT, WPARAM, LPARAM);
private:

};