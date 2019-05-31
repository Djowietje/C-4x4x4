#pragma once
#include "Graphics.hpp"
#include <wrl.h>
#include "Drawable.hpp"
#include <vector>

class Box : public Drawable
{
public:
	Box(int, int, int);
	Box() : Box(10, 10, 10) {}
	~Box();
	void update();

private:
	int length = 0;
	int width = 0;
	int height = 0;
};