#pragma once
#include "Graphics.hpp"
#include <wrl.h>
#include "Drawable.hpp"
#include <vector>

class Box : public Drawable
{
public:
	Box(float, float, float);
	Box() : Box(0.1f, 0.1f, 0.1f) {}
	~Box();
	void update();

private:
	float width = 0;
	float height = 0;
	float depth = 0;
};