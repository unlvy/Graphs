cmake_minimum_required(VERSION 3.10)
project(proj-3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(proj-3 main.cpp Graph.cpp Graph.h AdjacencyMatrix.cpp AdjacencyMatrix.h AdjacencyList.cpp AdjacencyList.h IncidenceMatrix.cpp IncidenceMatrix.h GraphRepresentation.h UserInput.cpp UserInput.h)
