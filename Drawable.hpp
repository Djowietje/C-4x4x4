#pragma once

#ifndef VERTEX_HPP
#define VERTEX_HPP
#include "Vertex.hpp"
#endif // !VERTEX_H

class Drawable
{
public:
	virtual Vertex* getVertices();
	virtual int getVertexCount();

	virtual void setVertices(const Vertex[]);
};