#pragma once
#include"Graph.hpp"
#include <queue>
#include <limits>
#include <map>
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


unsigned int* Sequential_Dijkstra_Two_Queue(Graph* G,int key){
    int n = G->number_nodes;
    unsigned int* d = (unsigned int*) malloc(n);
    for(int i=0;i<n;i++){
        d[i] = std::numeric_limits<int>::max();
    }
    Node* start;
    start = G->ret_node_at(key);
    start->print();
    d[start->key] = 0;
    TwoQueue Q;
    Q.insert(start);
    while(!Q.is_empty()){
        
        Node* i = Q.remove();
        std::vector<Edge> Succ = i->Neighbors;
        // std::cout << "Printing Neigh" << std::endl;
        // for(int k=0;k<Succ.size();k++){
        //     Succ[k].print();
        // }
        // std::cout << "finished" << std::endl;
        for(int j=0;j<Succ.size();j++){
            Edge e = Succ[j];
            int k_succ = e.to->key;
            if(d[k_succ]> d[i->key]+ e.weight){
                d[k_succ] = d[i->key] + e.weight;
                Q.insert(e.to);
            }
        }
    }
    return d;
}