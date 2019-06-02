#include "Box.hpp"

Box::Box(float width, float height, float depth)
	: 
	width(width),
	height(height),
	depth(depth)
{
	Color red = { 255, 0, 0, 255 };
	Color green = { 0, 255, 0, 255};

	vertices = {
		{-width / 2,  height / 2, depth / 2, red}, //TOP LEFT BACK->
		{ width / 2,  height / 2, depth / 2, red}, //TOP RIGHT BACK ->
		{ width / 2, -height / 2, depth / 2, red}, //BOTTOM RIGHT BACK ->
		{-width / 2, -height / 2, depth / 2, red}, //BOTTOM LEFT BACK ->
		
		{-width / 2,  height / 2, -depth / 2, green}, //TOP LEFT FRONT->
		{ width / 2,  height / 2, -depth / 2, green}, //TOP RIGHT FRONT ->
		{ width / 2, -height / 2, -depth / 2, green}, //BOTTOM RIGHT FRONT ->
		{-width / 2, -height / 2, -depth / 2, green}, //BOTTOM LEFT FRONT ->
	};

	indices = {
		//Front
		{0 , 1},
		{1 , 2},
		{2 , 3},
		{3 , 0},

		//Back
		{4 , 5},
		{5 , 6},
		{6 , 7},
		{7 , 4},

		//Left
		{4 , 0},
		{7 , 3},

		//Right
		{5 , 1},
		{6 , 2},
	};
}

Box::~Box()
{
}

void Box::update()
{
}
