#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <map>

#include "Graph.h"

class GraphWriter {

public:
    GraphWriter() = default;
    ~GraphWriter() = default;
    void writeAdjacencyMatrix(Graph* graph);
    void writeAdjacencyList(Graph* graph);
    void writeIncidenceMatrix(Graph* graph);
    void exportToGv(Graph* graph, std::string filename);
};
