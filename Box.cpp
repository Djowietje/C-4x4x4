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
		{0.0f,height,depth, red}, //TOP LEFT BACK->
		{width,height,depth, red}, //TOP RIGHT BACK ->
		{width,0.0f,depth, red}, //BOTTOM RIGHT BACK ->
		{0.0f,0.0f,depth, red}, //BOTTOM LEFT BACK ->
		
		{0.0f,height,0.0f, green}, //TOP LEFT FRONT->
		{width,height,0.0f, green}, //TOP RIGHT FRONT ->
		{width,0.0f,0.0f, green}, //BOTTOM RIGHT FRONT ->
		{0.0f,0.0f,0.0f, green}, //BOTTOM LEFT FRONT ->
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
