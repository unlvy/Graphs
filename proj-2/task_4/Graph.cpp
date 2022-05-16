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

Graph::Graph(std::string input)
{
	srand(time(NULL));
	istringstream iss(input);
	vector<string> results((istream_iterator<string>(iss)), istream_iterator<std::string>());
	_size = results.size();
	_tabSeries = new int[_size];

	for (int i = 0; i < _size; ++i)
	{
		_tabSeries[i] = atoi(results[i].c_str());
	}

	tempGraph = new int*[_size];
	for (int i=0; i<_size; i++)
		tempGraph[i] = new int[_size];
}

bool Graph::IsGraphicSequence()
{
	int* tab = new int[_size];
	bool graphicControl = true;

	for (int i = 0; i < _size; ++i)
		tab[i] = _tabSeries[i];

	sort(tab, tab + _size, [](int i, int j) {return i > j;});

	while (true)
	{
		graphicControl = true;
		for (int i = 0; i < _size; ++i)
		{
			if (tab[i] != 0)
			{
				graphicControl = false;
				break;
			}
		}

		if (graphicControl)
		{
			delete[] tab;
			return true;
		}

		if (tab[0] < 0 || tab[0] >= _size)
		{
			delete[] tab;
			return false;
		}

		for (int i = 1; i < _size; ++i)
		{
			if (tab[i] < 0)
			{
				delete[] tab;
				return false;
			}
		}

		for (int i = 1; i <= tab[0]; ++i)
			tab[i] = tab[i] - 1;

		tab[0] = 0;
		sort(tab, tab + _size, [](int i, int j) {return (i > j);});
	}
}

void Graph::CreateGraph()
{
	int* tab = new int[_size];
	int flag = 0;
	int node = 0;
	int index = 0;
	bool graphicControl = true;

	adjacencyList = new AdjacencyList(_size);
	adjacencyMatrix = new AdjacencyMatrix(_size);
	incidenceMatrix = new IncidenceMatrix(_size);

	for (int i = 0; i < _size; ++i)
		tab[i] = _tabSeries[i];

	while (true)
	{
		graphicControl = true;
		index = 0;
		for (int i = 0; i < _size; ++i)
		{
			if (tab[index] < tab[i])
				index = i;
		}

		while (tab[index] > 0)
		{
			node = rand() % _size;
			if (node != index && tab[node] > 0 && !adjacencyMatrix->edgeExists(index, node))
			{
				flag = 0;
				adjacencyMatrix->setEdge(node, index);
				adjacencyList->setEdge(node, index);
				incidenceMatrix->setEdge(node, index);
				--tab[node];
				--tab[index];
			}
			else
			{
				++flag;
				if (flag > _size * _size)
				{
					delete adjacencyList;
					delete adjacencyMatrix;
					delete incidenceMatrix;

					CreateGraph();

					return;
				}
			}
		}

		for (int i = 0; i < _size; ++i)
		{
			if (tab[i] != 0)
				graphicControl = false;
		}

		if (graphicControl)
			break;
	}

	adjacencyMatrix->print();
	adjacencyList->print();
	incidenceMatrix->print();

	delete[] tab;


	// kopiowanie macieszy sasiedztwa - skad bedziemy usuwac polaczenia
	for(int i = 0; i<_size; i++)
		for(int j = 0; j<_size; j++)
			tempGraph[i][j] = adjacencyMatrix->edgeExists(i, j);
}

void Graph::CreateVisualization(std::string file)
{
	ofstream plik(file);

	plik << "digraph G" << endl << "{" << endl;
	plik << "	layout=\"circo\";" << endl;
	plik << "	node [shape = circle];" << endl;

	for (int i = 0; i < _size - 1; ++i)
		plik << "	N" << i << " -> N" << i + 1 << " [arrowhead=none][style=invis]" << endl;
	plik << "	N" << _size - 1 << " -> N0 [arrowhead=none][style=invis]" << endl;

	for (int i = 0; i < _size; ++i)
	{
		for (int j = i + 1; j < _size; ++j)
		{
			if (adjacencyMatrix->edgeExists(i, j))
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

	while (n > 0)
	{
		a = b = c = d = 0;
		adjacencyListTemp = new AdjacencyList(_size);
		adjacencyMatrixTemp = new AdjacencyMatrix(_size);
		incidenceMatrixTemp = new IncidenceMatrix(_size);

		while (a == b || a == c || a == d || b == c || b == d || c == d || !adjacencyMatrix->edgeExists(a, b) || !adjacencyMatrix->edgeExists(c, d) || adjacencyMatrix->edgeExists(a, c) || adjacencyMatrix->edgeExists(b, d))
		{
			a = rand() % _size;
			b = rand() % _size;
			c = rand() % _size;
			d = rand() % _size;
		}

		for (int i = 0; i < _size; ++i)
		{
			for (int j = i + 1; j < _size; ++j)
			{
				if ((i != a || j != b) && (i != c || j != d) && (i != b || j != a) && (i != d || j != c) && adjacencyMatrix->edgeExists(i, j))
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

bool Graph::isBridge(int u, int v){
   int deg = 0;
   for(int i = 0; i<_size; i++){
    	if(tempGraph[v][i])
    		deg++;
	}
	if(deg>1){
    	return false;
	}
	return true;
}

int Graph::edgeCount(){
   int count = 0;
   for(int i = 0; i<_size; i++)
      for(int j = i; j<_size; j++)
         if(tempGraph[i][j])
            count++;
   return count;
}

void Graph::findEulerianCircuit(int edgeCounter, int start){
	edgeCounter = edgeCount();
	for(int v = 0; v<_size; v++){
		if(tempGraph[start][v]){ //wykonujemy jesli krawedz miedzy u,v istnieje i nie jest mostem
        	if(edgeCounter <= 1 || !isBridge(start, v)){
            	cout << start << "--" << v << " ";
            	tempGraph[start][v] = tempGraph[v][start] = 0; //usuwamy krawedz z macierzy
            	edgeCounter--; //zmniejszamy ilosc krawedzi
            	findEulerianCircuit(edgeCounter, v);
        	}
    	}
	}
}

Graph::~Graph()
{
	delete adjacencyList;
	delete adjacencyMatrix;
	delete incidenceMatrix;
	delete[] _tabSeries;

	for (int i=0; i<_size; i++)
		delete[] tempGraph[i];
	delete[] tempGraph;
}


string eulerianVertices(int n)
{
	string vertices;
	int number = 1;
	for (int i=0; i<n; i++)
	{
		while ( (number%2)!= 0 || number==0 )
			number = rand() % (n-1);

		vertices += to_string(number);
		vertices.append(" ");
		number = 1;
	}
	return vertices;
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}