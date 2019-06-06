#include "KeyHandler.hpp"
#include "Window.hpp"
#include "App.hpp"


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
	case 'W':
		SetWindowText(hWnd, getPositionString().str().c_str());
		pGfx->getCamPointer()->moveForward();
		break;
	case 'S':
		SetWindowText(hWnd, getPositionString().str().c_str());
		pGfx->getCamPointer()->moveBackward();
		break;
	case 'A':
		SetWindowText(hWnd, getPositionString().str().c_str());
		pGfx->getCamPointer()->strafeLeft();
		break;
	case 'D':
		SetWindowText(hWnd, getPositionString().str().c_str());
		pGfx->getCamPointer()->strafeRight();
		break;
	case '1':
		pGfx->getParent()->getParent()->playingField[0][0][0]->setSelectedByPlayer(1);
		break;
	case '2':
		SetWindowText(hWnd, "2 Pressed");
		pGfx->getParent()->getParent()->playingField[0][0][1]->setSelectedByPlayer(2);
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

