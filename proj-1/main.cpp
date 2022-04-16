#include "Graph.h"
#include "Vertice.h"
#include "Edge.h"
#include "GraphReader.h"

int main() {
    GraphReader reader;
    Graph *graph = reader.readIncidenceMatrix("../../examples/IncidenceMatrix.txt");
    delete graph;
}

