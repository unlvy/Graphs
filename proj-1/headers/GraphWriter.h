#pragma once

#include <iostream>
#include <map>

#include "Graph.h"

class GraphWriter {

public:
    GraphWriter() = default;
    ~GraphWriter() = default;
    void writeAdjacencyMatrix(Graph* graph);
    void writeAdjacencyList(Graph* graph);
    void writeIncidenceMatrix(Graph* graph);

};