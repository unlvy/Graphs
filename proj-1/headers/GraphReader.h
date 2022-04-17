#pragma once

#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <map>

#include "Graph.h"

class GraphReader {

public:
    GraphReader() = default;
    ~GraphReader() = default;
    Graph* readAdjacencyMatrix(std::string filename);
    Graph* readAdjacencyList(std::string filename);
    Graph* readIncidenceMatrix(std::string filename);
private:
    void splitString(std::string str, std::vector<std::string>& tokens);

};
