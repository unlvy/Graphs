#include "GraphWriter.h"

void GraphWriter::writeAdjacencyMatrix(Graph* graph) {
    
    const int numVertices = graph->getNumVertices();

    int** adjacencyMatrix = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjacencyMatrix[i] = new int[numVertices];
        std::fill(adjacencyMatrix[i], adjacencyMatrix[i] + numVertices, 0);
    }

    Vertice* v1;
    Vertice* v2;

    std::vector<Edge*> edges = graph->getEdges();
    for (Edge* edge : edges) {
        edge->getVertices(&v1, &v2);
        adjacencyMatrix[v1->getIndex() - 1][v2->getIndex() - 1] = 1;
        adjacencyMatrix[v2->getIndex() - 1][v1->getIndex() - 1] = 1;
    }

    std::cout << "\n"
        "-----------------------------------\n"
        "- Printing graph adjacency matrix -\n"
        "-----------------------------------\n";
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int i = 0; i < numVertices; i++) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}

void GraphWriter::writeAdjacencyList(Graph* graph) {

    const int numVertices = graph->getNumVertices();
    std::map<int, std::vector<int>> adjacencyList;
    Vertice* v1;
    Vertice* v2;
    int v1_id, v2_id;
    std::vector<Edge*> edges = graph->getEdges();

    for (Edge* edge : edges) {

        edge->getVertices(&v1, &v2);
        v1_id = v1->getIndex();
        v2_id = v2->getIndex();

        if (!(adjacencyList.count(v1_id) && 
            std::count(adjacencyList[v1_id].begin(), adjacencyList[v1_id].end(), v2_id))) {
            adjacencyList[v1_id].push_back(v2_id);
        }
        if (!(adjacencyList.count(v2_id) &&
            std::count(adjacencyList[v2_id].begin(), adjacencyList[v2_id].end(), v1_id))) {
            adjacencyList[v2_id].push_back(v1_id);
        }
    }

    std::cout << "\n" 
        "-----------------------------------\n"
        "-  Printing graph adjacency list  -\n"
        "-----------------------------------\n";
    for (int i = 1; i <= numVertices; i++) {
        if (adjacencyList.count(i)) {
            std::sort(adjacencyList[i].begin(), adjacencyList[i].end());
            for (int v : adjacencyList[i]) {
                std::cout << v << " ";
            }
        }
        std::cout << std::endl;
    }
}

void GraphWriter::writeIncidenceMatrix(Graph* graph) {

    const int numVertices = graph->getNumVertices();
    Vertice* v1;
    Vertice* v2;
    int v1_id, v2_id;

    std::cout << "\n"
        "-----------------------------------\n"
        "- Printing graph incidence matrix -\n"
        "-----------------------------------\n";
    for (int i = 1; i <= numVertices; i++) {
        for (Edge* edge : graph->getEdges()) {
            edge->getVertices(&v1, &v2);
            v1_id = v1->getIndex();
            v2_id = v2->getIndex();
            std::cout << ((v1_id == i || v2_id == i) ? 1 : 0) << " ";
        }
        std::cout << std::endl;
    }
}

void GraphWriter::exportToGv(Graph* graph, std::string filename) {

    filename += ".gv";
    std::ofstream stream(filename);
    if (stream.is_open()) {
        
        const int numVertices = graph->getNumVertices();
        std::map<int, std::vector<int>> adjacencyList;
        Vertice* v1;
        Vertice* v2;
        int v1_id, v2_id;
        std::vector<Edge*> edges = graph->getEdges();

        for (Edge* edge : edges) {

            edge->getVertices(&v1, &v2);
            v1_id = v1->getIndex();
            v2_id = v2->getIndex();

            if (!(adjacencyList.count(v1_id) && 
                std::count(adjacencyList[v1_id].begin(), adjacencyList[v1_id].end(), v2_id))) {
                adjacencyList[v1_id].push_back(v2_id);
            }
            if (!(adjacencyList.count(v2_id) &&
                std::count(adjacencyList[v2_id].begin(), adjacencyList[v2_id].end(), v1_id))) {
                adjacencyList[v2_id].push_back(v1_id);
            }
        }

        stream << 
            "graph g {\n"
            "\tlayout=\"neato\";\n"
            "\tnode[margin=0 fontcolor=black fontname=monospace fontsize=28 width=0.8 fillcolor=lightskyblue1 shape=circle style=filled]\n"
	        "\tedge[penwidth=2]\n";

        double x, y;
        double r = 5;
        double pi = 3.1415;

        for (int i = 1; i <= numVertices; i++) {
            x = -std::cos(2 * pi / numVertices * (i - 1) + pi / 2) * r;
            y = std::sin(2 * pi / numVertices * (i - 1) + pi / 2) * r;
            stream << "\t" << i << "[pos=\"" << x << ", " << y << "!\"]\n";
        }

        for (int i = 1; i <= numVertices; i++) {
            if (adjacencyList.count(i)) {
                std::sort(adjacencyList[i].begin(), adjacencyList[i].end());
                for (int v : adjacencyList[i]) {
                    stream << "\t" << i << " -- " << v << ";\n";
                    adjacencyList[v].erase(
                        std::remove(adjacencyList[v].begin(), 
                            adjacencyList[v].end(), i), 
                            adjacencyList[v].end());
                }
            }
        }

        stream << "}";
        stream.close();
        std::cout << 
            "\nFile generated. Please run below command:\n"
            "  dot " << filename << " -Tsvg -o output.svg\n"
            "To generate svg graphic\n";
    } else {
        std::cerr << "\nFailed to open " << filename << std::endl;
    }
}
