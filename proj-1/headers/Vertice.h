#pragma once

#include <string>

class Vertice {

public:
    Vertice(int index);
    ~Vertice() = default;
    int getIndex();
protected:
    int m_index;
};