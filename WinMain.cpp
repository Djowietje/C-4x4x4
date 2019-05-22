#ifndef MAIN_HPP
#define MAIN_HPP
#include "Main.hpp"
#endif

int CALLBACK wWinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{

	Window* mainWindow = new Window(800, 600, "WindowName");
	
	//main loop
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1) return -1;
	else return (int) msg.wParam;

}