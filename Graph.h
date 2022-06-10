#ifndef EXC03_GRAPH_H
#define EXC03_GRAPH_H
#include <vector>
#include <memory>
#include "Warehouse.h"
#include <algorithm>

using namespace std;


class Graph {
private:
    vector<vector<Warehouse>> adjMatrix;
    int size;


public:
    Graph(int s);
    void addEdge(Warehouse f, Warehouse t, int weight);
    void addVertex(Warehouse v);
    vector<Warehouse> dij(Warehouse from);


};



#endif
