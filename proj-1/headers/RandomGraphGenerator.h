#pragma once

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Graph.h"

class RandomGraphGenerator {

public:
    Graph* generate1(int n, int l);
    Graph* generate2(int n, double p);
};
