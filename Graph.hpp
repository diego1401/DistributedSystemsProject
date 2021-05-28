#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <stdlib.h>

//our classes
class Edge; class Node; class Graph;

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
    void print(){
        printf("Node(%d)\n",this->key);
    }
};

class Edge{
    public:
    Node* from;
    Node* to;
    int weight;
    Edge(){};
    Edge(Node* f,Node* t,int w){
        this->from = f; this->to = t; this->weight =w;
        // printf("Loading edge\n");
        // printf("%d,%d,%d\n",this->from->key,this->to->key,this->weight);
    }
};



class Graph{
    public:
    std::vector<Node> Nodes;
    std::vector<Edge> Edges;
    int number_nodes;
    Graph(){}
    Graph(std::string filename){
        this->number_nodes = 0;
        printf("Creating Graph\n");
        this->read_file(filename);
        printf("Done!\nFilling neighbors\n");
        this->fill_neighbors();
        printf("Done!\n");
    }

    void add_node(Node n){

        if(this->Nodes.empty()) {
           this->Nodes.push_back(n);
           this->number_nodes ++;
        //    printf("Node added!\n");
        }
        bool found = false;
        Node k;
        for(int i=0;i<this->Nodes.size();i++){
            k = this->Nodes[i];
            if(k.key == n.key){
                found = true;
                break;
            }
        }
        if(!found){
            this->number_nodes ++;
            this->Nodes.push_back(n);
            // printf("Node added!\n");
        } 
    }
    void fill_neighbors(){
        Edge e = Edges[0];
        for(int i=1;i<Edges.size();i++){
            e.from->Neighbors.push_back(e);
            e = Edges[i];
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
                this->add_node(*to);
                this->add_node(*from);
                w = rand() % MAX_WEIGHT + 1;
                e = Edge(from,to,w);
                this->Edges.push_back(e);
            }
            file.close();
        }
    }

    void random_nodes(int N, int maxweights){
        for (int i=0; i < N; i++){
            int maxl = rand()%(int)N/2 + 1;
            for (int j = 0; j < maxl; j++){
                int id1=0; int id2=0;
                while (id1 == id2){
                    id1 = rand()% N ; id2 = rand()%N ; 
                }
                int w = rand()%(maxweights) + 1;
                Node*to = new Node(id1); Node *from = new Node(id2);
                this->add_node(*to); this->add_node(*from);
                Edge e = Edge(from, to, w);
                this->Edges.push_back(e);
                std::cout << "From " << id2 << " to: " << id1 << " with weight " << w << std::endl;
            }
            // std::cout << "From " << id2 << " to: " << id1 << " with weight " << w << std::endl;
        }
        this->fill_neighbors();
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



