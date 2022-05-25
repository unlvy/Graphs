#pragma once

#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "GraphOptions.h"
#include "IncidenceMatrix.h"
#include <string>

class Graph {
private:
  int _size = 0;
  AdjacencyList *adjacencyList = nullptr;
  AdjacencyMatrix *adjacencyMatrix = nullptr;
  IncidenceMatrix *incidenceMatrix = nullptr;
  void addEdge(int i, int j);
  void transpose();
  void addWeight(int a, int b);
  int *Dijkstra(int src);

public:
  Graph(int n);
  ~Graph();
  void CreateGraph(double p);
  void printAll();
  void printAdjMat();
  int *Kosaraju();
  void prepareBellman(int a, int b);
  bool BellmanFord(int src, int *distSrc, bool Johnson);
  int **Johnson(int src);
};
