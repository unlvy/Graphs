#pragma once

#include "Vertice.h"

class Edge {

public:
    Edge(Vertice* v1, Vertice* v2, int index);
    ~Edge();
    int getIndex();
    void getVertices(Vertice** ver1, Vertice** ver2);
    static bool comparator(Edge* e1, Edge* e2);
protected:
    int m_index;
    Vertice* m_ver1;
    Vertice* m_ver2;
};