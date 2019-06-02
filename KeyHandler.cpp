#include "KeyHandler.hpp"


KeyHandler::KeyHandler(Graphics* pGfx)
	:
	pGfx(pGfx)
{
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

