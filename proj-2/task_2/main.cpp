#include <iostream>
#include "Graph.h"
#include "GraphReader.h"

using namespace std;

int main()
{
	int random;
	string input;

	std::cout << "\n"
        "-----------------------------------\n"
        "-      Read graph from file       -\n"
        "-----------------------------------\n"
        "- Options:                        -\n"
        "-     1. Read Adjacency Matrix    -\n"
        "-     2. Read Adjacency List      -\n"
        "-     3. Read Incidence Matrix    -\n"
		"-     4. Put Graph Sequence       -\n"
        "-                                 -\n"
        "-     0. Cancel                   -\n"
        "-----------------------------------\n"
        " Please choose option: ";
    
    int option;
    std::cin.clear();
    std::getline(std::cin, input);
    try { option = std::stoi(input); }
    catch (std::exception& e) { option = -1; }
    while(option < 0 || option > 4) {
        std::cout << " Bad entry. Please try again: ";
        std::cin.clear();
        std::getline(std::cin, input);
        try { option = std::stoi(input); }
        catch (std::exception& e) { option = -1; }
    }
    
    if (option == 0) { return 0; }

	Graph *m_graph;
	GraphReader m_reader;
    switch (option) {
    case 1:
		std::cout << "Please provide file name: ";
    	std::cin.clear();
    	std::getline(std::cin, input);
		m_graph = m_reader.readAdjacencyMatrix(input);
		cout << "Ilosc randomizacji: ";
		cin >> random;
        break;
    case 2:
		std::cout << " Please provide file name: ";
    	std::cin.clear();
    	std::getline(std::cin, input);
        m_graph = m_reader.readAdjacencyList(input);
		cout << "Ilosc randomizacji: ";
		cin >> random;
        break;
    case 3:
		std::cout << " Please provide file name: ";
    	std::cin.clear();
    	std::getline(std::cin, input);
		m_graph = m_reader.readIncidenceMatrix(input);
		cout << "Ilosc randomizacji: ";
		cin >> random;
        break;
	case 4:
		cout << "Podaj ciag: ";
    	std::cin.clear();
    	std::getline(cin, input);
		m_graph = new Graph(input);
		cout << "Ilosc randomizacji: ";
		cin >> random;
        break;
    default:
        return 0;
    }
	
	if(m_graph->IsGraphicSequence())
	{
		cout << "Jest ciagiem graficznym." << endl;
		m_graph->CreateGraph();
		m_graph->CreateVisualization("CreateVisualization1.dot");
		
		cout << "Podana liczba randomizacji grafu: " << random << endl;
		m_graph->Blend(random);
		m_graph->CreateVisualization("CreateVisualization2.dot");
	}
	else
	{
		cout << "Ciag nie jest ciagiem graficznym." << endl;
	}
	return 0;
}
