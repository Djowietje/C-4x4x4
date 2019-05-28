#ifndef MAIN_HPP
#define MAIN_HPP
#include "Main.hpp"
#endif

#include "Graphics.hpp"
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
};
