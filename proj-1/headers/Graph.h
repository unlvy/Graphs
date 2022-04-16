#pragma once

#include <vector>
#include <algorithm>

#include "Edge.h"

class Graph {

public:
    Graph();
    ~Graph();
    bool pushEdge(Edge* newEdge);
    bool popEdge(int index);
    void sort();
protected:
    std::vector<Edge*> m_edges;
};