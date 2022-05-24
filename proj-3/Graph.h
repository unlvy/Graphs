#pragma once

#include <string>
#include <set>
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "IncidenceMatrix.h"

class Graph
{
public:
	explicit Graph(int vertices);
	static Graph readFromAdjacencyMatrix(const std::string& filename);
	static Graph readFromIncidenceMatrix(const std::string& filename);
	void createVisualization(const std::string &filename);
	void createSpanningTreeVisualization(const std::string &filename);
	int getVertexCount() const;
	void setEdge(int vertex1, int vertex2, int weight);
	void setEdge(int edgeIndex, int weight);
	void removeEdge(int vertex1, int vertex2);
	bool edgeExists(int vertex1, int vertex2);
	std::vector<int> getNeighbors(int vertex);
	int getEdgeWeight(int vertex1, int vertex2);
	int getEdgeWeight(int edgeIndex);
	std::tuple<int,int> edgeToVertices(int edgeIndex);
	int verticesToEdge(int vertex1, int vertex2);
	void generateRandomEdges(double chance);
	bool isConnected();
	void print();
	void printDijkstra(int vertex);
	void printDistanceMatrix();
	std::vector<std::vector<int>> distanceMatrix();
	std::tuple<int, int> getCenter();
	std::tuple<int, int> getMinimaxCenter();

	Graph spanningTree();
protected:
	static void splitString(const std::string& str, std::vector<std::string>& tokens);
	void depthFirstSearch(int vertex, std::set<int> &visited);
	std::vector<int> dijkstra(int startingVertex);
	std::vector<int> dijkstraToPath(std::vector<int> dijkstra, int targetVertex);
	int pathToDistance(std::vector<int> path);
	int _vertices = 0;
	int _edges = 0;
	AdjacencyList _adjacencyList;
	AdjacencyMatrix _adjacencyMatrix;
	IncidenceMatrix _incidenceMatrix;
};
