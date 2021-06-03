#pragma once
#include"Graph.hpp"
#include <queue>
#include <limits>
#include <map>
#include <assert.h>    
//First we implement the sequential version of the algorithm described in the paper

class TwoQueue{
    public:
    std::queue<Node*> Q_pp;
    std::queue<Node*> Q_p;
    //Unreached:0 ; temporarily labeled:1; perm labeled:2;
    std::map<int,int> status;
    std::map<int,bool> in_queue;
    TwoQueue(){};

    void insert(Node* j){
        if(!this->in_queue[j->key]){
            //Unreached
            this->in_queue[j->key] = 1;
            if(this->status[j->key]==0){
                this->status[j->key] = 1;
                this->Q_p.push(j);
            } 
            //tmp labeled
            else if(this->status[j->key]==1) this->Q_pp.push(j);
        }
    }

    Node* remove(){
        if(!this->Q_pp.empty()){
            Node*j = this->Q_pp.front();
            this->in_queue[j->key] = 0;
            this->Q_pp.pop();
            return j;
        }
        if(!this->Q_p.empty()){
            Node*j = this->Q_p.front();
            this->in_queue[j->key] = 0;
            this->Q_p.pop();
            return j;
        }
        Node* empty;
        empty = new Node();
        return empty; //should never come here
    }

    bool is_empty(){
    return Q_pp.empty() && Q_p.empty();
    }
};

void print_dist(Graph* G,unsigned int* d){
            for (int i=0; i < G->number_nodes; i++){
                std::cout << d[i] << " ";
            }
            std::cout << std::endl;
}

unsigned int* Sequential_Dijkstra_Two_Queue(Graph* G,int key){
    Node* start;
    start = G->ret_node_at(key);
    int n = G->number_nodes;
    unsigned int* d = (unsigned int*) malloc(n*sizeof(unsigned int));
    for(int i=0;i<n;i++){
        d[i] = std::numeric_limits<int>::max();
    }
    d[start->key] = 0;
    TwoQueue Q;
    Q.insert(start);
    while(!Q.is_empty()){
        
        Node* i = Q.remove();
        std::vector<Edge> Succ = i->Neighbors;
        double curr_dis = d[i->key];
        for(int j=0;j<Succ.size();j++){
            Edge e = Succ[j]; 
            int k_succ = e.to->key;
            if(d[k_succ]> curr_dis + e.weight){
                assert(e.weight != -1);
                d[k_succ] = curr_dis + e.weight;
                Q.insert(e.to);
            }
        }
    }
    return d;
}