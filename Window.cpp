#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "Window.hpp"
#endif // !WINDOW_HPP

//Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass(const char* name) noexcept
	:
	hInst(GetModuleHandle(nullptr)),
	name(name)
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = messageHandlerPtr->handleMessage;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = name;
	
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(name, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
	return name;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return hInst;
}


// Window Stuff
Window::Window(int width, int height, const char* name)
	:
	width(width),
	height(height),
	name(name)
{
	WindowClass* wndClassPtr = new WindowClass(name);

	// calculate window size based on desired client region size
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	
	hWnd = CreateWindowEx(
		0, name,
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 800, 600,
		nullptr, nullptr, wndClassPtr->GetInstance(), nullptr
	);

	ShowWindow(hWnd, SW_SHOW);
	
}

Window::~Window()
{
	DestroyWindow(hWnd);
}