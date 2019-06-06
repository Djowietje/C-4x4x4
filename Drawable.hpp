#pragma once

#include <vector>
#include "Vertex.hpp"

class Drawable
{
public:
	std::vector<Vertex> vertices = {};
	std::vector<unsigned short> indices = {};
	std::vector<unsigned short> indicesTriangles = {};

	int drawMode = 0;
	float scale = 1.0f;
	Color blockColor = { 0 };
	Vertex location = { 0 };
	Vertex rotation = { 0 };

	std::vector<Vertex>* getVertices() { return &vertices; };
	std::vector<unsigned short>* getIndices() { return &indices; };
	std::vector<unsigned short>* getIndicesTriangles() { return &indicesTriangles; };


	int getDrawMode() { return drawMode;  };
	void setDrawMode(int _drawmode) { drawMode = _drawmode; };
	float getScale() { return scale; }
	Vertex* getRotation() { return &rotation; }
	Vertex* getLocation() { return &location; }
	Color* getColor();

	void setVertices(std::vector<Vertex> _vertices) { vertices = _vertices; };

};