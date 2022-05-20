#pragma once
#include "GraphOptions.h"

class IncidenceMatrix : public GraphOptions
{
public:
	IncidenceMatrix(int n);
	~IncidenceMatrix();
	void setEdge(int n1, int n2);
	int edgeExists(int n1, int n2);
	void print();
};