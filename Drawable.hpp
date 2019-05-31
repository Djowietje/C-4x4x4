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

	std::vector<Vertex>* getVertices() { return &vertices; };
	void setVertices(std::vector<Vertex> _vertices) { vertices = _vertices; };
};