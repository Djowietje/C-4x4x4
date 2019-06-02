#pragma once

#include <vector>
#include "Vertex.hpp"

class Drawable
{
public:
	std::vector<Vertex> vertices = {};
	std::vector<Index> indices = {};
	float scale = 1.0f;
	Vertex location = { 0 };
	Vertex rotation = { 0 };

	std::vector<Vertex>* getVertices() { return &vertices; };
	std::vector<Index>* getIndices() { return &indices; };
	Vertex* getRotation() { return &rotation; }
	float getScale() { return scale; }
	Vertex* getLocation() { return &location; }

	void setVertices(std::vector<Vertex> _vertices) { vertices = _vertices; };

};