#pragma once

//An abstract class for various graph representations
class GraphOptions
{
public:
	virtual ~GraphOptions() {} 

	//Printing a graph
	virtual void print() = 0;
	
	// A method to add a connection between nodes n1 and n2
	virtual void setEdge(int n1, int n2) = 0;

	// Does the ending edge already exist
	virtual int edgeExists(int n1, int n2) = 0;

	// Method checking if given nodes can create graph edge if true 1
	int checkVerticesGraph(int n1, int n2);

protected:
	
	int _vertices;
	int _edges;
	int**Option;

};
