#include <iostream>
#include "AdjacencyMatrix.h"

using namespace std;

AdjacencyMatrix::~AdjacencyMatrix()
{
	for(int i=0; i<_vertices; i++)
	{
		delete[] option[i];
	}
	delete[] option;
}

AdjacencyMatrix::AdjacencyMatrix(int n)
{
	_vertices = n;
	_edges = 0;
	option = new int*[n];
	for (int i = 0; i < n; i++)
	{
		option[i] = new int[n];
		for (int j = 0; j < n; j++) option[i][j] = 0;
	}
}

void AdjacencyMatrix::setEdge(int n1, int n2)
{
	if (!checkVerticeGraph(n1, n2)) return;

	option[n1][n2] = 1;
	option[n2][n1] = 1;
	_edges++;
}

int AdjacencyMatrix::edgeExists(int n1, int n2)
{
	if (option[n1][n2] == 1) return 1;
	else return 0;
}

void AdjacencyMatrix::print()
{
	cout << "-------------------\n";
	cout << "Macierz sasiedztwa:\n";
	for (int i = 0; i < _vertices; i++)
	{
		for (int j = 0; j < _vertices; j++)
		{
			cout << option[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------------\n";

}