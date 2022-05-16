#pragma once

#include <string>
#include "GraphOptions.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "IncidenceMatrix.h"

class Graph  
{
private:
	int _size = 0;
	bool _isGraphic = false;
	int* _tabSeries = nullptr;
	AdjacencyList* adjacencyList = nullptr;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	IncidenceMatrix* incidenceMatrix = nullptr;
	
public:
	Graph(std::string input);
	~Graph();
	bool IsGraphicSequence();
	void CreateVisualization(std::string file);
	void Blend(int n);
	void CreateGraph();
};

