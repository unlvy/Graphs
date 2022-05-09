#pragma once

#include "AdjacencyMatrix.h"
#include <string>

class Graph  
{
private:
	int _size = 0;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	void GoInside(int first, int current, bool* visited, int* stack, int _size);
public:
	Graph(std::string input);
	~Graph();
	std::string Hamilton();
};

