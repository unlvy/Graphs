#include "RandomGraphGenerator.h"

Graph* RandomGraphGenerator::generate1(int n, int l) {

    if (l > (n * (n - 1)) / 2 || l < 0 || n < 1) {
        std::cerr << "\nWrong input arguments dependencies\n";
        return nullptr;
    }

    int edgeIndex = 1;
    int v1_id, v2_id;
    std::srand(std::time(NULL));
    Graph* graph = new Graph();

    while (edgeIndex <= l) {

        v1_id = std::rand() % n + 1;
        v2_id = std::rand() % n + 1;
        while(v1_id == v2_id) {
            v2_id = std::rand() % n + 1;
        }

        if (graph->pushEdge(new Edge(
            new Vertice(v1_id), 
            new Vertice(v2_id), 
            edgeIndex))) 
            {
                edgeIndex++; 
        }
    }

    return graph;
}

Graph* RandomGraphGenerator::generate2(int n, double p) {
    
    if (p < 0.0 || p > 1.0 ) { return nullptr; }

    Graph* graph = new Graph();
    std::srand(std::time(NULL));
    int edgeNum = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (static_cast<double>(std::rand()) / RAND_MAX <= p) {
                graph->pushEdge(new Edge(
                    new Vertice(i), 
                    new Vertice(j), 
                    edgeNum++
                    ));
            }
        }
    }
    return graph;
}
