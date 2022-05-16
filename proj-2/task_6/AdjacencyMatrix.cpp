#include <iostream>
#include "AdjacencyMatrix.h"

using namespace std;

AdjacencyMatrix::~AdjacencyMatrix()
{
	for(int i=0; i<_vertices; i++)
	{
		delete[] Option[i];
	}
	delete[] Option;
}

AdjacencyMatrix::AdjacencyMatrix(int n)
{
	_vertices = n;
	_edges = 0;
	Option = new int*[n];
	for (int i = 0; i < n; i++)
	{
		Option[i] = new int[n];
		for (int j = 0; j < n; j++) Option[i][j] = 0;
	}
}

void AdjacencyMatrix::setEdge(int n1, int n2)
{
	if (!checkVerticesGraph(n1, n2)) return;

	Option[n1][n2] = 1;
	Option[n2][n1] = 1;
	_edges++;
}

int AdjacencyMatrix::edgeExists(int n1, int n2)
{
	if (Option[n1][n2] == 1) return 1;
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
			cout << Option[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------------\n";

}