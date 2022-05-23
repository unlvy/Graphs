#pragma once

#include <vector>

class GraphRepresentation
{
public:
	virtual void setEdge(int vertex1, int vertex2, int weight) = 0;
	virtual void removeEdge(int vertex1, int vertex2) = 0;
	virtual bool edgeExists(int vertex1, int vertex2) = 0;
	virtual void print() = 0;

protected:
	int _vertices = 0;
	int _edges = 0;
	std::vector<std::vector<int>> matrix;
};