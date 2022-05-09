#include <iostream>
#include <ctime>
#include <sstream>
#include "Graph.h"

using namespace std;


int main()
{
	int n;
	string vertices;
	srand(time(NULL));
	
	cout << "Podaj ilość wierzchołków: ";
	//cin >> n;
	std::string number;
	getline(std::cin, number);

	if (number.empty() || !is_number(number)) {
    	n =( std::rand() % 20 ) + 3;
	}else{
		n = stoi(number);
	}

	vertices = eulerianVertices(n);

	Graph graph(vertices);

	if(graph.IsGraphicSequence())
	{
		cout << "Podany ciag jest ciagiem graficznym." << endl;
		graph.CreateGraph();
		graph.CreateVisualization("output1.dot");
		
		cout << "-------------------\n";
		cout << "Znaleziony cykl Eulera:\n";
		graph.findEulerianCircuit();
		cout << "\n-------------------\n";

	}
	else
	{
		cout << "Podany ciag nie jest ciagiem graficznym." << endl;
	}
    
	return 0;
}