#include "AdjacencyMatrix.h"
#include <iomanip>
#include <iostream>

using namespace std;

AdjacencyMatrix::~AdjacencyMatrix() {
  for (int i = 0; i < _vertices; i++) {
    delete[] option[i];
    delete weightMatrix[i];
  }
  delete[] option;
  delete weightMatrix;
}

AdjacencyMatrix::AdjacencyMatrix(int n) {
  _vertices = n;
  _edges = 0;
  option = new int *[n];
  weightMatrix = new int *[n];
  for (int i = 0; i < n; i++) {
    option[i] = new int[n];
    weightMatrix[i] = new int[n];
    for (int j = 0; j < n; j++) {
      option[i][j] = 0;
      weightMatrix[i][j] = 0;
    }
  }
}

void AdjacencyMatrix::setEdge(int n1, int n2) {
  if (!checkVerticeGraph(n1, n2))
    return;

  option[n1][n2] = 1;
  weightMatrix[n1][n2] = 1;
  _edges++;
}

int AdjacencyMatrix::setWeight(int n1, int n2, int value) {
  weightMatrix[n1][n2] = value;
  return value;
}

int AdjacencyMatrix::edgeExists(int n1, int n2) {
  if (option[n1][n2] != 0)
    return 1;
  else
    return 0;
}

int AdjacencyMatrix::getWeight(int n1, int n2) { return weightMatrix[n1][n2]; }

int AdjacencyMatrix::getEdges() { return _edges; }
int AdjacencyMatrix::getVertices() { return _vertices; }

void AdjacencyMatrix::print() {
  cout << "------------------------------------------\n";
  cout << "Macierz sasiedztwa:";
  cout << "\tMacierz wag:\n";
  for (int i = 0; i < _vertices; i++) {
    for (int j = 0; j < _vertices; j++) {
      cout << setw(2) << option[i][j] << " ";
    }
    cout << "\t\t";
    for (int j = 0; j < _vertices; j++) {
      cout << setw(2) << weightMatrix[i][j] << " ";
    }

    cout << endl;
  }
  cout << "------------------------------------------\n";
}

void AdjacencyMatrix::transpose() {
  int **tempTranspose;
  tempTranspose = new int *[_vertices];
  for (int i = 0; i < _vertices; i++) {
    tempTranspose[i] = new int[_vertices];
  }

  for (int i = 0; i < _vertices; ++i)
    for (int j = 0; j < _vertices; ++j) {
      tempTranspose[j][i] = option[i][j];
    }

  option = tempTranspose;
}