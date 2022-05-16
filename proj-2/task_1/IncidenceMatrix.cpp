#include <iostream>
#include "IncidenceMatrix.h"

using namespace std;

IncidenceMatrix::IncidenceMatrix(int n)
{
	_vertices = n;
	_edges = 0;
	option = new int*[n];
}

IncidenceMatrix::~IncidenceMatrix()
{
	if(_edges > 0)
	{
		for (int i = 0; i < _vertices; i++)
		{
			delete[] option[i];
		}
	}
	delete[] option;
}

void IncidenceMatrix::setEdge(int n1, int n2)
{
	if (!checkVerticeGraph(n1, n2)) return;

	else
	{
		int ** newMatrix;
		newMatrix = new int*[_vertices];
		
		//for first vertice
		if (_edges == 0)
		{
			_edges++;
			for (int i = 0; i < _vertices; i++)
			{
				newMatrix[i] = new int[_edges];
				newMatrix[i][0] = 0;
			}
			newMatrix[n1][_edges - 1] = 1;
			newMatrix[n2][_edges - 1] = 1;
		}
		//for the next ones
		else
		{
			_edges++;
			for (int i = 0; i < _vertices; i++)
			{
				newMatrix[i] = new int[_edges];
				for (int j = 0; j < _edges - 1; j++)
				{
					newMatrix[i][j] = option[i][j];
				}
			}
			for (int i = 0; i < _vertices; i++)
			{
				newMatrix[i][_edges-1] = 0;
			}
			newMatrix[n1][_edges - 1] = 1;
			newMatrix[n2][_edges - 1] = 1;
			
		}

		if (_edges == 1) //we did't create array for elements, so this conditions should be fine
			delete[] option;
		else
		{
			for (int i = 0; i < _vertices; i++)
			{
				delete[] option[i];
			}
			delete[] option;
		}
		option = newMatrix;
	}
}

int IncidenceMatrix::edgeExists(int n1, int n2)
{
	for (int i = 0; i < _edges; i++)
	{
		if (option[n1][i] == 1 && option[n2][i] == 1) return 1;
	}
	return 0;
}

void IncidenceMatrix::print()
{
	cout << "-------------------\n";
	cout << "Macierz incydencji: \n";
	for (int i = 0; i < _vertices; i++)
	{
		for (int j = 0; j < _edges; j++)
		{
			cout << option[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------------\n";
}

