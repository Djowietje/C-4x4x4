#ifndef KEYHANDLER_HPP
#define KEYHANDLER_HPP
#include "KeyHandler.hpp"
#endif

KeyHandler::KeyHandler()
{
	std::cout << "INIT KeyHandler";
}

KeyHandler::~KeyHandler()
{
	std::cout << "Deconstrucing KeyHandler";
}

void KeyHandler::onKeyDown(WPARAM input, HWND hWnd) {
	switch (input)
	{
	case 'A':
		SetWindowText(hWnd, "Change Title as example.");
	default:
		break;
	}
}

