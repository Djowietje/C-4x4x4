#include "Box.hpp"

Box::Box(float width, float height, float depth)
	: 
	width(width),
	height(height),
	depth(depth)
{
	vertices = {
		{-width / 2,  height / 2, depth / 2}, //TOP LEFT BACK->
		{ width / 2,  height / 2, depth / 2}, //TOP RIGHT BACK ->
		{ width / 2, -height / 2, depth / 2}, //BOTTOM RIGHT BACK ->
		{-width / 2, -height / 2, depth / 2}, //BOTTOM LEFT BACK ->
		
		{-width / 2,  height / 2, -depth / 2}, //TOP LEFT FRONT->
		{ width / 2,  height / 2, -depth / 2}, //TOP RIGHT FRONT ->
		{ width / 2, -height / 2, -depth / 2}, //BOTTOM RIGHT FRONT ->
		{-width / 2, -height / 2, -depth / 2}, //BOTTOM LEFT FRONT ->
	};

	indices = {
		//Back
		0 , 1,
		1 , 2,
		2 , 3,
		3 , 0,

		//Front
		4 , 5,
		5 , 6,
		6 , 7,
		7 , 4,

		//Left
		4 , 0,
		7 , 3,

		//Right
		5 , 1,
		6 , 2,
	};

	indicesTriangles = {
		0,1,5 , 0,5,4, //Top
		4,5,7 , 5,6,7, //Front
		0,7,3 , 0,4,7, //Left
		1,0,3 , 2,1,3, //Back
		5,1,6 , 6,1,2, //Right
		6,3,7 , 6,2,3  //Bottom
	};
}

Box::~Box()
{
}

void Box::update()
{
	if (selectedByPlayer == 1 && !updated) {
		setDrawMode(1);
		getColor()->r = 255;
		getColor()->a = 255;
		updated = true;
	}
	else if (selectedByPlayer == 2 && !updated) {
		setDrawMode(2);
		getColor()->g = 255;
		getColor()->a = 255;
		updated = true;
	}
}

void Box::setSelectedByPlayer(int _selectedByPlayer)
{
	selectedByPlayer = _selectedByPlayer;
}
