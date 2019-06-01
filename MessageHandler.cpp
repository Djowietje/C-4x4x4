#include "MessageHandler.hpp"

MessageHandler::MessageHandler()
{
}

MessageHandler::~MessageHandler()
{
}

LRESULT CALLBACK MessageHandler::handleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(2);
		break;
	case WM_KEYDOWN:
		window->getKeyhandler()->onKeyDown(wParam, hWnd);
		break;
	case WM_LBUTTONDOWN:
		window->getMouseHandler()->onLeftClickDown(hWnd);
		break;
	case WM_MOUSEMOVE:
		window->getMouseHandler()->onMouseMove(hWnd, lParam);
		break;
	}
	

	return DefWindowProc(hWnd, msg, wParam, lParam);
}