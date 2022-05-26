#pragma once
#include "NodeDfs.h"
#include <vector>

class Dfs {
public:
  Dfs(int size);
  ~Dfs();
  void modifyNode(int lastTime, int nr);
  void print();
  NodeDfs getNodeDfs(int i);
  int getSize();
  void startTime(int timeStart, int nr);

private:
  int _curSize;
  std::vector<NodeDfs> _ptr;
};