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
	
public:
	Graph();
	Graph(std::string input);
	~Graph();
	bool IsGraphicSequence();
	void CreateVisualization(std::string file);
	void Blend(int n);
	void CreateGraph();
	void SetSize(int n) { this->_size = n;}
	void SetGraphic(bool n){ this->_isGraphic = n;}
	void SetSeries(std::vector<int> n){
		int *newTab = new int[n.size()];
		for(int i = 0; i<n.size(); i++)
		{
			newTab[i] = n[i];
		}
		delete [] _tabSeries;
        _tabSeries = new int[n.size()];
        this->_tabSeries = newTab;
	}

};

