#ifndef MAIN_HPP
#define MAIN_HPP
#include "Main.hpp"
#endif

class MouseHandler
{
public:
	MouseHandler();
	~MouseHandler();
	void onLeftClickDown(HWND);
	void onMouseMove(HWND, LPARAM);
};