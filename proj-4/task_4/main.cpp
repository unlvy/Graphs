#include "Graph.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

int main() {
  std::cout << "\n Insert number of vertices: ";

  int n;
  std::string input;
  std::cin.clear();
  std::getline(std::cin, input);
  try {
    n = std::stoi(input);
  } catch (std::exception &e) {
    n = -1;
  }

  while (n < 0) {
    std::cout << " Bad entry. Try again: ";
    std::cin.clear();
    std::getline(std::cin, input);
    try {
      n = std::stoi(input);
    } catch (std::exception &e) {
      n = -1;
    }
  }

  double p;
  std::cout << " Enter probability: ";
  std::cin.clear();
  std::getline(std::cin, input);
  try {
    p = std::stod(input);
  } catch (std::exception &e) {
    p = -1;
  }

  while (p < 0.0 || p > 1.0) {
    std::cout << " Bad entry. Try again: ";
    std::cin.clear();
    std::getline(std::cin, input);
    try {
      p = std::stod(input);
    } catch (std::exception &e) {
      p = -1.0;
    }
  }

  Graph graph(n);
  graph.CreateGraph(p);
  graph.printAll();

  std::cout << "\n Nacisnij enter by kontynuowac";
  std::cin.ignore();
  std::cout << "\n--------------------";

  int *comp;
  comp = graph.Kosaraju();

  int index = 0;
  bool strong = true;
  while (strong && index != n) {
    if (comp[index] != 1) {
      strong = false;
    }
    index++;
  }

  if (!strong) {
    std::cout << "\n Znalezione silnie spojne skladowe:";

    int *maxNr = std::max_element(comp, comp + n);

    for (int i = 1; i <= *maxNr; i++) {
      std::cout << "\n" << i << ": ";
      for (int j = 0; j < n; j++) {
        if (comp[j] == i) {
          std::cout << j << " ";
        }
      }
    }
    std::cout << "\n\n";
  } else {
    std::cout << "\n Podany digraf jest silnie spojny! \n";
    std::cout << "\n Nacisnij enter by kontynuowac";
    std::cin.ignore();
    std::cout << "\n--------------------";

    graph.prepareBellman(-5, 10);

    int *dist = new int[n];
    bool pos_cycle = graph.BellmanFord(0, dist, false);

    if (pos_cycle == true) {
      std::cout << "\n\n Nacisnij enter by kontynuowac";
      std::cin.ignore();
      std::cout << "\n--------------------";
      int **resultJohn = nullptr;
      resultJohn = graph.Johnson(0);

      std::cout << "\n\n";
      std::cout << "--------------------\n";
      std::cout << "Macierz odleglosci: \n";
      if (resultJohn != nullptr) {
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            std::cout << " " << std::setw(3) << resultJohn[i][j];
          }
          std::cout << std::endl;
        }
      }
      std::cout << "--------------------";
      std::cout << "\n\n";
    }
  }

  return 0;
}
