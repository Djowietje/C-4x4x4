#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "Window.hpp"
#endif // !WINDOW_HPP

Window::WindowClass::WindowClass(const char* name) noexcept
	:
	hInst(GetModuleHandle(nullptr)),
	name(name)
{

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = MessageHandler::handleMessage;
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

	pKeyHandler = new KeyHandler();
	pMouseHandler = new MouseHandler();

	hWnd = CreateWindowEx(
		0, name,
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, width, height,
		nullptr, nullptr, wndClassPtr->GetInstance(), this
	);

	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	ShowWindow(hWnd, SW_SHOW);
	
	//Create a D3D11 Graphics object
	pGfx = new Graphics(hWnd, width, height);
}

HWND Window::getHandle() {
	return hWnd;
}

Graphics* Window::getGfxPtr()
{
	return pGfx;
}

KeyHandler* Window::getKeyhandler()
{
	return pKeyHandler;
}

MouseHandler* Window::getMouseHandler()
{
	return pMouseHandler;
}

Window::~Window()
{
	DestroyWindow(hWnd);
}