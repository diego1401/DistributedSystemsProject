#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

class Edge{
    public:
    Node* from;
    Node* to;
    int weight;
    Edge(Node* f,Node* t,int w){
        this->from = f; this->to = t; this->weight =w;
        printf("Loading edge\n");
        printf("%d,%d,%d\n",this->from,this->to,this->weight);
    }
};

class Node{
    public:
    int key;
    int status;
    bool in_queue;
    std::vector<Edge> Neighbors; //array of Edges so we can keep the weight
    Node(){
        this->status = 0;
    };
    Node(int k){
        this->key = k;
        //Unreached:0 ; temporarily labeled:1; perm labeled:2;
        this->status = 0;
        this->in_queue = false;
    }
};

class Graph{
    public:
    std::vector<Node> Nodes;
    std::vector<Edge> Edges;
    int number_nodes;
    
    //Maybe...
    // Graph(int _number_nodes){
    //     this->number_nodes = _number_nodes;
    //     for(int i=0;i<this->size;i++){
    //         add_node(i);
    //     }
    //  this->fill_neighbors();
    // }

    void add_node(int k){
        Node n(k);
        this->Nodes.push_back(n);
    }
    void fill_neighbors(){
        Edge e = Edges[0];
        for(int i=1;i<Edges.size();i++){
            Nodes[e.from->key].Neighbors.push_back(e);
            e = Edges[i];
        }
    }
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
       Matrix[G->Edges[i].to->key + n*G->Edges[i].from->key] = G->Edges[i].weight; 
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



