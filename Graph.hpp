#pragma once
#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <queue>
#include <limits>
#include <map>
#include <thread>
#include <assert.h>   
#include <cstddef> /* NULL */
#include <metis.h> 
#include <mutex>
#include <atomic>   
#include <condition_variable>
#include <chrono>
#include <functional>
#include <numeric>
#include<iostream>
#include<algorithm>
#include <vector>
#include<math.h>
#include <climits>
#include <iostream>
#include <fstream>
using namespace std::chrono;

//our classes
class Edge; class Node; class Graph; class SubGraph;

class Node{
    public:
    int key;
    std::vector<Edge> Neighbors; //array of Edges so we can keep the weight
    
    Node(){
    };

    Node(int k){
        this->key = k;
    }

    void print(){
        printf("Node(%d)\n",this->key);
    }
    
};

class Edge{
    public:
    Node* from; Node* to;unsigned int weight;

    Edge(){};

    Edge(Node* f,Node* t,unsigned int w){
        this->from = f; this->to = t; this->weight =w;
    }
    void print(){
        std::cout << this->from->key << "->" << this->to->key << "w = " << this->weight << std::endl;
    }
};

class Graph{
    public:
    std::vector<Node*> Nodes;
    std::vector<Edge> Edges;
    int number_nodes;
    //For the Graph Partioning Library
    idx_t *xadj; idx_t *adjncy; idx_t *adjwgt; //WEIGHTS MUST BE GREATER THAN 0
    Graph(){};

    Graph(int N){
        this->number_nodes = N;
        for(int i=0;i<this->number_nodes;i++){
            this->Nodes.push_back(new Node(i));
        }

    };

    ~Graph(){
        free(xadj);
        free(adjncy);
        free(adjwgt);
    }

    Node* ret_node_at(int key){
        return this->Nodes[key];
    }

    bool contains(int key){
        return ret_node_at(key)!= NULL;
    }

    void fill_neighbors(){
        for(int i=0;i<this->Edges.size();i++){
            // this->Edges[i].print();
            this->Edges[i].from->Neighbors.push_back(this->Edges[i]);
        }
    }

    void random_nodes(int N,unsigned int maxweights){
        //Give Random Weights to their edges
        unsigned int w;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(i==j) continue;
                w = rand()%N + 1; 
                double coin = (double) rand()/RAND_MAX;
                if (coin > 0.1) continue;
                Node* from = this->ret_node_at(i);
                Node* to = this->ret_node_at(j);
                Edge e(from,to,w);
                this->Edges.push_back(e);
            }
        }

        this->fill_neighbors();

    }

    void fill_METIS_values(){
        xadj = (idx_t*) malloc((this->number_nodes+1)*sizeof(idx_t));
        //Only store Edges.size() because we are using weights we store
        // (u,v) and (v,u) Independently 
        adjncy = (idx_t*) malloc(Edges.size() * sizeof(idx_t));
        adjwgt = (idx_t*) malloc(Edges.size() * sizeof(idx_t));

        //We iterate over the nodes, and over its neighbors
        //because we need to store indep (u,v) and (v,u)
        xadj[0] = 0;
        for(int i=0;i<this->number_nodes;i++){
            Node* curr_node = ret_node_at(i);
            std::vector<Edge> Neighbors = curr_node->Neighbors;
            for(int j=0;j<Neighbors.size();j++){
                adjncy[xadj[i]+j] = Neighbors[j].to->key;
                adjwgt[xadj[i]+j] = Neighbors[j].weight;
            }
            xadj[i+1] = xadj[i] + Neighbors.size();
        }
    }

    void print_METIS(){
        std::cout << "xajd = ";
        for(int i=0;i<this->number_nodes;i++){
            std::cout << this->xadj[i] << ", ";
        }
        std::cout << this->xadj[this->number_nodes] << std::endl;

        std::cout << "adjncy = ";
        for(int i=0;i<this->Edges.size();i++){
            
            std::cout << this->adjncy[i];
            if(i!= this->Edges.size()-1) std::cout << ", ";
        }
        std::cout << std::endl;
        std::cout << "adjwgt = ";
        for(int i=0;i<this->Edges.size();i++){
            
            std::cout << this->adjwgt[i];
            if(i!= this->Edges.size()-1) std::cout << ", ";
        }
        std::cout << std::endl;
    }

    void print_nodes(){
        std::cout << "Nodes :" << std::endl;
        for(int i=0;i<this->Nodes.size();i++){
            this->Nodes[i]->print();
            std::cout <<  ",";
        }
        std::cout << std::endl;
    }
};

class SubGraph: public  Graph{
    public:
    int key; Graph* Main_Graph;
    std::vector<bool> BoundaryNodes; //Boundary Nodes are node from the main graph
    //that link this Subgraph with other subgraphs
    
    SubGraph(Graph* _Main_G,idx_t* part,int _key){
        this->key = _key;
        this->Main_Graph = _Main_G;
        this->number_nodes = this->Main_Graph->number_nodes;
        this->Nodes = this->Main_Graph->Nodes;
        std::vector<bool> BoundaryNodestmp(this->number_nodes);
        //It is useful to identify the Boundary Nodes
        for(int i=0;i<_Main_G->Edges.size();i++){
            int key_from = _Main_G->Edges[i].from->key;
            int key_to = _Main_G->Edges[i].to->key;

            if(part[key_from] == this-> key){
                BoundaryNodestmp[key_from] = true;
            }
            else if(part[key_to] == this-> key){
                BoundaryNodestmp[key_to] = true;
            }
        }
        this->BoundaryNodes = BoundaryNodestmp;

    }
};

int index(int x, int y, int n){
    return x + n*y;
}

unsigned int *Adj_Matrix(Graph* G){
    int n = G->Nodes.size();
    int m = G->Edges.size();
    // int* Matrix = (int*)malloc(n*n);
    unsigned int *Matrix = new unsigned int[n*n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) Matrix[index(i,j,n)] = 0;
            else{
                Matrix[index(i,j,n)] = std::numeric_limits<unsigned int>::max();
            }
            
        }
    }
    for(int i=0;i<m;i++){
        Matrix[index(G->Edges[i].from->key,G->Edges[i].to->key,n)] = G->Edges[i].weight; 
    }
    return Matrix;
}

void print_matrix(unsigned int* Matrix,int n){

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            std::cout<< Matrix[i + j*n] << "  ";
        }
        std::cout << std::endl;
    }
}


