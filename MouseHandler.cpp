#include "MouseHandler.hpp"


MouseHandler::MouseHandler(Graphics* pGfx)
	:
	pGfx(pGfx)
{
	
}

MouseHandler::~MouseHandler() {

}

void MouseHandler::onLeftClickDown(HWND hWnd) {
	SetWindowText(hWnd, "Clicked.");
}

void MouseHandler::onMouseMove(HWND hWnd, LPARAM lParam, WPARAM wParam) {
	auto newMouseX = GET_X_LPARAM(lParam);
	auto newMouseY = GET_Y_LPARAM(lParam);

	int directionX = mouseX - newMouseX;
	int directionY = mouseY- newMouseY;

	if (wParam == MK_LBUTTON) {
		pGfx->getCamPointer()->mouseMoved(directionX, directionY);
	}
	mouseX = newMouseX;
	mouseY = newMouseY;
}