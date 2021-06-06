#pragma once
#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
// #include "Dijkstra.h"

//our classes
class Edge; class Node; class Graph;

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
    Node* from; Node* to;int weight;

    Edge(){};

    Edge(Node* f,Node* t,int w){
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
    Graph(){};

    Graph(std::string filename){
        this->number_nodes = 0;
        printf("Creating Graph\n");
        this->read_file(filename);
        printf("Done!\nFilling neighbors\n");
        this->fill_neighbors();
        printf("Done!\n");
    }

    Node* ret_node_at(int key){
        for(int i=0;i<this->Nodes.size();i++){
            if(this->Nodes[i]->key == key) return this->Nodes[i];
        }
        return NULL;
    }

    bool add_node(Node* n){

        if(this->Nodes.empty()) {
           this->Nodes.push_back(n);
           this->number_nodes ++;
        //    printf("Node added!\n");
        }
        bool found = false;
        Node* k;
        for(int i=0;i<this->Nodes.size();i++){
            k = this->Nodes[i];
            if(k->key == n->key){
                found = true;
                return true;
            }
        }
        if(!found){
            this->number_nodes ++;
            this->Nodes.push_back(n);
            return false;
            // printf("Node added!\n");
        } 
        return false;
    }

    void fill_neighbors(){
        for(int i=0;i<this->Edges.size();i++){
            // this->Edges[i].print();
            this->Edges[i].from->Neighbors.push_back(this->Edges[i]);
        }
    }

    void read_file(std::string filename){
        int MAX_WEIGHT = 10000;
        std::ifstream file(filename);
        if (file.is_open()) {
            //get rid of useless lines
            std::string line;
            for(int j=0;j<4;j++){
                std::getline(file,line);
            }
            Node* to,*from;
            Edge e;
            int id1,id2,w;
            while (file >> id1 >> id2) {
                to = new Node(id1);
                from = new Node(id2);
                this->add_node(to);
                this->add_node(from);
                w = rand() % MAX_WEIGHT + 1;
                e = Edge(from,to,w);
                this->Edges.push_back(e);
            }
            file.close();
        }
    }

    void random_nodes(int N, int maxweights){
        //Add N Nodes
        for(int i=0;i<N;i++){
            Node*node = new Node(i);
            this->add_node(node);
        }
        //Give Random Weights to their edges
        int w;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                w = rand()%N + 1; 
                if(i==j) continue;
                Node* from = this->ret_node_at(i);
                Node* to = this->ret_node_at(j);
                Edge e(from,to,w);
                this->Edges.push_back(e);
            }
        }

        this->fill_neighbors();

    }

        // for (int i=0; i < N; i++){
        //     int maxl = rand()%(int)N/2 + 1;
        //     for (int j = 0; j < maxl; j++){
        //         int id1=0; int id2=0;
        //         while (id1 == id2){
        //             id1 = rand()% N ; id2 = rand()%N ; 
        //         }
        //         int w = rand()%(maxweights) + 1;
        //         Node*to = new Node(id1); Node *from = new Node(id2);
        //         bool found1,found2;
        //         found1 = this->add_node(to); found2 = this->add_node(from);
        //         if(found1) to = this->ret_node_at(to->key);
        //         if(found2) from = this->ret_node_at(from->key);
        //         Edge e = Edge(from, to, w);
        //         this->Edges.push_back(e);
        //         // std::cout << "From " << id2 << " to: " << id1 << " with weight " << w << std::endl;
        //     }
        //     // std::cout << "From " << id2 << " to: " << id1 << " with weight " << w << std::endl;
        // }
        // // std::cout << "filling neighbors " << std::endl;
        // this->fill_neighbors();
        // std::cout << "checking they are there "<< std::endl;
        // for(int i=0;i<this->Nodes.size();i++){
        //     this->Nodes[i]->print();
        //     std::cout << "Printing Neigh " ;
        //     for(int k=0;k<this->Nodes[i]->Neighbors.size();k++){
        //         this->Nodes[i]->Neighbors[k].print();
        //     }
        //     std::cout << std::endl;
        // }

};

int index(int x, int y, int n){
    return x + n*y;
}

int *Adj_Matrix(Graph* G){
    int n = G->Nodes.size();
    int m = G->Edges.size();
    // int* Matrix = (int*)malloc(n*n);
    int *Matrix = new int[n*n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) Matrix[index(i,j,n)] = 0;
            else{
                Matrix[index(i,j,n)] = -1;
            }
            
        }
    }
    for(int i=0;i<m;i++){
    //    printf("%d,%d,%d\n",G->Edges[i].from->key,G->Edges[i].to->key,G->Edges[i].weight);
    //    Matrix[G->Edges[i].from->key + n*G->Edges[i].to->key] = G->Edges[i].weight; 
        Matrix[index(G->Edges[i].from->key,G->Edges[i].to->key,n)] = G->Edges[i].weight; 
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



