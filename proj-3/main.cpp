#include <iostream>
#include <iomanip>
#include "Graph.h"
#include "UserInput.h"

int main()
{
	std::cout << "\n"
				 "-----------------------------------\n"
				 "-      Project 3. Main menu       -\n"
				 "-----------------------------------\n"
				 "- Options:                        -\n"
				 "-     1. Read graph from file     -\n"
				 "-     2. Generate random graph    -\n"
				 "-----------------------------------" << std::endl;

	Graph graph(0);
	std::function<bool(int)> isCorrectOption = [](int x) -> bool { return x == 1 | x == 2; };
	int option = UserInput::getInput("Please choose option: ", isCorrectOption);
	if (option == 1)
	{
		while (true)
		{
			std::string filename = UserInput::getInput("Please enter filename: ");
			std::cout << "\n"
						 "-----------------------------------\n"
						 "- Options:                        -\n"
						 "-     1. Adjacency matrix         -\n"
						 "-     2. Incidence matrix         -\n"
						 "-----------------------------------" << std::endl;
			int fileType = UserInput::getInput("Select file type: ", isCorrectOption);
			if (fileType == 1)
				graph = Graph::readFromAdjacencyMatrix(filename);
			else
				graph = Graph::readFromIncidenceMatrix(filename);

			if (graph.getVertexCount() == 0)
				std::cout << "Failed to open file or graph was empty! Please try again." << std::endl;
			else if (!graph.isConnected())
				std::cout << "Graph needs to be connected! Please try again." << std::endl;
			else
				break;
		}
	}
	else
	{
		std::function<bool(int)> isCorrectNumberOfVertices = [](int x) -> bool { return x > 1; };
		int vertexCount = UserInput::getInput("Insert number of vertices: ", isCorrectNumberOfVertices);
		std::function<bool(double)> isCorrectProbabilityOfEdges = [](double x) -> bool { return x > 0 && x <= 1; };
		double edgeChance = UserInput::getInput("Insert probability of edge: ", isCorrectProbabilityOfEdges);
		int attempt = 0;
		do
		{
			std::cout << "\rAttempt " << ++attempt << " at generating connected graph";
			graph = Graph(vertexCount);
			graph.generateRandomEdges(edgeChance);
		}
		while (!graph.isConnected());
		std::cout << std::endl;
	}

	std::string graphFilename = UserInput::getInput("Please enter filename for graph: ");
	std::string spanningTreeFilename = UserInput::getInput("Please enter filename for spanning tree: ");
	graph.createVisualization(graphFilename);
	graph.createSpanningTreeVisualization(spanningTreeFilename);
	graph.print();
	int vertexCount = graph.getVertexCount();
	std::function<bool(int)> isVertexInGraph = [vertexCount](int x) -> bool { return x >= 0 && x < vertexCount; };
	int dijkstraVertex = UserInput::getInput("Insert vertex to count distance from: ", isVertexInGraph);
	graph.printDijkstra(dijkstraVertex);
	graph.printDistanceMatrix();
	auto [center, centerSum] = graph.getCenter();
	auto [minimax, minimaxDistance] = graph.getMinimaxCenter();
	std::cout << "Center: " << center << " (sum: " << centerSum << ")" << std::endl;
	std::cout << "Minimax center: " << minimax << " (distance: " << minimaxDistance << ")" << std::endl;
	std::cout << "-------------------" << std::endl;

	return 0;
}