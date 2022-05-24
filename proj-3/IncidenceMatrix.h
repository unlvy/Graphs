#pragma once

#include "GraphRepresentation.h"

class IncidenceMatrix : public GraphRepresentation {
public:
	explicit IncidenceMatrix(int vertices);
	void setEdge(int vertex1, int vertex2, int weight) override;
	void removeEdge(int vertex1, int vertex2) override;
	bool edgeExists(int vertex1, int vertex2) override;
	std::tuple<int,int> edgeToVertices(int edgeIndex);
	int verticesToEdge(int vertex1, int vertex2);
	void print() override;
};
