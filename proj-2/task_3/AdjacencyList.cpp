#include <iostream>
#include <cstdlib>
#include "AdjacencyList.h"

using namespace std;

AdjacencyList::~AdjacencyList()
{
	for (int i = 0; i < _vertices; i++)
	{
		if (nodeEdges[i] > 0)
			delete[] Option[i];
	}
	delete[] Option;
	delete[] nodeEdges;
}

AdjacencyList::AdjacencyList(int n)
{
	
	_vertices = n;
	_edges = 0;
	Option = new int*[n];
	
	
	nodeEdges = new int[n];
	for (int i = 0; i < n; i++)
	{
		nodeEdges[i] = 0;
	}
}

void AdjacencyList::setEdge(int n1, int n2)
{
	
	if (!checkVerticesGraph(n1, n2)) return;
		
	
	if(nodeEdges[n1] == 0)
	{
		Option[n1] = new int[1];
		Option[n1][0] = n2;
		nodeEdges[n1]++;
	}
	
	else
	{
		
		int * newArray = new int[nodeEdges[n1]+1];
		for(int i=0; i<nodeEdges[n1]; i++)
		{
			newArray[i] = Option[n1][i];
		}
		newArray[nodeEdges[n1]] = n2;
		delete[] Option[n1];
		Option[n1] = newArray;
		nodeEdges[n1]++;
	}

	if(nodeEdges[n2] == 0)
	{
		Option[n2] = new int[1];
		Option[n2][0] = n1;
		nodeEdges[n2]++;
	}

	else
	{
		int * newArray = new int[nodeEdges[n2]+1];
		for(int i=0; i<nodeEdges[n2]; i++)
		{
			newArray[i] = Option[n2][i];
		}
		newArray[nodeEdges[n2]] = n1;
		delete[] Option[n2];
		Option[n2] = newArray;
		nodeEdges[n2]++;
	}
	_edges++;

}

int AdjacencyList::edgeExists(int n1, int n2)
{
	if(nodeEdges[n1] == 0) return 0;
	else
	{
		for(int i=0; i<nodeEdges[n1]; i++)
		{
			if(Option[n1][i] == n2) return 1;
		}
		return 0;
	}
}

void AdjacencyList::print()
{
	cout << "-------------------\n";
	cout << "Lista sasiedztwa:\n";
	for(int i=0; i<_vertices; i++)
	{
		cout <<i <<": ";
		if (nodeEdges[i] == 0)
		{
			cout << "-\n";
			continue;
		}
		else
			for(int j=0; j<nodeEdges[i]; j++)
			{
				cout << Option[i][j] << " ";
			}
		cout << endl;

	}
	cout << "-------------------\n";
	

}