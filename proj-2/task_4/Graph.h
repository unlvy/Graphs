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

	// funkcja sprawdzająca czy krawedz miedzy wierzcholkami u, v jest mostem (po zniszczeniu mostu graf przestalby byc spojny)	
	bool isBridge(int u, int v);
	
	// zwraca liczbe niezniszczonych jeszcze krawedzi w grafie
	int edgeCount();
	
	// wyznaczenie sciezki Eulera
	void findEulerianCircuit(int edgeCounter = 0, int start = 0);

};

// funkcja globalna tworząca ciąg wejściowy do grafu wierzcholkow eulerowskich
std::string eulerianVertices(int n);
bool is_number(const std::string& s);