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

	   
	for (auto& layer : playingField) // Iterating over slice [Y,Z]
	{
		for (auto& row : layer) // Iterating over rows [Z]
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

				//Reverse the location order because we want [X][Y][Z] coordinates instead of [Z][Y][X]
				box->getLocation()->x = z;
				box->getLocation()->y = y;
				box->getLocation()->z = x;

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
	for (auto& layer : playingField) // Iterating over slice [Y,Z]
	{
		for (auto& row : layer) // Iterating over rows [Z]
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
	bool succes = false;

	for (size_t i = 0; i < 4; i++)
	{
		if(playingField[x][i][z]->getSelectedByPlayer() == 0 ) {
			playingField[x][i][z]->setSelectedByPlayer(playerTurn);
			changePlayer();
			succes = true;

			std::stringstream ss;
			ss << "Selecting: [X: " << x << " Y: " << i << " Z: " << z << "]";
			SetWindowText(gfx->getParent()->getHandle(), ss.str().c_str());
			checkForWinner();
			break;
		}
	}
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
	
	auto winner = check4inLine();
	if (!winner) winner = checkHorizontalPlaneDiagonal();
	if (!winner) winner = checkVerticalPlaneDiagonal();
	if (!winner) winner = checkDepthPlaneDiagonal();
	if (!winner) winner = check3DDiagonal();
}

bool App::check4inLine() {
	int firstSelectionX;
	int firstSelectionY;
	int firstSelectionZ;
	bool winnerFound = false;

	for (size_t k = 0; k < 4; k++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (!winnerFound) {
				bool solidRowX = true;
				bool solidRowY = true;
				bool solidRowZ = true;
				for (size_t i = 0; i < 4; i++)
				{
					if (i == 0) {
						firstSelectionX = playingField[0][k][j]->getSelectedByPlayer();
						firstSelectionY = playingField[j][0][k]->getSelectedByPlayer();
						firstSelectionZ = playingField[j][k][0]->getSelectedByPlayer();

					} else {
						solidRowX = solidRowX && (playingField[i][k][j]->getSelectedByPlayer() == firstSelectionX);
						solidRowY = solidRowY && (playingField[j][i][k]->getSelectedByPlayer() == firstSelectionY);
						solidRowZ = solidRowZ && (playingField[j][k][i]->getSelectedByPlayer() == firstSelectionZ);
					}
				}

				if (solidRowX && firstSelectionX != 0) {
					winner = firstSelectionX;
					winnerFound = true;
				}
				else if (solidRowY && firstSelectionY != 0) {
					winner = firstSelectionY;
					winnerFound = true;
				}
				else if (solidRowZ && firstSelectionZ != 0) {
					winner = firstSelectionZ;
					winnerFound = true;
				}
			}
		}
	}
	return winnerFound;
}

bool App::checkHorizontalPlaneDiagonal() {
	int bottomLeft;
	int bottomRight;
	bool winnerFound = false;

	
	for (size_t j = 0; j < 4; j++)
	{
		if (!winnerFound) {
			bool upwardsDiagonal = true;
			bool downwardsDiagonal = true;

			for (size_t i = 0; i < 4; i++)
			{
				if (i == 0) {
					bottomLeft = playingField[0][j][0]->getSelectedByPlayer();
					bottomRight = playingField[3][j][0]->getSelectedByPlayer();
					if (bottomLeft == 0 && bottomRight == 0) break;
				}
				else {
					upwardsDiagonal = upwardsDiagonal && (playingField[i][j][i]->getSelectedByPlayer() == bottomLeft);
					downwardsDiagonal = downwardsDiagonal && (playingField[3-i][j][i]->getSelectedByPlayer() == bottomRight);
				}
			}

			if (upwardsDiagonal && bottomLeft != 0) {
				winner = bottomLeft;
				winnerFound = true;
			}

			else if (downwardsDiagonal && bottomRight != 0) {
				winner = bottomRight;
				winnerFound = true;
			}
		}
	}
	
	return winnerFound;
}

