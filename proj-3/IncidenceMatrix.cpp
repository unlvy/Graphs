#include <iostream>
#include <tuple>
#include <iomanip>
#include "IncidenceMatrix.h"

IncidenceMatrix::IncidenceMatrix(int vertices)
{
	_vertices = vertices;
	for (int i = 0; i < _vertices; i++)
		matrix.emplace_back();
}

void IncidenceMatrix::setEdge(int vertex1, int vertex2, int weight)
{
	for (int i = 0; i < _vertices; i++)
		if (i == vertex1 || i == vertex2)
			matrix[i].push_back(weight);
		else
			matrix[i].push_back(0);
	_edges++;
}

void IncidenceMatrix::removeEdge(int vertex1, int vertex2)
{
	int column;
	for (int i = 0; i < _edges; i++)
		if (matrix[vertex1][i] != 0 && matrix[vertex2][i] != 0)
			column = i;
	for (auto row : matrix)
		row.erase(row.begin() + column);
}

bool IncidenceMatrix::edgeExists(int vertex1, int vertex2)
{
	for (int i = 0; i < _edges; i++)
		if (matrix[vertex1][i] != 0 && matrix[vertex2][i] != 0)
			return true;
	return false;
}

std::tuple<int, int> IncidenceMatrix::edgeToVertices(int edgeIndex)
{
	for (int i = 0; i < _vertices; i++)
		if (matrix[i][edgeIndex] != 0)
			for (int j = i + 1; j < _vertices; j++)
				if (matrix[j][edgeIndex] != 0)
					return std::make_tuple(i, j);
	return std::make_tuple(-1, -1);
}

int IncidenceMatrix::verticesToEdge(int vertex1, int vertex2)
{
	for (int i = 0; i < _edges; i++)
		if (matrix[vertex1][i] != 0 && matrix[vertex2][i] != 0)
			return i;
	return -1;
}

void IncidenceMatrix::print()
{
	std::cout << "-------------------\nIncidence matrix:" << std::endl;
	for (int i = 0; i < _vertices; i++)
	{
		for (int j = 0; j < _edges; j++)
			std::cout << std::setw(2) << matrix[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << "-------------------" << std::endl;
}
