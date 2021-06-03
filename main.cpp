// #include "Graph.hpp"
#include "graph_part.cpp"
#include "Dijkstra/Dijkstra.h"
// int main(){
//     // Edge e1(0,1,2);
//     // Edge e2(1,2,3);
//     // Edge e3(2,3,4);
//     // Edge e4(3,0,1);
//     // Graph *G = new Graph();
//     // G->Nodes.push_back(0);
//     // G->Nodes.push_back(1);
//     // G->Nodes.push_back(2);
//     // G->Nodes.push_back(3);

//     // // G->Edges.push_back(e1);
//     // // G->Edges.push_back(e2);
//     // // G->Edges.push_back(e3);
//     // // G->Edges.push_back(e4);
//     // std::vector<Edge> E = {e1,e2,e3,e4};
//     // G->Edges = E;
    
//     // int * M = Adj_Matrix(G);
//     // print_matrix(M,G->Nodes.size());
//     // return 0;
//     //We create the graph

int main(){
    Graph *gra =  new Graph;
    gra->random_nodes(6,4);
    unsigned int* d;
    d = Sequential_Dijkstra_Two_Queue(gra, 0);

    int* mat = Adj_Matrix(gra);
    Dijkstra dijk = Dijkstra(gra, 0);
    dijk.compute();
    std::cout << "Original" << " ";
    dijk.print_dist();
    std::cout << std::endl;
    std::cout << "TwoQueue" << " ";
    for(int i=0;i<6;i++){
        std::cout << d[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
