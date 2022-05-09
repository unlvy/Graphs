#pragma once
#include "GraphOptions.h"

class AdjacencyMatrix : public GraphOptions
{
public:
	AdjacencyMatrix(int n);
	~AdjacencyMatrix();
	void setEdge(int n1, int n2);
	int edgeExists(int n1, int n2);
	void print();
};
