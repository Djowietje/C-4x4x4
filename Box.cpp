#include "Box.hpp"

Vertex* vertices;
int amountOfVertices;

Box::Box(int length, int width, int height)
	: 
	length(length),
	width(width),
	height(height)
{
	Vertex vert[] = {
		{ 0.0f,0.5f, 0.0f },
		{ 0.5f,-0.5f, 0.0f },
		{ -0.5f,-0.5f, 0.0f },
	};

	vertices = vert;
	amountOfVertices = sizeof(vert) / sizeof(Vertex);
}

Box::~Box()
{
}

void Box::update()
{
}

Vertex* Drawable::getVertices()
{
	return vertices;
}

int Drawable::getVertexCount() {
	return amountOfVertices;
}

void Drawable::setVertices(const Vertex _vertices[])
{
	
}
