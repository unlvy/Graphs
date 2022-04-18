#pragma once

#include <vector>
#include <algorithm>

#include "Edge.h"

class Graph {

public:
    Graph();
    ~Graph();
    int getNumVertices();
    bool pushEdge(Edge* newEdge);
    bool popEdge(int index);
    std::vector<Edge*>& getEdges();
    void sort();
protected:
    std::vector<Edge*> m_edges;
    int m_numVertices;
};
