#include "GraphReader.h"

Graph* GraphReader::readAdjacencyMatrix(std::string filename) {
    
    std::ifstream stream(filename);
    if (stream.is_open()) {

        std::string line;
        std::vector<std::string> tokens;
        int currentVerticeIndex = 1;
        int edgeIndex = 1;
        int verticeIndex;
        Graph* graph = new Graph();

        while (std::getline(stream, line)) {
            
            splitString(line, tokens);
            verticeIndex = 1;

            for (std::string token : tokens) {
                if (std::stoi(token)) {
                    if (graph->pushEdge(new Edge(new Vertice(currentVerticeIndex), new Vertice(verticeIndex), edgeIndex))) {
                        edgeIndex++;
                    }
                }
                verticeIndex++;
            }
            currentVerticeIndex++;
        }

        std::cout << "\nGraph read" << std::endl;
        return graph;

    } else {
        std::cerr << "\nFailed to open " << filename << std::endl;
        return nullptr;
    }
}

Graph* GraphReader::readAdjacencyList(std::string filename) {
    
    std::ifstream stream(filename);
    if (stream.is_open()) {

        std::string line;
        std::vector<std::string> tokens;
        int verticeIndex = 1;
        int edgeIndex = 1;
        Graph* graph = new Graph();

        while (std::getline(stream, line)) {
            
            splitString(line, tokens);

            for (std::string token : tokens) { 
                if (graph->pushEdge(new Edge(new Vertice(verticeIndex), new Vertice(std::stoi(token)), edgeIndex))) {
                    edgeIndex++;
                }
            }
            verticeIndex++;
        }

        std::cout << "\nGraph read" << std::endl;
        return graph;

    } else {
        std::cerr << "\nFailed to open " << filename << std::endl;
        return nullptr;
    }
}

Graph* GraphReader::readIncidenceMatrix(std::string filename) {

    std::ifstream stream(filename);
    if (stream.is_open()) {

        std::string line;
        std::vector<std::string> tokens;
        int verticeIndex = 1;
        int edgeIndex;
        Graph* graph = new Graph();
        std::map<int, int> edges;

        while (std::getline(stream, line)) {
            
            splitString(line, tokens);
            edgeIndex = 1;

            for (std::string token : tokens) { 
                if (std::stoi(token)) {   
                    if (edges.count(edgeIndex)) {
                        graph->pushEdge(new Edge(new Vertice(edges[edgeIndex]), new Vertice(verticeIndex), edgeIndex));
                    } else {
                        edges[edgeIndex] = verticeIndex;
                    }
                }
                edgeIndex++;
            }
            verticeIndex++;
        }
        
        graph->sort();
        std::cout << "\nGraph read" << std::endl;
        return graph;

    } else {
        std::cerr << "\nFailed to open " << filename << std::endl;
        return nullptr;
    }
}

void GraphReader::splitString(std::string str, std::vector<std::string>& tokens) {
    std::stringstream ss(str);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    tokens = std::vector<std::string>(begin, end);
}
