#pragma once

#include <Windows.h>
#include <iostream>
#include <sstream>
#include <windowsx.h>
#include <optional>

#include "Graphics.hpp"
#include "MessageHandler.hpp"
#include "KeyHandler.hpp"
#include "MouseHandler.hpp"

#include <memory>

class Window
{
public:
	Window(int, int, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	const char* name;
	HWND getHandle();
	Graphics& getGfxPtr();
	KeyHandler* getKeyhandler();
	MouseHandler* getMouseHandler();
private:
	class WindowClass
	{
	public:
		const char* GetName() noexcept;
		HINSTANCE GetInstance() noexcept;
		WindowClass(const char* name) noexcept;
		~WindowClass();

	private:
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		HINSTANCE hInst;
		const char* name;

	};

	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
	MouseHandler* pMouseHandler;
	KeyHandler* pKeyHandler;
};
