#include "App.h"

App::~App() {
    if (m_graph != nullptr) {
        delete m_graph;
    }
}

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
            randomGraph();
            break;
        case 3:
            printGraph();
            break;
        case 4:
            exportToGv();
            break;
        default:
            break;
        }      
    }
}

int App::printMenu() {
    std::cout << "\n"
        "-----------------------------------\n"
        "-      Project 1. Main menu       -\n"
        "-----------------------------------\n"
        "- Options:                        -\n"
        "-     1. Read graph from file     -\n"
        "-     2. Generate random graph    -\n"
        << (m_isGraphLoaded ? 
        "-     3. Print graph              -\n"
        "-     4. Export graph to .gv file -\n"
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
    while(option < 0 || option > (m_isGraphLoaded ? 4 : 2)) {
        std::cout << " Bad entry. Please try again: ";
        std::cin.clear();
        std::getline(std::cin, input);
        try { option = std::stoi(input); }
        catch (std::exception& e) { option = -1; }
    }
    return option;
}

void App::readGraph() {

    std::cout << "\n"
        "-----------------------------------\n"
        "-      Read graph from file       -\n"
        "-----------------------------------\n"
        "- Options:                        -\n"
        "-     1. Read Adjacency Matrix    -\n"
        "-     2. Read Adjacency List      -\n"
        "-     3. Read Incidence Matrix    -\n"
        "-                                 -\n"
        "-     0. Cancel                   -\n"
        "-----------------------------------\n"
        " Please choose option: ";
    
    int option;
    std::string input;
    std::cin.clear();
    std::getline(std::cin, input);
    try { option = std::stoi(input); }
    catch (std::exception& e) { option = -1; }
    while(option < 0 || option > 3) {
        std::cout << " Bad entry. Please try again: ";
        std::cin.clear();
        std::getline(std::cin, input);
        try { option = std::stoi(input); }
        catch (std::exception& e) { option = -1; }
    }
    
    if (option == 0) { return; }
    std::cout << " Please provide file name: ";
    std::cin.clear();
    std::getline(std::cin, input);

    if (m_graph != nullptr) { delete m_graph; }

    switch (option) {
    case 1:
        m_graph = m_reader.readAdjacencyMatrix(input);
        break;
    case 2:
        m_graph = m_reader.readAdjacencyList(input);
        break;
    case 3:
        m_graph = m_reader.readIncidenceMatrix(input);
        break;
    default:
        return;
    }
    m_isGraphLoaded = m_graph == nullptr ? false : true;
}

void App::randomGraph() {
    std::cout << "\n"
        "-----------------------------------\n"
        "-      Create random graph        -\n"
        "-----------------------------------\n"
        " Insert number of vertices: ";
    
    int n;
    std::string input;
    std::cin.clear();
    std::getline(std::cin, input);
    try { n = std::stoi(input); }
    catch (std::exception& e) { n = -1; }
    while(n < 0) {
        std::cout << " Bad entry. Please try again: ";
        std::cin.clear();
        std::getline(std::cin, input);
        try { n = std::stoi(input); }
        catch (std::exception& e) { n = -1; }
    }

    std::cout << "\n"
        "-----------------------------------\n"
        "-      Create random graph        -\n"
        "-----------------------------------\n"
        "- Options:                        -\n"
        "-     1. Number of edges          -\n"
        "-     2. Probability of edge      -\n"
        "-                                 -\n"
        "-     0. Cancel                   -\n"
        "-----------------------------------\n"
        " Please choose option: ";

    int option;
    std::cin.clear();
    std::getline(std::cin, input);
    try { option = std::stoi(input); }
    catch (std::exception& e) { option = -1; }
    while(option < 0 || option > 2) {
        std::cout << " Bad entry. Please try again: ";
        std::cin.clear();
        std::getline(std::cin, input);
        try { option = std::stoi(input); }
        catch (std::exception& e) { option = -1; }
    }

    switch (option) {
    case 0:
        return;
        
    case 1:
        int l;
        std::cout << " Please enter number: ";
        std::cin.clear();
        std::getline(std::cin, input);
        try { l = std::stoi(input); }
        catch (std::exception& e) { l = -1; }
        while(l < 0 || l > (n * (n - 1)) / 2) {
            std::cout << " Bad entry. Please try again: ";
            std::cin.clear();
            std::getline(std::cin, input);
            try { l = std::stoi(input); }
            catch (std::exception& e) { l = -1; }
        }
        if (m_graph != nullptr) { delete m_graph; }
        m_graph = m_rGenerator.generate1(n, l);
        break;

    case 2:
        double p;
        std::cout << " Please enter number: ";
        std::cin.clear();
        std::getline(std::cin, input);
        try { p = std::stod(input); }
        catch (std::exception& e) { l = -1; }
        while(p < 0.0 || p > 1.0) {
            std::cout << " Bad entry. Please try again: ";
            std::cin.clear();
            std::getline(std::cin, input);
            try { p = std::stod(input); }
            catch (std::exception& e) { p = -1.0; }
        }
        if (m_graph != nullptr) { delete m_graph; }
        m_graph = m_rGenerator.generate2(n, p);
        break;

    default:
        return;
    }

    if (m_graph != nullptr) { m_isGraphLoaded = true; }

}

void App::printGraph() {

    std::cout << "\n"
        "-----------------------------------\n"
        "-      Print graph                -\n"
        "-----------------------------------\n"
        "- Options:                        -\n"
        "-     1. Print Adjacency Matrix   -\n"
        "-     2. Print Adjacency List     -\n"
        "-     3. Print Incidence Matrix   -\n"
        "-                                 -\n"
        "-     0. Cancel                   -\n"
        "-----------------------------------\n"
        " Please choose option: ";
    
    int option;
    std::string input;
    std::cin.clear();
    std::getline(std::cin, input);
    try { option = std::stoi(input); }
    catch (std::exception& e) { option = -1; }
    while(option < 0 || option > 3) {
        std::cout << " Bad entry. Please try again: ";
        std::cin.clear();
        std::getline(std::cin, input);
        try { option = std::stoi(input); }
        catch (std::exception& e) { option = -1; }
    }
    
    if (option == 0) { return; }
    switch (option) {
    case 1:
        m_writer.writeAdjacencyMatrix(m_graph);
        break;
    case 2:
        m_writer.writeAdjacencyList(m_graph);
        break;
    case 3:
        m_writer.writeIncidenceMatrix(m_graph);
        break;
    default:
        return;
    }
}

void App::exportToGv() {
    std::cout << "\n"
        "-----------------------------------\n"
        "-      Export graph to .gv file   -\n"
        "-----------------------------------\n"
        " Please provide filename: ";
        std::string input;
        std::cin.clear();
        std::getline(std::cin, input);
        m_writer.exportToGv(m_graph, input);
}
