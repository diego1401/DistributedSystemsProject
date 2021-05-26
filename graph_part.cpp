#include"Graph.hpp"
#include <queue>
#include <limits>
//First we implement the sequential version of the algorithm described in the paper

class TwoQueue{
    public:
    std::queue<Node*> Q_pp;
    std::queue<Node*> Q_p;
    TwoQueue(){};

    void insert(Node* j){
        if(!j->in_queue){
            //Unreached
            if(j->status==0) this->Q_p.push(j);
            //tmp labeled
            else if(j->status==1) this->Q_pp.push(j);
        }
    }

    Node* remove(){
        if(!this->Q_pp.empty()){
            Node*j = this->Q_pp.front();
            this->Q_pp.pop();
            return j;
        }
        if(!this->Q_p.empty()){
            Node*j = this->Q_p.front();
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


int* Sequential_Dijkstra_Two_Queue(Graph* G, Node* s){
    int n = G->number_nodes;
    int* d = (int*) malloc(n);
    for(int i=0;i<n;i++){
        d[i] = std::numeric_limits<int>::max();
    }
    s->print();
    d[s->key] = 0;
    TwoQueue Q;
    Q.insert(s);
    while(!Q.is_empty()){
        Node* i = Q.remove();
        std::vector<Edge> Succ = i->Neighbors;
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