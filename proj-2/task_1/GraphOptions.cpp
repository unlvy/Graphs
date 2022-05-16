#include <iostream>
#include "GraphOptions.h"

using namespace std;

int GraphOptions::checkVerticeGraph(int n1, int n2)
{
	if (n1 < 0 || n1 >= _vertices || n2 < 0 || n2 >= _vertices)
	{
		return 0;
	}
	if (n1 == n2)
	{
		return 0;
	}
	if (edgeExists(n1, n2))
	{
		return 0;
	}
	return 1;
}
