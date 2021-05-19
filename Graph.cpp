#include "Graph.hpp"


int main(){
    Edge e1(0,1,2);
    Edge e2(1,2,3);
    Edge e3(2,3,4);
    Edge e4(3,0,1);
    Graph *G = new Graph();
    G->Nodes.push_back(0);
    G->Nodes.push_back(1);
    G->Nodes.push_back(2);
    G->Nodes.push_back(3);

    // G->Edges.push_back(e1);
    // G->Edges.push_back(e2);
    // G->Edges.push_back(e3);
    // G->Edges.push_back(e4);
    std::vector<Edge> E = {e1,e2,e3,e4};
    G->Edges = E;
    
    int * M = Adj_Matrix(G);
    print_matrix(M,G->Nodes.size());
    return 0;
}
