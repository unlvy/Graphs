#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

class App {
public:
    App() = default;
    ~App() = default;
    void run();
private:
    void readGraph();
    void randomWalkPageRank();
    void powerIterationPageRank();
    int printMenu();

    bool m_isGraphLoaded = false;
    std::map<std::string, std::vector<std::string>> m_adjList;

    const double DAMPING_FACTOR = 0.15;
    const double EPSILON = 1.0e-9;
    const int NUM_ITERATIONS = 1000000;
    const int RANGE_FROM = 0;
    const int RANGE_TO = 1000000;
};
