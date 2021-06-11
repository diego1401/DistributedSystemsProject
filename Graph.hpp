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
    //For the Graph Partioning Library
    idx_t *xadj;
    idx_t *adjncy;
    idx_t *adjwgt; //WEIGHTS MUST BE GREATER THAN 0
    Graph(){};

    Graph(std::string filename){
        this->number_nodes = 0;
        printf("Creating Graph\n");
        this->read_file(filename);
        printf("Done!\nFilling neighbors\n");
        this->fill_neighbors();
        printf("Done!\nFilling METIS values");
        this->fill_METIS_values();
        printf("Done\n");
    }

    ~Graph(){
        free(xadj);
        free(adjncy);
        free(adjwgt);
    }

    Node* ret_node_at(int key){
        for(int i=0;i<this->Nodes.size();i++){
            if(this->Nodes[i]->key == key) return this->Nodes[i];
        }
        return NULL;
    }

    bool contains(int key){
        return ret_node_at(key)!= NULL;
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
            int lines_to_skip = 0;
            std::string line;
            for(int j=0;j<lines_to_skip;j++){
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

    void fill_METIS_values(){
        xadj = (idx_t*) malloc((this->number_nodes+1)*sizeof(idx_t));
        //Only store Edges.size() because we are using weights we store
        // (u,v) and (v,u) Independently 
        adjncy = (idx_t*) malloc(Edges.size() * sizeof(idx_t));
        adjwgt = (idx_t*) malloc(Edges.size() * sizeof(idx_t));
        //vwgt = to be done...

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
    int key;
    Graph* Main_Graph;

    std::vector<Node*> BoundaryNodes; //Boundary Nodes are node from the main graph
    //that link this Subgraph with other subgraphs
    
    void UpdateBoundaryNodes(){
        for(int i=0;i<this->number_nodes;i++){
            Node* curr_node = this->Main_Graph->Nodes[i];
            std::vector<Edge> Neighbors = curr_node->Neighbors;
            for(int j=0;j<Neighbors.size();j++){
                //As contains searches for a key, it does not matter that the nodes in 
                // this->Nodes and Main_Graph->Nodes are not the same
                if(!this->contains(Neighbors[j].to->key)){
                    this->BoundaryNodes.push_back(curr_node);
                    //We now know it is a Boundary Node
                    break;
                }
            }
        }
    }

    SubGraph(Graph* _Main_G,idx_t* part,int _key){
        this->number_nodes = 0;
        this->key = _key;
        this->Main_Graph = _Main_G;
        // std::cout << "SubGraph: " << this->key << std::endl;
        //we add only the Edges that involve nodes of the subgraph
        for(int i=0;i<_Main_G->Edges.size();i++){
            //The associated k of the nodes has to be the same as for the graph
            int key_from = _Main_G->Edges[i].from->key;
            int key_to = _Main_G->Edges[i].to->key;
            // std::cout << key_from << "->" << key_to << "(" <<part[key_from] << "," << part[key_to] << ")";
            if(part[key_from] == this-> key &&
               part[key_to]   == this-> key){
                //    std::cout << "added!" ;
                   Node*to = new Node(key_to);
                   Node*from = new Node(key_from);
                   if(this->add_node(to)){
                       to = this->ret_node_at(key_to);
                   };

                   if(this->add_node(from)){
                       from = this->ret_node_at(key_from);
                   };
                   Edge e(from,to,_Main_G->Edges[i].weight);
                   this->Edges.push_back(e);

               }
            // std::cout << std::endl;
        }
        //Fill neighbors
        this->fill_neighbors();
        //Update the Boundary Nodes
        this->UpdateBoundaryNodes();

    }


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


