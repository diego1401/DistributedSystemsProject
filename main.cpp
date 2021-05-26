// #include "Graph.hpp"
#include "graph_part.cpp"

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
    Graph* Gra;
    Gra = new Graph("Dataset/roadNet-CA.txt");
    Node* s;
    printf("%lu\n",Gra->Nodes.size());
    s = &Gra->Nodes[0];
    printf("Starting Dijkstra Two Q\n");
    int* d = Sequential_Dijkstra_Two_Queue(Gra,s);
    return 0;
}
