#include "Window.hpp"
#include "App.hpp"

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
Window::Window(int width, int height, const char* name, App* parent)
	:
	width(width),
	height(height),
	name(name),
	parent(parent)
{
	WindowClass* wndClassPtr = new WindowClass(name);

	

	hWnd = CreateWindowEx(
		0, name,
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, width, height,
		nullptr, nullptr, wndClassPtr->GetInstance(), this
	);

	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	ShowWindow(hWnd, SW_SHOW);
	
	//Create a D3D11 Graphics object and pass it to handlers.
	pGfx = new Graphics(hWnd, width, height, this);
	pKeyHandler = new KeyHandler(pGfx);
	pMouseHandler = new MouseHandler(pGfx);
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

App* Window::getParent()
{
	return parent;
}

Window::~Window()
{
	DestroyWindow(hWnd);
}