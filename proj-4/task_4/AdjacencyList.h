#pragma once
#include "GraphOptions.h"

class AdjacencyList : public GraphOptions {
public:
  AdjacencyList(int node);
  ~AdjacencyList();
  void setEdge(int n1, int n2);
  int edgeExists(int n1, int n2);
  void print();

private:
  int *nodeEdges;
};
