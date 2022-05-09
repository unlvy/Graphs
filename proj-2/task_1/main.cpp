#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	int random;
	string data;

	cout << "Podaj ciag liczb: ";
	getline(cin, data);
	cout << "Podaj randomizację: ";
	cin >> random;
	
	Graph graph(data);
	if(graph.IsGraphicSequence())
	{
		cout << "Ciag jest graficzny." << endl;
		graph.CreateGraph();
		graph.CreateVisualization("CreateVisualization1.dot");
		
		cout << "Podana liczba randomizacji grafu: " << random << endl;
		graph.Blend(random);
		graph.CreateVisualization("CreateVisualization2.dot");
	}
	else
	{
		cout << "Ciag nie jest graficzny." << endl;
	}
	return 0;
}
