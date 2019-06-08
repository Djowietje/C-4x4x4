#include "App.hpp"

const int amountOfBoxes = 64;

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

				box->getLocation()->x = z;
				box->getLocation()->y = x;
				box->getLocation()->z = y;

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

	gfx->clearBuffer(backGroundColor, backGroundColor, 1.0f);
	
	draw();

	if (winner != 0) {
		std::stringstream ss;
		ss << "Winner Player #" << winner << " !";
		gfx->drawTextOnScreen(ss.str().c_str(), 0, 0);
	}
	
	gfx->swapBackToFrontBuffer();

}

void App::draw() {

	for (auto obj : objectsToDraw) {
		gfx->drawObject(&obj);
	}
	gfx->getComPointer()->pContext->Draw(1u, 0u);
}

bool App::selectColumn(int x, int z)
{
	auto yColumn = playingField[x][z];
	bool succes = false;

	for (size_t i = 0; i < 4; i++)
	{
		if (yColumn[i]->getSelectedByPlayer() == 0 ) {
			yColumn[i]->setSelectedByPlayer(playerTurn);
			changePlayer();
			succes = true;
			break;
		}
	}

	if (succes) checkForWinner();
	return succes;
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

int App::getPlayerTurn()
{
	return playerTurn;
}

void App::changePlayer() 
{
	playerTurn = playerTurn %2 +1;
}

void App::checkForWinner() {
	
	auto winner = checkVertically();
	if (!winner) winner = checkHorizontallyZ();
	if (!winner) winner = checkHorizontallyX();
	

}

bool App::checkVertically() {
	int firstSelection;
	bool solidRow = true;
	bool winnerFound = false;

	for (size_t k = 0; k < 4; k++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (!winnerFound) {
				for (size_t i = 0; i < 4; i++)
				{
					if (i == 0) firstSelection = playingField[k][j][0]->getSelectedByPlayer();
					else solidRow = solidRow && (playingField[k][j][i]->getSelectedByPlayer() == firstSelection);
				}

				if (solidRow) {
					winner = firstSelection;
					winnerFound = true;
				}
			}
		}
	}
	return winnerFound;
}

bool App::checkHorizontallyZ() {
	int firstSelection;
	bool solidRow = true;
	bool winnerFound = false;

	for (size_t k = 0; k < 4; k++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (!winnerFound) {
				for (size_t i = 0; i < 4; i++)
				{
					if (i == 0) firstSelection = playingField[j][0][k]->getSelectedByPlayer();
					else solidRow = solidRow && (playingField[j][i][k]->getSelectedByPlayer() == firstSelection);
				}

				if (solidRow) {
					winner = firstSelection;
					winnerFound = true;
				}
			}
		}
	}
	return winnerFound;
}

bool App::checkHorizontallyX() {
	int firstSelection;
	bool solidRow = true;
	bool winnerFound = false;

	for (size_t k = 0; k < 4; k++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (!winnerFound) {
				for (size_t i = 0; i < 4; i++)
				{
					if (i == 0) firstSelection = playingField[0][j][k]->getSelectedByPlayer();
					else solidRow = solidRow && (playingField[i][j][k]->getSelectedByPlayer() == firstSelection);
				}

				if (solidRow) {
					winner = firstSelection;
					winnerFound = true;
				}
			}
		}
	}
	return winnerFound;
}