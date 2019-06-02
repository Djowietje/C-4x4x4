#pragma once

#include <Windows.h>
#include <sstream>
#include <windowsx.h>
#include "Graphics.hpp"

class MouseHandler
{
public:
	MouseHandler(Graphics*);
	~MouseHandler();
	void onLeftClickDown(HWND);
	void onMouseMove(HWND, LPARAM, WPARAM);
	int getMouseX() { return mouseX; }
	int getMouseY() { return mouseY; }
private:
	Graphics* pGfx;
	int mouseX = 0;
	int mouseY = 0;
};