bool App::checkVerticalPlaneDiagonal() {
	int bottomLeft;
	int bottomRight;
	bool winnerFound = false;

	for (size_t j = 0; j < 4; j++)
	{
		if (!winnerFound) {
			bool upwardsDiagonal = true;
			bool downwardsDiagonal = true;

			for (size_t i = 0; i < 4; i++)
			{
				if (i == 0) {
					bottomLeft = playingField[0][0][j]->getSelectedByPlayer();
					bottomRight = playingField[3][0][j]->getSelectedByPlayer();
					if (bottomLeft == 0 && bottomRight == 0) break;
				}
				else {
					upwardsDiagonal = upwardsDiagonal && (playingField[i][i][j]->getSelectedByPlayer() == bottomLeft);
					downwardsDiagonal = downwardsDiagonal && (playingField[i][3-i][j]->getSelectedByPlayer() == bottomRight);
				}
			}

			if (upwardsDiagonal && bottomLeft != 0) {
				winner = bottomLeft;
				winnerFound = true;
			}

			else if (downwardsDiagonal && bottomRight != 0) {
				winner = bottomRight;
				winnerFound = true;
			}
		}
	}

	return winnerFound;
}

bool App::checkDepthPlaneDiagonal() {
	int bottomLeft;
	int bottomRight;
	bool winnerFound = false;

	for (size_t j = 0; j < 4; j++)
	{
		if (!winnerFound) {
			bool upwardsDiagonal = true;
			bool downwardsDiagonal = true;

			for (size_t i = 0; i < 4; i++)
			{
				if (i == 0) {
					bottomLeft = playingField[j][0][0]->getSelectedByPlayer();
					bottomRight = playingField[j][0][3]->getSelectedByPlayer();
					if (bottomLeft == 0 && bottomRight == 0) break;
				}
				else {
					upwardsDiagonal = upwardsDiagonal && (playingField[j][i][i]->getSelectedByPlayer() == bottomLeft);
					downwardsDiagonal = downwardsDiagonal && (playingField[j][i][3-i]->getSelectedByPlayer() == bottomRight);
				}
			}

			if (upwardsDiagonal && bottomLeft != 0) {
				winner = bottomLeft;
				winnerFound = true;
			}

			else if (downwardsDiagonal && bottomRight != 0) {
				winner = bottomRight;
				winnerFound = true;
			}
		}
	}

	return winnerFound;
}

bool App::check3DDiagonal() {
	int bottomLeftFront;
	int bottomRightFront;
	int topLeftFront;
	int topRightFront;
	bool winnerFound = false;
	
	bool bottomLeftFrontToRightTopBack = true;
	bool bottomRightFrontToTopLeftBack = true;
	bool topLeftFrontToBottomRightBack = true;
	bool topRightFrontToBottomLeftBack = true;

	for (size_t i = 0; i < 4; i++)
	{
		if (i == 0) {
			bottomLeftFront = playingField[0][0][0]->getSelectedByPlayer();
			bottomRightFront = playingField[3][0][0]->getSelectedByPlayer();
			topLeftFront = playingField[0][3][0]->getSelectedByPlayer();
			topRightFront = playingField[3][3][0]->getSelectedByPlayer();
		}
		else {
			bottomLeftFrontToRightTopBack = bottomLeftFrontToRightTopBack && (playingField[i][i][i]->getSelectedByPlayer() == bottomLeftFront);
			bottomRightFrontToTopLeftBack = bottomRightFrontToTopLeftBack && (playingField[3 - i][i][i]->getSelectedByPlayer() == bottomRightFront);
			topLeftFrontToBottomRightBack = topLeftFrontToBottomRightBack && (playingField[i][3 - i][i]->getSelectedByPlayer() == topLeftFront);
			topRightFrontToBottomLeftBack = topRightFrontToBottomLeftBack && (playingField[3 - i][3 - i][i]->getSelectedByPlayer() == topRightFront);
		}
	}

	if (bottomLeftFrontToRightTopBack && bottomLeftFront != 0) {
		winner = bottomLeftFront;
		winnerFound = true;
	} else if (bottomRightFrontToTopLeftBack && bottomRightFront != 0) {
		winner = bottomRightFront;
		winnerFound = true;
	} else if (topLeftFrontToBottomRightBack && topLeftFront != 0) {
		winner = topLeftFront;
		winnerFound = true;
	} else if (topRightFrontToBottomLeftBack && topRightFront != 0) {
		winner = topRightFront;
		winnerFound = true;
	}


	return winnerFound;
}