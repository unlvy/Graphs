#include "Graph.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

Graph::Graph()
{
	int _size = 0;
	bool _isGraphic = false;
	int* _tabSeries = nullptr;
}

Graph::Graph(std::string input)
{
	istringstream iss(input);
	vector<string> results((istream_iterator<string>(iss)), istream_iterator<std::string>());
	_size = results.size();
	_tabSeries = new int[_size];
	for(int i = 0; i < _size; ++i)
	{
		_tabSeries[i] = atoi(results[i].c_str());
	}
}

bool Graph::IsGraphicSequence()
{

	int* tab = new int[_size];
	bool graphicControl = true;

	std::cout<<_size<<std::endl;
	for(int i = 0; i<_size; i++)
	{
		std::cout<<_tabSeries[i]<<std::endl;
	}

	for(int i = 0; i < _size; ++i)
		tab[i] = _tabSeries[i];
	
	sort(tab, tab + _size, [](int i, int j) {return i > j;});
	
	while(true)
	{
		graphicControl = true;
		for(int i = 0; i < _size; ++i)
		{
			if(tab[i] != 0)
			{
				graphicControl = false;
				break;
			}
		}
		
		if(graphicControl)
		{
			delete[] tab;
			return true;
		}
		
		if(tab[0] < 0 || tab[0] >= _size)
		{
			delete[] tab;
			return false;
		}
		
		for(int i = 1; i < _size; ++i)
		{
			if(tab[i] < 0)
			{
				delete[] tab;
				return false;
			}
		}
		
		for(int i = 1; i <= tab[0]; ++i)
			tab[i] = tab[i] - 1;
			
		tab[0] = 0;
		sort(tab, tab + _size, [](int i, int j) {return (i > j);});
	}
}

void Graph::CreateGraph()
{
	srand(time(NULL));
	
	int* tab = new int[_size];
	int node = 0;
	int flag = 0;
	
	adjacencyList = new AdjacencyList(_size);
	adjacencyMatrix = new AdjacencyMatrix(_size);
	incidenceMatrix = new IncidenceMatrix(_size);
	
	for(int i = 0; i < _size; ++i)
		tab[i] = _tabSeries[i];
		
	for(int i = 0; i < _size; ++i)
	{
		flag = 0;
		while(tab[i] > 0)
		{
			node = rand()%_size;
			++flag;
			
			if(flag == _size)
			{
				adjacencyList = new AdjacencyList(_size);
				adjacencyMatrix = new AdjacencyMatrix(_size);
				incidenceMatrix = new IncidenceMatrix(_size);
	
				for(int j = 0; j < _size; ++j)
					tab[j] = _tabSeries[j];
				i = -1;
				break;
			}
			
			if(i != node && !adjacencyMatrix->edgeExists(i, node) && tab[node] > 0)
			{
				adjacencyMatrix->setEdge(i, node);
				adjacencyList->setEdge(i, node);
				incidenceMatrix->setEdge(i, node);
				--tab[i];
				--tab[node];
			}
		}
	}
	
	adjacencyMatrix->print();
	adjacencyList->print();
	incidenceMatrix->print();
	
	delete[] tab;
}

void Graph::CreateVisualization(std::string file)
{
	ofstream plik(file);
	
	plik << "digraph G" << endl << "{" << endl;
	plik << "	layout=\"circo\";" << endl;
	plik << "	node [shape = circle];" << endl;
	
	for(int i = 0; i < _size - 1; ++i)
		plik << "	N" << i << " -> N" << i + 1 << " [arrowhead=none][style=invis]" << endl;
	plik << "	N" << _size - 1 << " -> N0 [arrowhead=none][style=invis]" << endl;
	
	for(int i = 0; i < _size; ++i)
	{
		for(int j = i + 1; j < _size; ++j)
		{
			if(adjacencyMatrix->edgeExists(i, j))
				plik << "	N" << j << " -> N" << i << " [arrowhead=none]" << endl;
		}
	}
	plik << "}";
	
	cout << "Wygenerowano skrypt o nazwie '" << file << "' dla grafu o liczbie wierzcholkow: " << _size << endl;
	
	plik.close();
}

void Graph::Blend(int n)
{
	AdjacencyList* adjacencyListTemp;
	AdjacencyMatrix* adjacencyMatrixTemp;
	IncidenceMatrix* incidenceMatrixTemp;
	int a, b, c, d;
	
	srand(time(NULL));
	
	while(n > 0)
	{
		a = b = c = d = 0;
		adjacencyListTemp = new AdjacencyList(_size);
		adjacencyMatrixTemp = new AdjacencyMatrix(_size);
		incidenceMatrixTemp = new IncidenceMatrix(_size);
		
		while(a == b || a == c || a == d || b == c || b == d || c == d || !adjacencyMatrix->edgeExists(a, b) || !adjacencyMatrix->edgeExists(c, d) || adjacencyMatrix->edgeExists(a, c) || adjacencyMatrix->edgeExists(b, d))
		{
			a = rand()%_size;
			b = rand()%_size;
			c = rand()%_size;
			d = rand()%_size;
		}
		
		for(int i = 0; i < _size; ++i)
		{
			for(int j = i + 1; j < _size; ++j)
			{
				if((i != a || j != b) && (i != c || j != d) && (i != b || j != a) && (i != d || j != c) && adjacencyMatrix->edgeExists(i, j))
				{
					adjacencyMatrixTemp->setEdge(i, j);
					adjacencyListTemp->setEdge(i, j);
					incidenceMatrixTemp->setEdge(i, j);
				}
			}
		}
		
		adjacencyMatrixTemp->setEdge(a, c);
		adjacencyListTemp->setEdge(a, c);
		incidenceMatrixTemp->setEdge(a, c);
		
		adjacencyMatrixTemp->setEdge(b, d);
		adjacencyListTemp->setEdge(b, d);
		incidenceMatrixTemp->setEdge(b, d);
			
		delete adjacencyList;
		delete adjacencyMatrix;
		delete incidenceMatrix;
		
		adjacencyList = adjacencyListTemp;
		adjacencyMatrix = adjacencyMatrixTemp;
		incidenceMatrix = incidenceMatrixTemp;
		
		adjacencyListTemp = nullptr;
		adjacencyMatrixTemp = nullptr;
		incidenceMatrixTemp = nullptr;
		
		--n;
	}
	
	adjacencyMatrix->print();
	adjacencyList->print();
	incidenceMatrix->print();
}

Graph::~Graph()
{
	delete adjacencyList;
	delete adjacencyMatrix;
	delete incidenceMatrix;
	delete[] _tabSeries;
}
