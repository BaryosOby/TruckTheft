#include "Graph.h"

Graph::Graph(int s):adjMatrix(s, vector<Warehouse>(s)), size(s) {
}

void Graph::addEdge(Warehouse f, Warehouse t, int weight) {

}

void Graph::addVertex(Warehouse v) {
    if(find(adjMatrix[0].begin(), adjMatrix[0].end(), v) != adjMatrix[0].end()){

    }
}

vector<Warehouse> Graph::dij(Warehouse from) {
    return vector<Warehouse>();
}
