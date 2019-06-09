#pragma once
#include <chrono>
#include <vector>
#include <Windows.h>
#include <windowsx.h>
#include <optional>
#include "Window.hpp"
#include "Main.hpp"
#include "DrawableWithSize.hpp"

class App
{
public:
	App();
	int setup();
	std::optional<int> processMessages();
	Box* playingField[4][4][4];
	int getPlayerTurn();
	void changePlayer();
	bool selectColumn(int x, int y);

private:
	void update();
	void draw();
	void checkForWinner();
	Window* window;
	Graphics* gfx;
	std::vector<DrawableWithSize> objectsToDraw;

	float backGroundColor = 0.0f;
	float counter = 0.0f;
	int playerTurn = 1;
	int winner = 0;
	bool check4inLine();
	bool checkHorizontalPlaneDiagonal();
	bool checkVerticalPlaneDiagonal();
	bool checkDepthPlaneDiagonal();
	bool check3DDiagonal();
};