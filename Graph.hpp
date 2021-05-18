#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

class Edge{
    public:
    int from;
    int to;
    int weight;
    Edge(int f,int t,int w){
        this->from = f; this->to = t; this->weight =w;
        printf("Loading edge\n");
        printf("%d,%d,%d\n",this->from,this->to,this->weight);
    }
};

class Graph{
    public:
    std::vector<int> Nodes;
    std::vector<Edge> Edges;
    int num;
    // void read_file() // create function to read the file and fill the vectors
};

int* Adj_Matrix(Graph* G){
    int n = G->Nodes.size();
    int m = G->Edges.size();
    int* Matrix = (int*)malloc(n*n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) Matrix[i + j*n] = 0;
            else{
                Matrix[i + j*n] = -1;
            }
            
        }
    }
    for(int i=0;i<m;i++){
       printf("%d,%d,%d\n",G->Edges[i].from,G->Edges[i].to,G->Edges[i].weight);
       Matrix[G->Edges[i].to + n*G->Edges[i].from] = G->Edges[i].weight; 
    }
    return Matrix;
}

void print_matrix(int* Matrix,int n){

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            std::cout<< Matrix[i + j*n] << "  ";
        }
        std::cout << std::endl;
    }
}



