#pragma once

//An abstract class for various graph representations
class GraphOptions
{
public:
	virtual ~GraphOptions() {} 

	//Wypisywanie grafu w formie liczbowej (macierze, lista)
	virtual void print() = 0;
	
	//Dodanie polaczenia pomiedzy wezlami n1 i n2
	virtual void setEdge(int n1, int n2) = 0;

	//Czy krawedz o zadanych koncach juz istnieje
	virtual int edgeExists(int n1, int n2) = 0;

	//Czy podane wezly moga stworzyc krawedz grafu (z uwzglednieniem warunkow zadanych na graf prosty), 1 że tak
	int checkVerticeGraph(int n1, int n2);

protected:
	int _vertices;
	int _edges;
	int**option;

};
