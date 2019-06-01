#pragma once

#include <Windows.h>

#include "Window.hpp"
#include "KeyHandler.hpp"
#include "MouseHandler.hpp"

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();
	static LRESULT CALLBACK handleMessage(HWND, UINT, WPARAM, LPARAM);
private:
	static void setup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};