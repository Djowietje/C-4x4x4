#include "KeyHandler.hpp"
#include "Window.hpp"
#include "App.hpp"

App* pApp;

KeyHandler::KeyHandler(Graphics* pGfx)
	:
	pGfx(pGfx)
{
	pApp = pGfx->getParent()->getParent();
}

KeyHandler::~KeyHandler()
{
	std::cout << "Deconstrucing KeyHandler";
}

void KeyHandler::onKeyDown(WPARAM input, HWND hWnd) {
	int playerTurn = pApp->getPlayerTurn();

	std::stringstream ss;
	ss << "Prev Input: [" << prevInput << "]  Input: [" << input << "]";
	SetWindowText(hWnd, ss.str().c_str());

	switch (input)
	{
	case 'W':
		pGfx->getCamPointer()->moveForward();
		break;
	case 'S':
		pGfx->getCamPointer()->moveBackward();
		break;
	case 'A':
		pGfx->getCamPointer()->strafeLeft();
		break;
	case 'D':
		pGfx->getCamPointer()->strafeRight();
		break;
	case '1':
		if (prevInput == '1' || prevInput == '2' || prevInput == '3' || prevInput == '4') {
			pApp->selectColumn(0, (int)prevInput - '0' - 1);
			prevInput = 0;
		} else prevInput = input;
		break;
	case '2':
		if (prevInput == '1' || prevInput == '2' || prevInput == '3' || prevInput == '4') {
			pApp->selectColumn(1, (int)prevInput - '0' - 1);
			prevInput = 0;
		} else prevInput = input;
		break;
	case '3':
		if (prevInput == '1' || prevInput == '2' || prevInput == '3' || prevInput == '4') {
			pApp->selectColumn(2, (int)prevInput - '0' - 1);
			prevInput = 0;
		} else prevInput = input;
		break;
	case '4':
		if (prevInput == '1' || prevInput == '2' || prevInput == '3' || prevInput == '4') {
			pApp->selectColumn(3, (int)prevInput - '0' - 1);
			prevInput = 0;
		} else prevInput = input;
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

