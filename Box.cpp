#include "Box.hpp"

Box::Box(int length, int width, int height)
	: 
	length(length),
	width(width),
	height(height)
{
	vertices = {

		{0.05f,0.15f,0.1f}, //TOP LEFT BACK->
		{0.15f,0.15f,0.1f}, //TOP RIGHT BACK ->
		
		{0.15f,0.15f,0.1f}, //TOP RIGHT BACK ->
		{0.15f,0.05f,0.1f}, //BOTTOM RIGHT BACK ->

		{0.15f,0.05f,0.1f}, //BOTTOM RIGHT BACK ->
		{0.05f,0.05f,0.1f}, //BOTTOM LEFT BACK ->
		
		{0.05f,0.05f,0.1f}, //BOTTOM LEFT BACK ->
		{0.05f,0.15f,0.1f}, //TOP LEFT BACK ->
		
		{0.05f,0.15f,0.1f}, //TOP LEFT BACK ->
		{0.0f,0.1f,0.0f}, //TOP LEFT FRONT->

		{0.0f,0.1f,0.0f}, //TOP LEFT FRONT->
		{0.1f,0.1f,0.0f}, //TOP RIGHT FRONT ->

		{0.1f,0.1f,0.0f}, //TOP RIGHT FRONT ->
		{0.1f,0.0f,0.0f}, //BOTTOM RIGHT FRONT ->

		{0.1f,0.0f,0.0f}, //BOTTOM RIGHT FRONT ->
		{0.0f,0.0f,0.0f}, //BOTTOM LEFT FRONT ->

		{0.0f,0.0f,0.0f}, //BOTTOM LEFT FRONT ->
		{0.0f,0.1f,0.0f}, //TOP LEFT FRONT ->

	};
}

Box::~Box()
{
}

void Box::update()
{
}
