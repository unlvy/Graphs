#include <iostream>
#include "IncidenceMatrix.h"

using namespace std;

IncidenceMatrix::IncidenceMatrix(int n)
{
	_vertices = n;
	_edges = 0;
	Option = new int*[n];
}

IncidenceMatrix::~IncidenceMatrix()
{
	if(_edges > 0)
	{
		for (int i = 0; i < _vertices; i++)
		{
			delete[] Option[i];
		}
	}
	delete[] Option;
}

void IncidenceMatrix::setEdge(int n1, int n2)
{
	if (!checkVerticesGraph(n1, n2)) return;

	else
	{
		int ** newMatrix;
		newMatrix = new int*[_vertices];
		
		//dla pierwszej krawedzi
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
		//dla kazdej kolejnej krawedzi
		else
		{
			_edges++;
			for (int i = 0; i < _vertices; i++)
			{
				newMatrix[i] = new int[_edges];
				for (int j = 0; j < _edges - 1; j++)
				{
					newMatrix[i][j] = Option[i][j];
				}
			}
			for (int i = 0; i < _vertices; i++)
			{
				newMatrix[i][_edges-1] = 0;
			}
			newMatrix[n1][_edges - 1] = 1;
			newMatrix[n2][_edges - 1] = 1;
			
		}

		if (_edges == 1) //nie utworzylismy wczesniej tablic dla elementow, a wiec wystarczy
			delete[] Option;
		else
		{
			for (int i = 0; i < _vertices; i++)
			{
				delete[] Option[i];
			}
			delete[] Option;
		}
		Option = newMatrix;
	}
}

int IncidenceMatrix::edgeExists(int n1, int n2)
{
	for (int i = 0; i < _edges; i++)
	{
		if (Option[n1][i] == 1 && Option[n2][i] == 1) return 1;
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
			cout << Option[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------------\n";
}

