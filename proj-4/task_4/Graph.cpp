#include "Graph.h"
#include "Dfs.h"
#include <iomanip>
#include <iostream>
#include <limits.h>

Graph::Graph(int n) {
  _size = n;
  adjacencyList = new AdjacencyList(_size);
  adjacencyMatrix = new AdjacencyMatrix(_size);
  incidenceMatrix = new IncidenceMatrix(_size);
}

Graph::~Graph() {
  delete adjacencyList;
  delete adjacencyMatrix;
  delete incidenceMatrix;
}

void Graph::CreateGraph(double p) {
  std::srand(time(NULL));

  for (int i = 0; i < _size; i++) {
    for (int j = i + 1; j < _size; j++) {
      if (static_cast<double>(std::rand()) / RAND_MAX <= p) {
        addEdge(i, j);
      }

      if (static_cast<double>(std::rand()) / RAND_MAX <= p) {
        addEdge(j, i);
      }
    }
  }
}

void Graph::addEdge(int i, int j) {
  adjacencyMatrix->setEdge(i, j);
  adjacencyList->setEdge(i, j);
  incidenceMatrix->setEdge(i, j);
}

void Graph::printAll() {
  adjacencyMatrix->print();
  adjacencyList->print();
  incidenceMatrix->print();
}

void Graph::printAdjMat() { adjacencyMatrix->print(); }

void Graph::transpose() { adjacencyMatrix->transpose(); }

void DfsVisit(int nr, AdjacencyMatrix *adjMat, Dfs &node, int &time) {
  time = time + 1;
  node.startTime(time, nr);

  for (int j = 0; j < node.getSize(); j++) {

    if (adjMat->edgeExists(nr, j)) {
      if (node.getNodeDfs(j)._time == -1) {
        DfsVisit(j, adjMat, node, time);
      }
    }
  }
  time = time + 1;

  node.modifyNode(time, nr);
}

void compR(int nrComp, int nr, AdjacencyMatrix *adjMat, int *comp, int size) {

  for (int j = 0; j < size; j++) {

    if (adjMat->edgeExists(nr, j)) {
      if (comp[j] == -1) {
        comp[j] = nrComp;
        compR(nrComp, j, adjMat, comp, size);
      }
    }
  }
}

int *Graph::Kosaraju() {
  Dfs node(_size);
  int time = 0;

  for (int i = 0; i < _size; i++) {
    if (node.getNodeDfs(i)._time == -1) {
      DfsVisit(i, adjacencyMatrix, node, time);
    }
  }
  // node.print();
  std::cout << "\n\n";

  transpose();

  int *comp = new int[_size];

  for (int i = 0; i < _size; i++) {
    comp[i] = -1;
  }

  // sorter
  int *sortLast = new int[_size];
  int *sortNr = new int[_size];

  for (int i = 0; i < _size; i++) {
    sortLast[i] = node.getNodeDfs(i)._timeLast;
    sortNr[i] = i;
  }

  for (int k = 1; k < _size; k++) {
    int tempLast = sortLast[k];
    int tempNr = sortNr[k];
    int j = k - 1;
    while (j >= 0 && tempLast > sortLast[j]) {
      sortLast[j + 1] = sortLast[j];
      sortNr[j + 1] = sortNr[j];
      j = j - 1;
    }
    sortLast[j + 1] = tempLast;
    sortNr[j + 1] = tempNr;
  }

  int nr = 0;
  for (int i = 0; i < _size; i++) {
    if (comp[sortNr[i]] == -1) {
      nr = nr + 1;
      comp[sortNr[i]] = nr;
      compR(nr, sortNr[i], adjacencyMatrix, comp, _size);
    }
  }

  return comp;
}

struct Edge {
  int from;
  int to;
  int weight;
};

void Graph::addWeight(int a, int b) {
  std::srand(time(NULL));
  for (int i = 0; i < _size; i++) {
    for (int j = 0; j < _size; j++) {
      if (adjacencyMatrix->edgeExists(i, j)) {
        adjacencyMatrix->setWeight(i, j, rand() % (b - a + 1) + a);
      }
    }
  }
}

void Graph::prepareBellman(int a, int b) {
  transpose();
  addWeight(a, b);
}

