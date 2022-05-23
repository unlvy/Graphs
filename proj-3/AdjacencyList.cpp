#include <iostream>
#include <algorithm>
#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(int vertices)
{
	_vertices = vertices;
	for (int i = 0; i < _vertices; i++)
		matrix.emplace_back();
}

void AdjacencyList::setEdge(int vertex1, int vertex2, int weight)
{
	matrix[vertex1].push_back(vertex2);
	matrix[vertex2].push_back(vertex1);
	std::sort(matrix[vertex1].begin(), matrix[vertex1].end());
	std::sort(matrix[vertex2].begin(), matrix[vertex2].end());
	_edges++;
}

void AdjacencyList::removeEdge(int vertex1, int vertex2)
{
	matrix[vertex1].erase(std::remove(matrix[vertex1].begin(), matrix[vertex1].end(), vertex2), matrix[vertex1].end());
	matrix[vertex2].erase(std::remove(matrix[vertex2].begin(), matrix[vertex2].end(), vertex1), matrix[vertex2].end());
	_edges--;
}

bool AdjacencyList::edgeExists(int vertex1, int vertex2)
{
	return std::any_of(matrix[vertex1].begin(), matrix[vertex1].end(), [vertex2](int x) { return x == vertex2; });
}

std::vector<int> AdjacencyList::getNeighbors(int vertex)
{
	return matrix[vertex];
}

void AdjacencyList::print()
{
	std::cout << "-------------------\nAdjacency list:" << std::endl;
	for (int i = 0; i < _vertices; i++)
	{
		std::cout << i << ": ";
		for (int vertex : matrix[i])
			std::cout << vertex << " ";
		std::cout << std::endl;
	}
	std::cout << "-------------------" << std::endl;
}
