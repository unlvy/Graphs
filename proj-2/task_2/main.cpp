#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	int random;
	string input;

	Graph *m_graph;
	cout << "Podaj ciag: ";
	std::cin.clear();
	std::getline(cin, input);
	m_graph = new Graph(input);
	cout << "Ilosc randomizacji: ";
	cin >> random;
	
	if(m_graph->IsGraphicSequence())
	{
		cout << "Jest ciagiem graficznym." << endl;
		m_graph->CreateGraph();
		m_graph->CreateVisualization("drawgraph1.dot");
		
		cout << "Podana liczba randomizacji grafu: " << random << endl;
		m_graph->Blend(random);
		m_graph->CreateVisualization("drawgraph2.dot");
	}
	else
	{
		cout << "Ciag nie jest ciagiem graficznym." << endl;
	}
	return 0;
}
