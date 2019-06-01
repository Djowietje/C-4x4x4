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
	std::vector<DrawableWithSize> objectsToDraw;

	ID3D11DeviceContext* pContext;
	ID3D11Device* pDevice;
	float backGroundColor = 0.0f;
	float counter = 0.0f;
};