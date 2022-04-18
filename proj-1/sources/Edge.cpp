#include "Edge.h"

bool Edge::comparator(Edge* e1, Edge* e2) {
    return e1->getIndex() < e2->getIndex();
}

Edge::Edge(Vertice* v1, Vertice* v2, int index) {
    m_index = index;
    m_ver1 = v1;
    m_ver2 = v2;
}

Edge::~Edge() {
    if (m_ver1 != nullptr) { delete m_ver1; }
    if (m_ver2 != nullptr) { delete m_ver2; }   
}

int Edge::getIndex() {
    return m_index;
}

void Edge::getVertices(Vertice** ver1, Vertice** ver2) {
    *ver1 = m_ver1;
    *ver2 = m_ver2;
}
