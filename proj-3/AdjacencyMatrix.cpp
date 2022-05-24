#include <iostream>
#include <iomanip>
#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(int vertices)
{
	_vertices = vertices;
	for (int i = 0; i < _vertices; i++)
	{
		matrix.emplace_back();
		for (int j = 0; j < _vertices; j++)
			matrix[i].push_back(0);
	}
}

void AdjacencyMatrix::setEdge(int vertex1, int vertex2, int weight)
{
	matrix[vertex1][vertex2] = weight;
	matrix[vertex2][vertex1] = weight;
	_edges++;
}

void AdjacencyMatrix::removeEdge(int vertex1, int vertex2)
{
	matrix[vertex1][vertex2] = 0;
	matrix[vertex2][vertex1] = 0;
	_edges--;
}

bool AdjacencyMatrix::edgeExists(int vertex1, int vertex2)
{
	return matrix[vertex1][vertex2] != 0;
}

int AdjacencyMatrix::getEdgeWeight(int vertex1, int vertex2)
{
	return matrix[vertex1][vertex2];
}

void AdjacencyMatrix::print()
{
	std::cout << "-------------------\nAdjacency matrix:" << std::endl;
	for (int i = 0; i < _vertices; i++)
	{
		for (int j = 0; j < _vertices; j++)
			std::cout << std::setw(2) << matrix[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << "-------------------" << std::endl;
}
