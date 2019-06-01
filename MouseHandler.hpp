#pragma once

#include <Windows.h>
#include <sstream>
#include <windowsx.h>

class MouseHandler
{
public:
	MouseHandler();
	~MouseHandler();
	void onLeftClickDown(HWND);
	void onMouseMove(HWND, LPARAM);
	int getMouseX() { return mouseX; }
	int getMouseY() { return mouseY; }
private:
	int mouseX;
	int mouseY;
};