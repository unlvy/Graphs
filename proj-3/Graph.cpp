#include <iostream>
#include <fstream>
#include <random>
#include <set>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include "Graph.h"

Graph::Graph(int vertices) : _adjacencyList(vertices), _adjacencyMatrix(vertices), _incidenceMatrix(vertices)
{
	_vertices = vertices;
}

Graph Graph::readFromAdjacencyMatrix(const std::string& filename)
{
	std::ifstream stream(filename);
	if (stream.is_open())
	{
		std::string line;
		std::vector<std::string> tokens;
		std::vector<std::vector<int>> matrix;

		std::getline(stream, line);
		splitString(line, tokens);

		int vertexCount = (int)tokens.size();
		Graph graph(vertexCount);

		int i = 0;
		do
		{
			splitString(line, tokens);
			int j = 0;
			for (const std::string& token : tokens)
			{
				int weight = std::stoi(token);
				graph.setEdge(i, j, weight);
				j++;
			}
			i++;
		}
		while (std::getline(stream, line));

		stream.close();
		return graph;
	}
	return Graph(0);
}

Graph Graph::readFromIncidenceMatrix(const std::string& filename)
{
	std::ifstream stream(filename);
	if (stream.is_open())
	{
		std::string line;
		std::vector<std::string> tokens;

		std::vector<std::vector<int>> matrix;
		int row = 0;
		while (std::getline(stream, line))
		{
			matrix.emplace_back();
			splitString(line, tokens);
			for (const std::string& token : tokens)
			{
				int value = std::stoi(token);
				matrix[row].push_back(value);
			}
			row++;
		}

		int vertexCount = (int)matrix.size();
		Graph graph(vertexCount);

		for (int i = 0; i < vertexCount; i++)
			for (int j = 0; j < matrix[i].size(); j++)
				if (matrix[i][j] != 0)
					for (int k = i + 1; k < vertexCount; k++)
						if (matrix[k][j] != 0)
							graph.setEdge(i, k, matrix[i][j]);

		stream.close();
		return graph;
	}
	return Graph(0);
}

void Graph::createVisualization(const std::string &filename)
{
	std::ofstream file(filename + ".gv");

	file << "graph g {" << std::endl
		 << "\tnode[fontname=consolas fillcolor=lightskyblue1 shape=circle style=filled]" << std::endl
		 << "\tedge[fontname=consolas]" << std::endl;

	for (int i = 0; i < _vertices; ++i)
		file << "\t" << i << std::endl;

	for (int i = 0; i < _vertices; ++i)
		for (int j = i + 1; j < _vertices; j++)
			if (edgeExists(i, j))
				file << "\t" << i << " -- " << j << " [label=" << getEdgeWeight(i, j) << "]" << std::endl;
	file << "}";

	file.close();

	std::cout << "-------------------\nGraph Dot file generated. Please run the following command:\n" << "  dot "
			  << filename << ".gv -Tsvg -o output.svg\n"
			  << "to generate svg graphic\n-------------------" << std::endl;
}

void Graph::createSpanningTreeVisualization(const std::string &filename)
{
	Graph tree = spanningTree();

	std::ofstream file(filename + ".gv");

	file << "graph g {" << std::endl
		 << "\tnode[fontname=consolas fillcolor=lightskyblue1 shape=circle style=filled]" << std::endl
		 << "\tedge[fontname=consolas]" << std::endl;

	for (int i = 0; i < _vertices; ++i)
		file << "\t" << i << std::endl;

	for (int i = 0; i < _vertices; ++i)
		for (int j = i + 1; j < _vertices; j++)
			if (tree.edgeExists(i, j))
				file << "\t" << i << " -- " << j << " [label=" << getEdgeWeight(i, j)
					 << " color=blue fontcolor=blue penwidth=2]" << std::endl;
			else if (edgeExists(i, j))
				file << "\t" << i << " -- " << j << " [label=" << getEdgeWeight(i, j)
					 << " color=gray fontcolor=gray]" << std::endl;
	file << "}";

	file.close();

	std::cout << "-------------------\nSpanning tree Dot file generated. Please run the following command:\n"
			  << "  dot " << filename << ".gv -Tsvg -o output.svg\n"
			  << "to generate svg graphic\n-------------------" << std::endl;
}

int Graph::getVertexCount() const
{
	return _vertices;
}

