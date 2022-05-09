#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Graph::Graph(std::string input)
{
	cout << "Wczytywanie danych z pliku: " << input << endl;
	ifstream wej(input);
	string line, graphicControl;
	int n = 0;
	
	getline(wej, line);
	graphicControl = line;
	++n;
	getline(wej, line);
	while(line != graphicControl && line != "")
	{
		++n;
		graphicControl = line;
		getline(wej, line);
	}
	_size = n;
	
	wej.close();
	wej.open("input.txt");
	getline(wej, line);
	graphicControl = line;
	
	adjacencyMatrix = new AdjacencyMatrix(_size);
	for(int i = 0; i < _size; ++i)
	{
		for(int j = i + 1; j < _size; ++j)
		{
			if(line[2 * j] == '1')
			adjacencyMatrix->setEdge(i, j);
		}
		getline(wej, line);
	}
	adjacencyMatrix->print();
}

void Graph::GoInside(int first, int current, bool* visited, int* stack, int _size)
{
	for(int i = 0; i < _size; ++i)
	{
		
		if(stack[i] == -1)
		{
			stack[i] = current;
			break;
		}
	}
	
	visited[current] = 1;
	
	for(int i = 0; i < _size; ++i)
		cout << stack[i] << " ";
	cout << endl;
	
	for(int i = 0; i < _size; ++i)
		cout << visited[i] << " ";
	cout << endl << endl;
	
	for(int i = 0; i < _size; ++i)
	{
		if(i == current)
			continue;
		
		if(adjacencyMatrix->edgeExists(i, current) && visited[i] == false)
		{
			bool graphicControl = true;
			
			GoInside(first, i, visited, stack, _size);
			
			if(stack[_size - 1] != -1)
			{
				if(adjacencyMatrix->edgeExists(first, stack[_size - 1]))
				{
					return;
				}
				else
				{
					visited[stack[_size - 1]] = 0;
					stack[_size - 1] = -1;
					break;
				}
			}
			else
			{
				for(int i = 0; i < _size; ++i)
				{
					if(stack[i] == -1)
					{
						visited[stack[i - 1]] = 0;
						stack[i - 1] = -1;
						break;
					}
				}
			}
		}
	}
}

string Graph::Hamilton()
{
	bool visited[_size];
	int stack[_size];
	string answer = "";
	
	for(int i = 0; i < _size; ++i)
	{
		cout << "Wierzcholek poczatkowy: " << i << endl;
		bool graphicControl = true;
		
		for(int j = 0; j < _size; ++j)
		{
			visited[j] = 0;
			stack[j] = -1;
		}
		
		GoInside(i, i, visited, stack, _size);
		cout << endl << endl;
		
		if(stack[_size - 1] != -1)
		{
			answer += "[";
			for(int j = 0; j < _size; ++j)
			{
				answer += to_string(stack[j]);
				answer += " - ";
			}
			answer += to_string(i);
			answer += "]";
			
			return answer;
		}
	}
	
	return "";
}

Graph::~Graph()
{
	delete adjacencyMatrix;
}


