#include "Dfs.h"
#include <iostream>

Dfs::Dfs(int size) {
  for (int i = 0; i < size; i++) {
    _ptr.push_back(NodeDfs(-1, -1, 0));
  }
  _curSize = 0;
}

Dfs::~Dfs() {}

void Dfs::modifyNode(int timeLast, int nr) {
  _ptr[nr]._nr = nr;
  _ptr[nr]._timeLast = timeLast;
  _curSize++;
}

void Dfs::print() {
  std::cout << std::endl;
  for (int i = 0; i < _curSize; i++) {
    std::cout << " " << _ptr[i]._nr << "," << _ptr[i]._time << "-"
              << _ptr[i]._timeLast << "\n";
  }
}

NodeDfs Dfs::getNodeDfs(int i) { return _ptr[i]; }

int Dfs::getSize() { return _ptr.size(); }

void Dfs::startTime(int timeStart, int nr) { _ptr[nr]._time = timeStart; }