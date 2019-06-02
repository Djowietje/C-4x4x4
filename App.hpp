#pragma once

#include "Main.hpp"
#include "DrawableWithSize.hpp"
#include <chrono>
#include <vector>

class App
{
public:
	App();
	int setup();
	std::optional<int> processMessages();
private:
	void update();
	void draw();

	Window* window;
	Graphics* gfx;
	std::vector<DrawableWithSize> objectsToDraw;

	float backGroundColor = 0.0f;
	float counter = 0.0f;
};