#pragma once

// An abstract class for various graph representations
class GraphOptions {
public:
  virtual ~GraphOptions() {}

  // Plotting a graph in numerical form (matrices, list)
  virtual void print() = 0;

  // Adding a link between nodes n1 and n2
  virtual void setEdge(int n1, int n2) = 0;

  // Does the edge with the given ends already exist
  virtual int edgeExists(int n1, int n2) = 0;

  // Can the given nodes create the edge of the graph (taking into account the
  // conditions given for a simple graph), 1 that yes
  int checkVerticeGraph(int n1, int n2);

protected:
  int _vertices;
  int _edges;
  int **option;
};
