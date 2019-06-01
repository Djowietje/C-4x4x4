#pragma once

#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include "Drawable.hpp"
#endif // !DRAWABLE_HPP
#pragma once

struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct Vertex
{
	float x;
	float y;
	float z;
	Color c;
};

struct Index {
	unsigned short from;
	unsigned short to;
};
