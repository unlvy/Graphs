#include "GraphReader.h"

Graph* GraphReader::readAdjacencyMatrix(std::string filename) {
    
    std::ifstream stream(filename);
    Graph* graph = new Graph();
    if (stream.is_open()) {

        std::string line;
        std::vector<std::string> tokens;
        std::vector<int> sequence;

        int numberOfLines=0;
        while (std::getline(stream, line)) {
            
            splitString(line, tokens);
            sequence.push_back(0);
            for(int j=numberOfLines+1;j<tokens.size();j++)
            {
                if (std::stoi(tokens[j])) {
                    sequence[numberOfLines] += std::stoi(tokens[j]);
                }
            }
            numberOfLines++;
            
        }
        graph->SetSize(sequence.size());
        graph->SetSeries(sequence);

        std::cout << "\nGraph read" << std::endl;
        stream.close();
        return graph;

    } else {
        std::cerr << "\nFailed to open " << filename << std::endl;
        return graph;
    }
}


Graph* GraphReader::readAdjacencyList(std::string filename) {

    std::ifstream plik(filename);
    Graph* graph = new Graph();
    if (plik.is_open()) {

        std::string line;
        std::vector<std::string> tokens;
        std::vector<int> sequence;

        int numberOfLines=0;
        while (std::getline(plik, line)) {
            
            splitString(line, tokens);
            sequence.push_back(0);
            for (std::string token : tokens) { 
                std::cout<<token;
                if (std::stoi(token)) {
                    sequence[numberOfLines]++;
                }
            }

            numberOfLines++;
        }
        
        graph->SetSize(sequence.size());
        graph->SetSeries(sequence);

        std::cout << "\nGraph read" << std::endl;
        plik.close();
        return graph;

    } else {
        std::cerr << "\nFailed to open " << filename << std::endl;
        return graph;
    }
}


Graph* GraphReader::readIncidenceMatrix(std::string filename) {

    std::ifstream stream(filename);
    Graph* graph = new Graph();
    if (stream.is_open()) {

        std::string line;
        std::vector<std::string> tokens;
        std::vector<int> sequence;

        int numberOfLines=0;
        while (std::getline(stream, line)) {
            
            splitString(line, tokens);
            sequence.push_back(0);
            for(std::string token: tokens)
            {
                if (std::stoi(token)) {
                    sequence[numberOfLines] += std::stoi(token);
                }
            }
            numberOfLines++;
        }

        graph->SetSize(sequence.size());
        graph->SetSeries(sequence);
        std::cout << "\nGraph read" << std::endl;
        stream.close();
        return graph;

    } else {
        std::cerr << "\nFailed to open " << filename << std::endl;
        return graph;
    }
}

void GraphReader::splitString(std::string str, std::vector<std::string>& tokens) {
    std::stringstream ss(str);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    tokens = std::vector<std::string>(begin, end);
}
