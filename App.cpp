#include "App.hpp"

App::App() {
	window = new Window(800, 600, "New APP Layout");
}

int App::setup() {
	while (true) {
		if (const auto exitCode = processMessages()) return *exitCode;
		update();
	}
}

void App::update() {
	
	window->getGfxPtr().swapBackToFrontBuffer();
}

std::optional<int> App::processMessages() {
	MSG msg;
	BOOL gResult;
	while ((gResult = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) > 0) {
		if (msg.message == WM_QUIT) return static_cast<int>(msg.wParam);

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return {};

}