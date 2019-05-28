#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP
#include "MessageHandler.hpp"
#endif // !MESSAGEHANDLER_HPP

KeyHandler* keyHandlerPtr = new KeyHandler();
MouseHandler* mouseHandlerPtr = new MouseHandler();

MessageHandler::MessageHandler()
{
}

MessageHandler::~MessageHandler()
{
}

LRESULT CALLBACK MessageHandler::handleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(2);
		break;
	case WM_KEYDOWN:
		keyHandlerPtr->onKeyDown(wParam, hWnd);
		break;
	case WM_LBUTTONDOWN:
		mouseHandlerPtr->onLeftClickDown(hWnd);
		break;
	case WM_MOUSEMOVE:
		mouseHandlerPtr->onMouseMove(hWnd, lParam);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}