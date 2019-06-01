#pragma once
#include <vector>

#ifndef VERTEX_HPP
#define VERTEX_HPP
#include "Vertex.hpp"
#endif // !VERTEX_H

class Drawable
{
public:
	std::vector<Vertex> vertices = {};
	std::vector<Index> indices = {};
	float rotationZ = 1.0f;
	float scale = 1.0f;
	Vertex location = { 0 };

	std::vector<Vertex>* getVertices() { return &vertices; };
	std::vector<Index>* getIndices() { return &indices; };
	float getRotationZ() { return rotationZ; }
	float getScale() { return scale; }
	Vertex* getLocation() { return &location; }

	void setVertices(std::vector<Vertex> _vertices) { vertices = _vertices; };

};