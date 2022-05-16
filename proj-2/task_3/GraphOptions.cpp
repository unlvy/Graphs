#include <iostream>
#include "GraphOptions.h"

using namespace std;

int GraphOptions::checkVerticesGraph(int n1, int n2)
{
	if (n1 < 0 || n1 >= _vertices || n2 < 0 || n2 >= _vertices)
	{
		cout << "Nie ma takiego wezla. Nie dodano jednej z krawedzi.\n";
		return 0;
	}
	if (n1 == n2)
	{
		cout << "Graf prosty nie moze laczyc wezla z samym soba.\n";
		return 0;
	}
	if (edgeExists(n1, n2))
	{
		cout << "Krawedz juz istnieje\n";
		return 0;
	}
	return 1;
}