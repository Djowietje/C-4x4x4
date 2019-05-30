#include "App.hpp"
const int amountOfBoxes = 1;
DrawableWithSize allObjects[amountOfBoxes];

App::App() {
	window = new Window(800, 600, "C++ 4x4x4");
	pContext = window->getGfxPtr().getContextPointer();
	pDevice = window->getGfxPtr().getDevicePointer();
}

int App::setup() {
	//Initialize all object we want to draw.
	//DrawableWithSize* allObjects[amountOfBoxes];
	
	for (size_t i = 0; i < amountOfBoxes; i++)
	{
		DrawableWithSize obj = { new Box, sizeof(Box) };
		allObjects[i] = obj;
		amountOfObjects++;
	}
	//objectsToDraw = allObjects;
	

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
	//for (size_t i = 0; i < amountOfObjects; i++) {
	//	(*objectsToDraw[i]).obj->getVertices()[0].x += 0.001f;
	//}
	
	draw();
}

void App::draw() {
	window->getGfxPtr().clearBuffer(backGroundColor, backGroundColor, 1.0f);
	window->getGfxPtr().drawObject((allObjects[0]));
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