#pragma once

#include "GraphRepresentation.h"

class AdjacencyList : public GraphRepresentation {
public:
	explicit AdjacencyList(int vertices);
	void setEdge(int vertex1, int vertex2, int weight) override;
	void removeEdge(int vertex1, int vertex2) override;
	bool edgeExists(int vertex1, int vertex2) override;
	std::vector<int> getNeighbors(int vertex);
	void print() override;
};
