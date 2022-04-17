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
