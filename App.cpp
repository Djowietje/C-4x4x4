#include "App.hpp"

const int amountOfBoxes = 8;

App::App() {
	window = new Window(800, 600, "C++ 4x4x4");
	objectsToDraw = {};
	gfx = window->getGfxPtr();

}

int App::setup() {
	float width = 1.0f;
	float height = 1.0f;
	float depth = 1.0f;
	
	for (size_t i = 0; i < amountOfBoxes; i++){
		Box* b = new Box(width, height, depth);
		b->getLocation()->x = width * (i%4);
		b->getLocation()->y = height * (((i - i%4)/4)%4);
		b->getLocation()->z = depth * ((i - i % 16) / 16);
		DrawableWithSize obj = { b, sizeof(Box) };
		objectsToDraw.push_back(obj);
	}

	while (true) {
		if (const auto exitCode = processMessages()) return *exitCode;
		update();
	}
}

void App::update() {
	backGroundColor = sin(counter) /30.0f;
	counter += 0.1f;

	//Update all Drawables;
	for (size_t i = 0; i < objectsToDraw.size(); i++) {
		DrawableWithSize d = objectsToDraw.data()[i];
		//d.obj->getLocation()->x += backGroundColor;
		//d.obj->getRotation()->x += 0.01f;
		d.obj->getRotation()->y -= 0.01f;

	}
	draw();
}

void App::draw() {
	gfx->clearBuffer(backGroundColor, backGroundColor, 1.0f);
	for (auto obj : objectsToDraw) {
		gfx->drawObject(&obj);
	}
	gfx->getComPointer()->pContext->Draw(1u, 0u);
	gfx->swapBackToFrontBuffer();
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