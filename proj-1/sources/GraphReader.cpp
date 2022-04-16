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

        return graph;

    } else {
        std::cerr << "Failed to open " << filename << std::endl;
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

        return graph;

    } else {
        std::cerr << "Failed to open " << filename << std::endl;
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

        while (std::getline(stream, line)) {
            
            splitString(line, tokens);
            edgeIndex = 1;
            std::map<int, int> edges;

            for (std::string token : tokens) { 
                if (std::stoi(token)) {
                    if (edges.find(edgeIndex) == edges.end()) {
                        edges[edgeIndex] = verticeIndex;
                    } else {
                        graph->pushEdge(new Edge(new Vertice(edges[edgeIndex]), new Vertice(verticeIndex), edgeIndex));
                    }
                }
                edgeIndex++;
            }
            verticeIndex++;
        }
        
        graph->sort();
        return graph;

    } else {
        std::cerr << "Failed to open " << filename << std::endl;
        return nullptr;
    }
}

void GraphReader::splitString(std::string str, std::vector<std::string>& tokens) {
    std::stringstream ss(str);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    tokens = std::vector<std::string>(begin, end);
}
