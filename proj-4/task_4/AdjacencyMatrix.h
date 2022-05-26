#pragma once
#include "GraphOptions.h"

class AdjacencyMatrix : public GraphOptions {
public:
  AdjacencyMatrix(int n);
  ~AdjacencyMatrix();
  void setEdge(int n1, int n2);
  int setWeight(int n1, int n2, int value);
  int edgeExists(int n1, int n2);
  int getWeight(int n1, int n2);
  void print();
  void transpose();
  int getEdges();
  int getVertices();

private:
  int **weightMatrix;
};