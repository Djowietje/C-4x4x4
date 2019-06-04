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
		break;
	case 'W':
		SetWindowText(hWnd, getPositionString().str().c_str());
		pGfx->getCamPointer()->moveForward();
		break;
	case 'S':
		SetWindowText(hWnd, getPositionString().str().c_str());
		pGfx->getCamPointer()->moveBackward();
		break;
	default:
		break;
	}
}

std::stringstream KeyHandler::getPositionString()
{
	auto pos = pGfx->getCamPointer();
	std::stringstream ss;
	ss << "newPosition [" << pos->getPosX() << "," << pos->getPosY() << "," << pos->getPosZ() << "]";
	return ss;
}

