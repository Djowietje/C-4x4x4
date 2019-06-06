#pragma once
#include "Graphics.hpp"
#include <wrl.h>
#include "Drawable.hpp"
#include <vector>

class Box : public Drawable
{
public:
	Box(float, float, float);
	Box() : Box(1.0f, 1.0f, 1.0f) {}
	~Box();
	void update();
	void setSelectedByPlayer(int);
private:
	float width = 1.0f;
	float height = 1.0f;
	float depth = 1.0f;
	int selectedByPlayer = 0;
	bool updated = false;
};