#include "App.hpp"

const int amountOfBoxes = 2;

App::App() {
	window = new Window(800, 600, "C++ 4x4x4");
	pContext = window->getGfxPtr().getContextPointer();
	pDevice = window->getGfxPtr().getDevicePointer();
	objectsToDraw = {};
}

int App::setup() {
	
	for (size_t i = 0; i < amountOfBoxes; i++){
		Box* b = new Box(0.1f, 0.1f, 0.1f);
		b->getLocation()->x = 0.1f * i;
		b->getLocation()->y = 0.1f * i;
		DrawableWithSize obj = { b, sizeof(Box) };
		objectsToDraw.push_back(obj);
	}

	while (true) {
		if (const auto exitCode = processMessages()) return *exitCode;
		update();
	}
}

void App::update() {
	backGroundColor = sin(counter) /2.0f + 0.5f;
	counter += 0.1f;
	bool runOnce = true;

	//Update all Drawables;
	for (size_t i = 0; i < objectsToDraw.size(); i++) {
		DrawableWithSize d = objectsToDraw.data()[i];
		d.obj->getLocation()->x += 0.01f;
	}
	draw();
}

void App::draw() {
	window->getGfxPtr().clearBuffer(backGroundColor, backGroundColor, 1.0f);
	for (auto obj : objectsToDraw) {
		window->getGfxPtr().drawObject(&obj);
	}
	pContext->Draw(1u, 0u);
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