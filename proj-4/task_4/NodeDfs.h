#pragma once

class NodeDfs {
public:
  NodeDfs(int time, int timeLast, int nr) {
    _time = time;
    _timeLast = timeLast;
    _nr = nr;
  }
  int _time;
  int _timeLast;
  int _nr;
};