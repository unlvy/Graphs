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

	//Metoda sprawdzajaca, czy podane wezly moga stworzyc krawedz grafu (z uwzglednieniem warunkow zadanych na graf prosty)
	// Zwraca 1, jesli wezly przeszly test i mozna stworzyc takie polaczenie
	int checkVerticesGraph(int n1, int n2);

protected:
	
	int _vertices;
	
	int _edges;
	
	int**Option;

};