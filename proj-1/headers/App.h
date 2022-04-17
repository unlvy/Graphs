#include "Graph.h"
#include "Vertice.h"
#include "Edge.h"
#include "GraphReader.h"
#include "GraphWriter.h"

class App {
public:
    App() = default;
    ~App();
    void run();
private:
    int printMenu();
    void readGraph();
    void printGraph();
    void exportToGv();

    GraphReader m_reader;
    GraphWriter m_writer;
    Graph* m_graph = nullptr;
    bool m_isGraphLoaded;
};