void Graph::setEdge(int vertex1, int vertex2, int weight)
{
	if ((vertex1 >= 0) && (vertex2 >= 0) && (vertex1 < _vertices) && (vertex2 < _vertices) && (vertex1 != vertex2) &&
		!edgeExists(vertex1, vertex2) && weight != 0)
	{
		_adjacencyList.setEdge(vertex1, vertex2, weight);
		_adjacencyMatrix.setEdge(vertex1, vertex2, weight);
		_incidenceMatrix.setEdge(vertex1, vertex2, weight);
		_edges++;
	}
}

void Graph::setEdge(int edgeIndex, int weight)
{
	if (edgeIndex >= 0 && weight != 0)
	{
		auto [vertex1, vertex2] = edgeToVertices(edgeIndex);
		if ((vertex1 >= 0) && (vertex2 >= 0) && (vertex1 < _vertices) && (vertex2 < _vertices) &&
			(vertex1 != vertex2) &&
			!edgeExists(vertex1, vertex2))
		{
			_adjacencyList.setEdge(vertex1, vertex2, weight);
			_adjacencyMatrix.setEdge(vertex1, vertex2, weight);
			_incidenceMatrix.setEdge(vertex1, vertex2, weight);
			_edges++;
		}
	}
}

void Graph::removeEdge(int vertex1, int vertex2)
{
	if ((vertex1 >= 0) && (vertex2 >= 0) && (vertex1 < _vertices) && (vertex2 < _vertices) && (vertex1 != vertex2) &&
		edgeExists(vertex1, vertex2))
	{
		_adjacencyList.removeEdge(vertex1, vertex2);
		_adjacencyMatrix.removeEdge(vertex1, vertex2);
		_incidenceMatrix.removeEdge(vertex1, vertex2);
		_edges--;
	}
}

bool Graph::edgeExists(int vertex1, int vertex2)
{
	return _adjacencyMatrix.edgeExists(vertex1, vertex2);
}

std::vector<int> Graph::getNeighbors(int vertex)
{
	return _adjacencyList.getNeighbors(vertex);
}

int Graph::getEdgeWeight(int vertex1, int vertex2)
{
	if ((vertex1 >= 0) && (vertex2 >= 0) && (vertex1 < _vertices) && (vertex2 < _vertices) && (vertex1 != vertex2))
		return _adjacencyMatrix.getEdgeWeight(vertex1, vertex2);
	return 0;
}

int Graph::getEdgeWeight(int edgeIndex)
{
	auto [vertex1, vertex2] = edgeToVertices(edgeIndex);
	return getEdgeWeight(vertex1, vertex2);
}

std::tuple<int, int> Graph::edgeToVertices(int edgeIndex)
{
	return _incidenceMatrix.edgeToVertices(edgeIndex);
}

int Graph::verticesToEdge(int vertex1, int vertex2)
{
	return _incidenceMatrix.verticesToEdge(vertex1, vertex2);
}

void Graph::generateRandomEdges(double chance)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	std::uniform_int_distribution<> wdis(1, 10);
	for (int i = 0; i < _vertices; i++)
		for (int j = i + 1; j < _vertices; j++)
			if (dis(gen) < chance)
				setEdge(i, j, wdis(gen));
}

bool Graph::isConnected()
{
	std::set<int> visited;
	depthFirstSearch(0, visited);
	return visited.size() == _vertices;
}

void Graph::print()
{
	_adjacencyList.print();
	_adjacencyMatrix.print();
	_incidenceMatrix.print();
}

void Graph::printDijkstra(int vertex)
{
	std::cout << "-------------------\nDistances from vertex " << vertex << ":" << std::endl;
	auto dijkstraResult = dijkstra(vertex);
	for (int i = 0; i < _vertices; i++)
	{
		auto path = dijkstraToPath(dijkstraResult, i);
		std::cout << "d(" << i << ")\t= " << pathToDistance(path) << "\t==> [";
		for (auto v : path)
			std::cout << v << " - ";
		std::cout << "\b\b\b]  " << std::endl;
	}
	std::cout << "-------------------" << std::endl;
}

void Graph::printDistanceMatrix()
{
	std::cout << "-------------------\nDistance matrix:" << std::endl;
	auto matrix = distanceMatrix();
	for (const auto &row : matrix)
	{
		for (int value : row)
			std::cout << std::setw(2) << value << " ";
		std::cout << std::endl;
	}
	std::cout << "-------------------" << std::endl;
}

