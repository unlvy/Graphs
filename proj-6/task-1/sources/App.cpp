#include "App.h"

void App::run() {

    int option;

    while(true) {
        option = printMenu();
        switch (option) {
        case 0:
            return;
        case 1:
            readGraph();
            break;
        case 2:
            randomWalkPageRank();
            break;
        case 3:
            powerIterationPageRank();
            break;
        default:
            break;
        }      
    }
}

void App::readGraph() {

    std::string filename;
    std::cout << " Please provide file name: ";
    std::cin.clear();
    std::getline(std::cin, filename);

    std::ifstream stream(filename);
    if (stream.is_open()) {

        m_adjList.clear();

        std::string line;
        std::vector<std::string> tokens;
        int pos;
        std::string vertice;

        while (std::getline(stream, line)) {

            pos = line.find(':');
            line.erase(std::remove(line.begin(), line.end(), ','), line.end());
            vertice = line.substr(0, pos);

            std::stringstream ss(line.substr(pos + 1));
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            tokens = std::vector<std::string>(begin, end);

            m_adjList[vertice] = tokens;
        }

        std::cout << "\nGraph read" << std::endl;
        stream.close();
        m_isGraphLoaded = true;
    } else {
        std::cerr << "\nFailed to open " << filename << std::endl;
    }
}

void App::randomWalkPageRank() {

    std::cout << "\n"
        "-----------------------------------\n"
        "-      Random Walk Page Rank      -\n"
        "-----------------------------------\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(RANGE_FROM, RANGE_TO);

    std::map<std::string, double> rank;
    std::string currentKey;
    std::map<std::string, std::vector<std::string>>::iterator it_map;
    std::vector<std::string>::iterator it_vec;

    for (auto const& [key, ignored]: m_adjList) {
        rank[key] = 0.0;
    }

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        if (i == 0 || ((static_cast<double>(distrib(gen)) / RANGE_TO) <= DAMPING_FACTOR) || m_adjList[currentKey].size() == 0) {

            it_map = m_adjList.begin();
            std::advance(it_map, distrib(gen) % m_adjList.size());
            currentKey = it_map->first;
            rank[currentKey] += 1.0 / NUM_ITERATIONS;

        } else {
            it_vec = m_adjList[currentKey].begin();
            std::advance(it_vec, distrib(gen) % m_adjList[currentKey].size());
            currentKey = *it_vec;
            rank[currentKey] += 1.0 / NUM_ITERATIONS;
        }
        
    }

    std::vector<std::pair<std::string, double>> result;
    for (const auto& element : rank) {
        result.emplace_back(element);
    }

    std::sort(result.begin(), result.end(),
        [] (const auto &a, const auto& b) { return a.second > b.second;});

    for(auto const& [key, value]: result) {
        std::cout << key << " rank: " << value << std::endl;
    }
}

void App::powerIterationPageRank() {

    std::cout << "\n"
        "-----------------------------------\n"
        "-    Power Iteration Page Rank    -\n"
        "-----------------------------------\n";
    
    int i, j;
    i = j = 0;
    int size = m_adjList.size();
    std::vector<std::vector<double>> stMatrix(size, std::vector(size, 0.0));
    std::vector<std::string> keys;
    for (auto const& [key, ignored]: m_adjList) { keys.push_back(key); }
    std::sort(keys.begin(), keys.end());

    for (auto [key, value] : m_adjList) {
        std::sort(value.begin(), value.end());

        for (int k = 0; k < size; k++) {
            if (value.size() == 0) {
                stMatrix[i][k] = 1.0 / static_cast<double>(size);  
                continue;
            } 

            if (value[j] == keys[k]) {
                j++;
                stMatrix[i][k] = 1.0 / static_cast<double>(value.size());
            } else {
                stMatrix[i][k] = 0.0;
            }
        }
        j = 0;
        i++;
    }

    std::vector<double> rank(size, 1.0 / static_cast<double>(size));
    std::vector<double> newRank(size, 1.0 / static_cast<double>(size));
    double val;
    int iter = 0;
    do {
        rank = newRank;
        for (int i = 0; i < size; i++) {
            val = 0.0;
            for (int j = 0; j < size; j++) {
                val += stMatrix[j][i] * rank[j];
            }
            newRank[i] = (1.0 - DAMPING_FACTOR) * val + DAMPING_FACTOR * 1.0 / static_cast<double>(size);
        }
        iter++;
    }
    while (std::sqrt(std::inner_product(rank.begin(), rank.end(), newRank.begin(), 0.0)) >= EPSILON && iter != 100);
    std::cout << "Number of iterations: " << iter << std::endl;

    std::vector<std::pair<std::string, double>> result;
    for (int i = 0; i < size; i++) {
        result.emplace_back(std::make_pair(keys[i], rank[i]));
    }

    std::sort(result.begin(), result.end(),
        [] (const auto &a, const auto& b) { return a.second > b.second;});

    for(auto const& [key, value]: result) {
        std::cout << key << " rank: " << value << std::endl;
    }
}

int App::printMenu() {
    std::cout << "\n"
        "-----------------------------------\n"
        "-     Project 6.1. Main menu      -\n"
        "-----------------------------------\n"
        "- Options:                        -\n"
        "-     1. Read graph from file     -\n"
        << (m_isGraphLoaded ? 
        "-     2. Random walk PageRank     -\n"
        "-     3. Power iteration PageRank -\n"
        : "") <<
        "-                                 -\n"
        "-     0. Exit                     -\n"
        "-----------------------------------\n"
        " Please choose option: ";
    
    int option;
    std::string input;
    std::cin.clear();
    std::getline(std::cin, input);
    try { option = std::stoi(input); }
    catch (std::exception& e) { option = -1; }
    while(option < 0 || option > (m_isGraphLoaded ? 3 : 1)) {
        std::cout << " Bad entry. Please try again: ";
        std::cin.clear();
        std::getline(std::cin, input);
        try { option = std::stoi(input); }
        catch (std::exception& e) { option = -1; }
    }
    return option;
}