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
};