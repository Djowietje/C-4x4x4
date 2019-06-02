#pragma once

#include <Windows.h>
#include <iostream>
#include <sstream>
#include "Graphics.hpp"

class KeyHandler
{
public:
	KeyHandler(Graphics*);
	~KeyHandler();
	void onKeyDown(WPARAM, HWND);
private:
	Graphics* pGfx;
};
