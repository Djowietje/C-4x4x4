#ifndef MOUSEHANDLER_HPP
#define MOUSEHANDLER_HPP
#include "MouseHandler.hpp"
#endif // !MOUSEHANDLER_HPP

MouseHandler::MouseHandler() {

}

MouseHandler::~MouseHandler() {

}

void MouseHandler::onLeftClickDown(HWND hWnd) {
	SetWindowText(hWnd, "Clicked.");
}

void MouseHandler::onMouseMove(HWND hWnd, LPARAM lParam) {
	std::stringstream ss;
	ss << "Mouse Moved (X: " << GET_X_LPARAM(lParam) << ", Y: " << GET_Y_LPARAM(lParam) << ")";
	SetWindowText(hWnd, ss.str().c_str());
}