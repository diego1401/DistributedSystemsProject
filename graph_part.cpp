#pragma once
#include"Graph.hpp"
using namespace std::chrono;

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

/*
    Now we proceed to implement the 
    parallel version of the code
*/

void aux_SSSP(Graph* G, SubGraph* Gk, unsigned int* d,idx_t* part,
              std::atomic<int>& sendTag,std::atomic<int>& ProcessesDone,
              std::vector<std::vector<Edge>>& MessageArray,
              std::mutex& lock,std::mutex& lock2,std::condition_variable& ProcessesDoneSignal,
              int num_threads,int starting_key=0){
    TwoQueue Q;
    Node* start;
    start = Gk->ret_node_at(starting_key);
    if(start != NULL){
        // std::cout << "found" << std::endl;
        Q.insert(start);
    } 
    while(true){
        //Local SSSP
        while(!Q.is_empty()){
        Node* i = Q.remove();
        // for each successor node j of i, in current subgraph
        std::vector<Edge> Succ = i->Neighbors; unsigned int curr_dis = d[i->key];
        for(int j=0;j<Succ.size();j++){
            int w = Succ[j].weight; int k = Succ[j].to->key; 
            // std::cout << "Data: " << curr_dis << " " << w << std::endl;
            if(d[k]> curr_dis + w){
                d[k] = curr_dis + w; Q.insert(Succ[j].to);
            }
        }
        //Dealing with Boundary Nodes
        Node* i_prime = G->ret_node_at(i->key);
        Succ = i_prime->Neighbors; curr_dis = d[i_prime->key];
        for(int j=0;j<Succ.size();j++){ //iterate over the neighbors of i in all graphs
            int k = part[Succ[j].to->key]; //Id of the subgraph
            // std::cout << "Boundary" << std::endl;
            // std::cout << i_prime->key << "->" << Succ[j].to->key << std::endl;
            // std::cout << "k = "<< k << "Gk = " << Gk->key <<" , " <<d[Succ[j].to->key]<< ">"<<curr_dis << "+"<< Succ[j].weight<< std::endl;
            if(k != (Gk->key) && (d[Succ[j].to->key]> curr_dis + Succ[j].weight)){
                
                sendTag.fetch_add(1);
                std::lock_guard<std::mutex> lk(lock);
                MessageArray[k].push_back(Succ[j]);//send the edge that connects the 2 subgraphs
            }  
        }}
        //Summing SendTags
        // std::cout << "Summing in " << Gk->key << std::endl;
        ProcessesDone.fetch_add(1);
        // ProcessesDoneSignal.notify_all();
        int exitFlag = 0;
        // std::unique_lock<std::mutex> lk(lock2);
        while(ProcessesDone != num_threads){
            exitFlag = sendTag;
            // ProcessesDoneSignal.wait(lk);
        }
        exitFlag = sendTag;
        // ProcessesDoneSignal.notify_all();
        // std::cout << "Finished = " << exitFlag << "in " << Gk->key << std::endl;

        //Sending messages or ending
        if(exitFlag){
            for(int i=0;i<MessageArray[Gk->key].size();i++){
                int m = MessageArray[Gk->key][i].from->key; 
                int n = MessageArray[Gk->key][i].to->key;
                int w = MessageArray[Gk->key][i].weight;
                if(d[n]>d[m]+w){
                    d[n] = d[m] + w;
                    Q.insert(MessageArray[Gk->key][i].to);
                }
            }

            ProcessesDone.fetch_sub(1);
            // ProcessesDoneSignal.notify_all();
            while(ProcessesDone != 0){
                // ProcessesDoneSignal.wait(lk);
            }
            sendTag = 0;
            // ProcessesDoneSignal.notify_all();

        }
        else{
            break;
        }
    }

}

unsigned int* Parallel_SSSP(Graph* G,duration<double>& time_span2,int starting_key=0){
    int num_threads = 7; std::vector<std::thread> threads(num_threads);
    //Do graph partionning 
    idx_t nParts  = (idx_t) num_threads; idx_t objval;
    idx_t nVertices = (idx_t)G->number_nodes; idx_t* part = (idx_t *) malloc(nVertices*sizeof(idx_t));
    idx_t nWeights = 1; //idx why XD

    int ret = METIS_PartGraphKway(&nVertices,&nWeights, G->xadj, G->adjncy,
				       NULL, NULL, G->adjwgt, &nParts, NULL,
				       NULL, NULL, &objval, part);
    std::cout << "METIS_PartGraphKway status:" << ret << std::endl;
    //init SubGraphs
    std::vector<SubGraph*> Graphs(num_threads);
    for(int i=0;i<num_threads;i++){
        Graphs[i] = new SubGraph(G,part,i);
    }

    //Init dist
    int n = G->number_nodes; unsigned int* d = (unsigned int*) malloc(n*sizeof(unsigned int));
    for(int i=0;i<n;i++){
        d[i] = std::numeric_limits<int>::max();
    }
    Node* start; start = G->ret_node_at(starting_key); d[start->key] = 0;

    std::atomic<int> sendTag{0}; std::atomic<int> ProcessesDone{0};
    std::vector<std::vector<Edge>> MessageArray(num_threads);
    std::mutex lock; std::mutex lock2; std::condition_variable ProcessesDoneSignal;
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for(unsigned long i=0;i<(num_threads);++i)
    {
        threads[i]=std::thread(aux_SSSP,G,Graphs[i],d,part,
                                std::ref(sendTag),std::ref(ProcessesDone),std::ref(MessageArray),std::ref(lock),std::ref(lock2),
                                std::ref(ProcessesDoneSignal),num_threads,0);
    }
    
    for(unsigned long i=0;i<(num_threads);++i)
    {
        if(threads[i].joinable()) threads[i].join();
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    time_span2 = duration_cast<duration<double> >(t2 - t1);
    return d;
}