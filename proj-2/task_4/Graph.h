#pragma once

#include <string>
#include <vector>
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

	int** tempGraph;
	int edgeCounter;

public:
	Graph(std::string input);
	~Graph();
	bool IsGraphicSequence();
	void CreateVisualization(std::string file);
	void Blend(int n);
	void CreateGraph();

	// function that checks if the edge between the vertices u, v is a bridge (after destroying the bridge, the graph would cease to be cohesive)
	bool isBridge(int u, int v);
	
	// returns the number of still undamaged edges in the graph
	int edgeCount();
	
	// determination of Euler's path
	void findEulerianCircuit(int edgeCounter = 0, int start = 0);

};

// a global function that creates an input string to a Eulerian vertex graph
std::string eulerianVertices(int n);
bool is_number(const std::string& s);