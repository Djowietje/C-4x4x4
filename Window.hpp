#ifndef MAIN_HPP
#define MAIN_HPP
#include "Main.hpp"
#endif

class Window
{
public:
	Window(int, int, const char* name);
	~Window();
	const char* name;

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
		//static constexpr const char* wndClassName = "Main Window";
		//static WindowClass wndClass;
		HINSTANCE hInst;
		const char* name;
	};

	int width;
	int height;
	HWND hWnd;
};
