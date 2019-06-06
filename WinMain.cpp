#include "Main.hpp"
#include "App.hpp"

int CALLBACK wWinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	return App{}.setup();
}