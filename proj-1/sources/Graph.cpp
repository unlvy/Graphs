#include "Graph.h"

Graph::Graph() {
    m_numVertices = 0;
}

Graph::~Graph() {
    for (Edge* edge : m_edges) {
        if (edge != nullptr) { delete edge; }
    }
}

int Graph::getNumVertices() {
    return m_numVertices;
}

bool Graph::pushEdge(Edge* newEdge) {
    
    if (newEdge == nullptr) {
        return false;
    }

    Vertice* ver1;
    Vertice* ver2;
    Vertice* newVer1;
    Vertice* newVer2;

    newEdge->getVertices(&newVer1, &newVer2);
    if (newVer1 == nullptr || newVer2 == nullptr) {
        delete newEdge;
        return false;
    }

    int nv1_id = newVer1->getIndex();
    int nv2_id = newVer2->getIndex();
    int v1_id, v2_id;

    for (Edge* edge : m_edges) {
        
        if (edge->getIndex() == newEdge->getIndex()) {
            return false;
        }

        edge->getVertices(&ver1, &ver2);
        v1_id = ver1->getIndex();
        v2_id = ver2->getIndex();

        if ((nv1_id == v1_id && nv2_id == v2_id)
            || (nv1_id == v2_id && nv2_id == v1_id)) {
                delete newEdge;
                return false;
        }
    }

    if (nv1_id > m_numVertices) { m_numVertices = nv1_id; }
    if (nv2_id > m_numVertices) { m_numVertices = nv2_id; }
    m_edges.push_back(newEdge);
    return true;
}

bool Graph::popEdge(int index) {

    // index is index of edge
    // method probably needs improvement - does 
    // not affect m_numVertices
    // not used in proj-1

    int pos = -1;
    for (Edge* edge : m_edges) {
        pos++;
        if (edge->getIndex() == index) {
            delete m_edges[pos];
            m_edges.erase(m_edges.begin() + pos);
            return true;
        }
    }
    return false;
}

std::vector<Edge*>& Graph::getEdges() {
    return m_edges;
}

void Graph::sort() {
    std::sort(m_edges.begin(), m_edges.end(), Edge::comparator);
}
