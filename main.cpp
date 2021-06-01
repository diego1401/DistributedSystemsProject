// #include "Graph.hpp"
#include "graph_part.cpp"
#include "Dijkstra.h"
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

    // for(int i=0;i<gra->Nodes.size();i++){
    //     gra->Nodes[i]->print();
    //     std::cout << "Printing Neigh " ;
    //     for(int k=0;k<gra->Nodes[i]->Neighbors.size();k++){
    //         gra->Nodes[i]->Neighbors[k].print();
    //     }
    //     std::cout << std::endl;
    // }

    int* mat = Adj_Matrix(gra);
    // print_matrix(mat, gra->Nodes.size());
    unsigned int* d;
    Dijkstra dijk = Dijkstra(gra, 0);
    d = Sequential_Dijkstra_Two_Queue(gra, 0);
    dijk.compute();
    std::cout << "Original" << " ";
    dijk.print_dist();
    std::cout << std::endl;
    for(int i=0;i<6;i++){
        std::cout << d[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
