#include "App.hpp"

const int amountOfBoxes = 64;
int playerTurn = 1;

App::App() {
	window = new Window(800, 600, "C++ 4x4x4", this);
	objectsToDraw = {};
	gfx = window->getGfxPtr();

}

int App::setup() {
	float width = 1.0f;
	float height = 1.0f;
	float depth = 1.0f;

	float x = -1.0f;
	float y = 0.0f;
	float z = 0.0f;

	for (auto& layer : playingField) // Iterating over layers (Z)
	{
		for (auto& row : layer) // Iterating over rows
		{
			for (auto& box : row) {
				box = new Box(width, height, depth);

				if ( (x += 1) < 4) {
				}
				else if ( (y += 1) < 4) {
					x = 0.0f;
				}
				else if ( (z += 1) < 4) {
					x = 0.0f;
					y = 0.0f;
				}

				box->getLocation()->x = x;
				box->getLocation()->y = y;
				box->getLocation()->z = z;

				DrawableWithSize obj = { box, sizeof(Box) };
				objectsToDraw.push_back(obj);
			}
		}
	}

	while (true) {
		if (const auto exitCode = processMessages()) return *exitCode;
		update();
	}
}

void App::update() {
	backGroundColor = sin(counter) /30.0f;
	counter += 0.1f;

	//Update all boxes (checking state)
	for (auto& layer : playingField) // Iterating over layers (Z)
	{
		for (auto& row : layer) // Iterating over rows
		{
			for (auto& box : row) { 
				box->update();
			}
		}
	}
	

	draw();
}

void App::draw() {
	gfx->clearBuffer(backGroundColor, backGroundColor, 1.0f);

	//Draw some text
	//https://github.com/Microsoft/DirectXTK/wiki/Drawing-text
	//gfx->m_spriteBatch->Begin();
	//const wchar_t* text = L"Hello World";

	//DirectX::XMVECTOR pos = { 0.0f,0.0f };
	//DirectX::XMVECTOR col = { 0.0f,0.0f,0.0f,0.0f };

	//gfx->m_font->DrawString(gfx->m_spriteBatch.get(), text, pos, col, 0.f, pos);
	//gfx->m_spriteBatch->End();

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