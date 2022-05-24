#pragma once

#include "GraphRepresentation.h"

class AdjacencyMatrix : public GraphRepresentation
{
public:
	explicit AdjacencyMatrix(int vertices);
	void setEdge(int vertex1, int vertex2, int weight) override;
	void removeEdge(int vertex1, int vertex2) override;
	bool edgeExists(int vertex1, int vertex2) override;
	int getEdgeWeight(int vertex1, int vertex2);
	void print() override;
};