std::vector<std::vector<int>> Graph::distanceMatrix()
{
	std::vector<std::vector<int>> matrix;
	for (int i = 0; i < _vertices; i++)
	{
		matrix.emplace_back();
		auto dijkstraResult = dijkstra(i);
		for (int j = 0; j < _vertices; j++)
			matrix[i].push_back(pathToDistance(dijkstraToPath(dijkstraResult, j)));
	}
	return matrix;
}

std::tuple<int, int> Graph::getCenter()
{
	auto matrix = distanceMatrix();
	std::vector<int> sums;
	for (auto row : matrix)
		sums.push_back(std::accumulate(row.begin(), row.end(), 0));
	auto min = std::min_element(sums.begin(), sums.end());
	return std::make_tuple(min - sums.begin(), *min);
}

std::tuple<int, int> Graph::getMinimaxCenter()
{
	auto matrix = distanceMatrix();
	std::vector<int> maxes;
	for (auto row : matrix)
		maxes.push_back(*std::max_element(row.begin(), row.end()));
	auto min = std::min_element(maxes.begin(), maxes.end());
	return std::make_tuple(min - maxes.begin(), *min);
}

void Graph::splitString(const std::string& str, std::vector<std::string>& tokens) {
	std::stringstream ss(str);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	tokens = std::vector<std::string>(begin, end);
}

void Graph::depthFirstSearch(int vertex, std::set<int> &visited) // NOLINT(misc-no-recursion)
{
	visited.insert(vertex);
	for (int neighbor : _adjacencyList.getNeighbors(vertex))
		if (visited.find(neighbor) == visited.end())
			depthFirstSearch(neighbor, visited);
}

std::vector<int> Graph::dijkstra(int startingVertex)
{
	std::vector<int> prev, dist, ready;

	for (int i = 0; i < _vertices; i++)
	{
		dist.push_back(std::numeric_limits<int>::max());
		prev.push_back(-1);
	}
	dist[startingVertex] = 0;

	while (ready.size() != _vertices)
	{
		int minIndex, minDist = std::numeric_limits<int>::max();
		for (int i = 0; i < _vertices; i++)
		{
			if (std::find(ready.begin(), ready.end(), i) == ready.end() && dist[i] < minDist)
			{
				minIndex = i;
				minDist = dist[i];
			}
		}

		ready.push_back(minIndex);

		for (int i = 0; i < _vertices; i++)
		{
			auto n = getNeighbors(minIndex);
			if (std::find(n.begin(), n.end(), i) != n.end() &&
				std::find(ready.begin(), ready.end(), i) == ready.end() &&
				dist[i] > dist[minIndex] + getEdgeWeight(i, minIndex))
			{
				dist[i] = dist[minIndex] + getEdgeWeight(i, minIndex);
				prev[i] = minIndex;
			}
		}
	}

	return prev;
}

std::vector<int> Graph::dijkstraToPath(std::vector<int> dijkstra, int targetVertex)
{
	std::vector<int> path;
	while (targetVertex != -1)
	{
		path.push_back(targetVertex);
		targetVertex = dijkstra[targetVertex];
	}
	std::reverse(path.begin(), path.end());
	return path;
}

int Graph::pathToDistance(std::vector<int> path)
{
	int distance = 0;
	for (int i = 1; i < path.size(); i++)
		distance += getEdgeWeight(path[i], path[i - 1]);
	return distance;
}

Graph Graph::spanningTree()
{
	Graph result = Graph(_vertices);

	std::vector<int> C, E, Q;
	for (int i = 0; i < _vertices; i++)
	{
		C.push_back(std::numeric_limits<int>::max());
		E.push_back(-1);
		Q.push_back(i);
	}
	C[0] = 0;

	while (!Q.empty())
	{
		int minIndex = *(Q.begin()), minDist = std::numeric_limits<int>::max();
		for (int i : Q)
		{
			if (C[i] < minDist)
			{
				minIndex = i;
				minDist = C[i];
			}
		}
		Q.erase(std::remove(Q.begin(), Q.end(), minIndex), Q.end());

		auto [vertex1, vertex2] = edgeToVertices(E[minIndex]);
		result.setEdge(vertex1, vertex2, getEdgeWeight(E[minIndex]));

		auto neighbors = getNeighbors(minIndex);
		for (int i : neighbors)
		{
			if (std::find(Q.begin(), Q.end(), i) != Q.end() && getEdgeWeight(minIndex, i) < C[i])
			{
				C[i] = getEdgeWeight(minIndex, i);
				E[i] = verticesToEdge(minIndex, i);
			}
		}
	}

	return result;
}