bool Graph::BellmanFord(int src, int *distSrc, bool Johnson) {
  int verNr = adjacencyMatrix->getVertices();
  int edNr = adjacencyMatrix->getEdges();
  Edge *edges = new Edge[edNr];

  // Init
  int index = 0;
  for (int i = 0; i < verNr; i++) {
    distSrc[i] = INT_MAX;
    for (int j = 0; j < verNr; j++) {
      if (adjacencyMatrix->edgeExists(i, j)) {
        edges[index].from = i;
        edges[index].to = j;
        edges[index].weight = adjacencyMatrix->getWeight(i, j);
        index++;
      }
    }
  }
  distSrc[src] = 0;

  if (!Johnson)
  {
    printAll();
  }
  

  // Relaxation
  for (int i = 1; i <= verNr - 1; i++) {
    for (int j = 0; j < edNr; j++) {
      int u = edges[j].from;
      int v = edges[j].to;
      int weight = edges[j].weight;
      if (distSrc[u] != INT_MAX && distSrc[u] + weight < distSrc[v])
        distSrc[v] = distSrc[u] + weight;
    }
  }

  // negative edge
  for (int i = 0; i < edNr; i++) {
    int u = edges[i].from;
    int v = edges[i].to;
    int weight = edges[i].weight;
    if (distSrc[u] != INT_MAX && distSrc[u] + weight < distSrc[v]) {
      std::cout << "\n Istnieje negatywny cykl! "
                << "\n";
      return false;
    }
  }

  std::cout << "\n Wierzcholek   Odleglosc od " << src << "\n";
  for (int i = 0; i < verNr; ++i) {
    std::cout << "   " << i << "\t\t" << std::setw(2) << distSrc[i] << "\n";
  }

  delete[] edges;
  return true;
}

int minDist(int *dist, bool *shortestVer, int size) {
  int min = INT_MAX;
  int min_index = 0;

  for (int i = 0; i < size; i++) {
    if (shortestVer[i] == false && dist[i] <= min) {
      min = dist[i];
      min_index = i;
    }
  }
  return min_index;
}

int *Graph::Dijkstra(int src) {
  int *output = new int[_size];
  bool *shortestVer = new bool[_size];

  // Init
  for (int i = 0; i < _size; i++) {
    output[i] = INT_MAX;
    shortestVer[i] = false;
  }
  output[src] = 0;

  for (int k = 0; k < _size - 1; k++) {
    int i = minDist(output, shortestVer, _size);
    shortestVer[i] = true;

    for (int j = 0; j < _size; j++) {
      if (!shortestVer[j] && adjacencyMatrix->edgeExists(i, j) &&
          output[i] != INT_MAX &&
          output[i] + adjacencyMatrix->getWeight(i, j) < output[j])
        output[j] = output[i] + adjacencyMatrix->getWeight(i, j);
    }
  }
  return output;
}

int **Graph::Johnson(int src) {
  int *h = new int[_size + 1];
  Graph primGraph = Graph(_size + 1);
  for (int i = 0; i < _size; i++) {
    for (int j = 0; j < _size; j++) {
      if (adjacencyMatrix->edgeExists(i, j)) {
        primGraph.adjacencyMatrix->setEdge(i, j);
        primGraph.adjacencyMatrix->setWeight(i, j,
                                             adjacencyMatrix->getWeight(i, j));
      }
    }
  }

  for (int j = 0; j < _size; j++) {
    primGraph.adjacencyMatrix->setEdge(_size, j);
    primGraph.adjacencyMatrix->setWeight(_size, j, 0);
  }

  if (primGraph.BellmanFord(_size, h,true) == false) {
    return nullptr;
  } else {
    for (int i = 0; i < _size; i++) {
      for (int j = 0; j < _size; j++) {
        if (adjacencyMatrix->edgeExists(i, j)) {
          adjacencyMatrix->setWeight(
              i, j, adjacencyMatrix->getWeight(i, j) + h[i] - h[j]);
        }
      }
    }

    int **D;
    D = new int *[_size];
    for (int i = 0; i < _size; i++) {
      D[i] = new int[_size];

      for (int j = 0; j < _size; j++) {
        D[i][j] = INT_MAX;
      }
    }

    for (int i = 0; i < _size; i++) {
      int *du = Dijkstra(i);
      for (int j = 0; j < _size; j++) {
        D[i][j] = du[j] - h[i] + h[j];
      }
    }
    return D;
  }
}