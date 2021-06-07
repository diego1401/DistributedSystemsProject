#pragma once
#include"Graph.hpp"

/*
    First we implement the sequential 
    version of the algorithm described 
    in the paper
*/

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

//Todo: - Confirm code is run. If it is, Boundary Nodes sufficient?
//      - How to implement SendTag?

// void aux_SSSP(Graph* G, SubGraph* Gk, unsigned int* d,idx_t* part,
//               int sendTag,std::vector<std::vector<int>>& MessageArray,std::mutex lock,int key=0){
//     TwoQueue Q;
//     Node* start;
//     start = Gk->ret_node_at(key);
//     Q.insert(start);
//     while(true){
//         while(!Q.is_empty()){
//         Node* i = Q.remove();
//         // for each successor node j of i, in current subgraph
//         std::vector<Edge> Succ = i->Neighbors; double curr_dis = d[i->key];
//         for(int j=0;j<Succ.size();j++){
//             int w = Succ[j].weight; int k = Succ[j].to->key; 
//             if(d[k]> curr_dis + w){
//                 d[k] = curr_dis + w; Q.insert(Succ[j].to);
//             }
//         }
//         //for each successor node r(in a subgraph k) of i
//         //find i in the original graph
//         Node* i_prime = G->ret_node_at(i->key);
//         std::vector<Edge> Succ = i->Neighbors; double curr_dis = d[i->key];
//         for(int j=0;j<Succ.size();j++){
//             int w = Succ[j].weight; int k = Succ[j].to->key; 
//             if(d[k]> curr_dis + w){
//                 std::lock_guard<std::mutex> lk(lock);
//                 sendTag += 1;
//                 MessageArray[Gk->key].push_back(k);
//             }
//         }
        

//         }
    
//     }

// }

// unsigned int* Parallel_SSSP(Graph* G,int key,idx_t *part){
//     int num_threads = 5;
//     std::vector<std::thread> threads(num_threads-1);

//     //Do graph partionning 
//     idx_t* part;
//     //Init dist
//     int n = G->number_nodes; unsigned int* d = (unsigned int*) malloc(n*sizeof(unsigned int));
//     for(int i=0;i<n;i++){
//         d[i] = std::numeric_limits<int>::max();
//     }
//     Node* start; start = G->ret_node_at(key); d[start->key] = 0;

//     std::atomic<int> sendTag{0};
//     std::vector<std::vector<int>> MessageArray(num_threads);
//     std::mutex lock;

//     for(unsigned long i=0;i<(num_threads-1);++i)
//     {
//         threads[i]=std::thread(Parallel_SSSP,G,NULL,d,part,sendTag,MessageArray,lock);
//     }
// }