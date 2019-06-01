#pragma once

#include <Windows.h>
#include <iostream>
#include <sstream>

class KeyHandler
{
public:
	KeyHandler();
	~KeyHandler();
	void onKeyDown(WPARAM, HWND);
};
