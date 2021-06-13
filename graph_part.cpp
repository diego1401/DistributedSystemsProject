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
        d[i] = std::numeric_limits<unsigned int>::max();
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

void ComputationStep(TwoQueue& Q,Graph* G, SubGraph* Gk, unsigned int* d,idx_t* part,bool& Done,
              std::vector<int>& sendTag, std::vector<std::vector<Edge>>& MessageArray, std::vector<std::mutex>& message_lock,
              int num_threads){

    //Local SSSP
    std::vector<std::vector<Edge>> local_message_array(num_threads);
    sendTag[Gk->key] = 0;
    while(!Q.is_empty()){
        Node* i = Q.remove();
        // for each successor node j of i, in current subgraph
        std::vector<Edge> Succ = i->Neighbors; unsigned int curr_dis = d[i->key];          
        for(int j=0;j<Succ.size();j++){
            int neighbor_key = Succ[j].to->key; 
            if(d[neighbor_key]> curr_dis + Succ[j].weight){
                d[neighbor_key] = curr_dis + Succ[j].weight; Q.insert(Succ[j].to);
            }
        }
        
        //Dealing with Boundary Nodes
        Node* i_prime = Gk->getBoundaryNode(i->key);
        if(i_prime != NULL){
        Succ = i_prime->Neighbors;
        for(int j=0;j<Succ.size();j++){ //iterate over the neighbors of i in all graphs
            int neighbor_key = Succ[j].to->key;
            if(d[neighbor_key]> curr_dis + Succ[j].weight){
                sendTag[Gk->key] = 1;
                local_message_array[part[neighbor_key]].push_back(Succ[j]);//send the edge that connects the 2 subgraphs 
                //to the subgraph of the neighbor 
            }  
        }
    }
    }

    //sending messages
    for(int k=0;k<local_message_array.size();k++){
        //If we have a message to send to the k subgraph we 
        //take the lock
        if(!local_message_array[k].empty()){
            std::lock_guard<std::mutex> lk(message_lock[k]);
            while(!local_message_array[k].empty()){
                MessageArray[k].push_back(local_message_array[k].back());
                local_message_array[k].pop_back();
            }
                
        }
    }
}

void CommunicationStep(TwoQueue& Q, std::vector<std::vector<Edge>>& MessageArray,
                std::vector<std::mutex>& lock_dist, std::vector<std::mutex>& message_lock,
                SubGraph* Gk, unsigned int* d){
                std::lock_guard<std::mutex> lk(message_lock[Gk->key]);
            while(!(MessageArray[Gk->key].empty())){
                Edge e = MessageArray[Gk->key].back(); 
                MessageArray[Gk->key].pop_back();
                // m -> n with weight w
                int m = e.from->key; int n = e.to->key;
                if(n>m){
                    std::lock_guard<std::mutex> lok(lock_dist[n]); 
                    std::lock_guard<std::mutex> lok2(lock_dist[m]);
                    if(d[n]>d[m]+e.weight){
                    d[n] = d[m] + e.weight; 
                    Node* node = Gk->ret_node_at(n);
                    Q.insert(node);
                    }
                }
                else{
                    std::lock_guard<std::mutex> lok2(lock_dist[m]);
                    std::lock_guard<std::mutex> lok(lock_dist[n]); 
                    if(d[n]>d[m]+e.weight){
                    d[n] = d[m] + e.weight; 
                    Node* node = Gk->ret_node_at(n);
                    Q.insert(node);
                    }   
                }
            }
}


unsigned int* Parallel_SSSP(Graph* G,duration<double>& time_span2,int starting_key=0){
    int num_threads = 2; std::vector<std::thread> threads(num_threads);
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
        d[i] = std::numeric_limits<unsigned int>::max();
    }
    Node* start; start = G->ret_node_at(starting_key); d[start->key] = 0;

    bool Done = false;
    std::vector<int> sendTag(num_threads);
    std::vector<int> ProcessesDone(num_threads); std::vector<std::vector<Edge>> MessageArray(num_threads);
    std::vector<std::mutex> lock(num_threads); std::vector<std::mutex> lock_dist(n); 
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    duration<double> total_CS ; duration<double> total_comS;
    //init 
    std::vector<TwoQueue> Q_s(num_threads); 
    for(int i=0;i<Q_s.size();i++){
        Node* start; start = Graphs[i]->ret_node_at(starting_key);
        if(start != NULL) Q_s[i].insert(start);
    }
    
    while(true){
        //First Step: Computation Step
        high_resolution_clock::time_point tmp1 = high_resolution_clock::now();
        for(unsigned long i=0;i<(num_threads);++i)
        {
            threads[i]=std::thread(ComputationStep,std::ref(Q_s[i]),G,Graphs[i],d,part, std::ref(Done),
                                    std::ref(sendTag),std::ref(MessageArray),std::ref(lock),
                                    num_threads);
        }
        
        for(unsigned long i=0;i<(num_threads);++i)
        {
            if(threads[i].joinable()) threads[i].join();
        }
        high_resolution_clock::time_point tmp2 = high_resolution_clock::now();
        total_CS += duration_cast<duration<double> >(tmp2 - tmp1);
        //Retrieve Tags from all processes
        int exitFlag = std::accumulate(sendTag.begin(),sendTag.end(),0);
        if(exitFlag){
            //Second Step: Communication Step
            high_resolution_clock::time_point tmp1 = high_resolution_clock::now();
            for(unsigned long i=0;i<(num_threads);++i)
                {
                    threads[i]=std::thread(CommunicationStep,std::ref(Q_s[i]),std::ref(MessageArray),std::ref(lock_dist),std::ref(lock),Graphs[i],d);
                }
            for(unsigned long i=0;i<(num_threads);++i)
                {
                    if(threads[i].joinable()) threads[i].join();
                }
            high_resolution_clock::time_point tmp2 = high_resolution_clock::now();
            total_comS += duration_cast<duration<double> >(tmp2 - tmp1);
            }   
            else{
                break;
            }
        }
    
    std::cout << "Computation Step: " << total_CS.count() << ". Communication Step: " << total_comS.count() << std::endl;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    time_span2 = duration_cast<duration<double> >(t2 - t1);
    return d;
}


/*
    Other attempts
*/

/*
void aux_SSSP1(Graph* G, SubGraph* Gk, unsigned int* d,idx_t* part,
              std::vector<int>& sendTag,std::vector<int>& ProcessesDone,
              std::vector<std::vector<Edge>>& MessageArray,
              std::vector<std::mutex>& message_lock,std::vector<std::mutex>& lock_dist,std::condition_variable& ProcessesDoneSignal,
              int num_threads,int starting_key=0){

    TwoQueue Q; Node* start; start = Gk->ret_node_at(starting_key);
    if(start != NULL) Q.insert(start);

    while(true){
        //Local SSSP
        std::vector<std::vector<Edge>> local_message_array(num_threads);
        while(!Q.is_empty()){
        Node* i = Q.remove();
        // for each successor node j of i, in current subgraph
        std::vector<Edge> Succ = i->Neighbors;
        unsigned int curr_dis = d[i->key];
                    
        for(int j=0;j<Succ.size();j++){
            unsigned int w = Succ[j].weight; int neighbor_key = Succ[j].to->key; 
            if(d[neighbor_key]> curr_dis + w){
                d[neighbor_key] = curr_dis + w; Q.insert(Succ[j].to);
            }
        }
        //Dealing with Boundary Nodes
        Node* i_prime = G->ret_node_at(i->key);
        Succ = i_prime->Neighbors;
        for(int j=0;j<Succ.size();j++){ //iterate over the neighbors of i in all graphs
            int neighbor_key = Succ[j].to->key;
            int k = part[neighbor_key]; //Id of the subgraph
            if(k != (Gk->key) && (d[neighbor_key]> curr_dis + Succ[j].weight)){
                sendTag[Gk->key] = 1;
                local_message_array[k].push_back(Succ[j]);//send the edge that connects the 2 subgraphs
            }  
        }}
        //sending messages
        for(int k=0;k<MessageArray.size();k++){
            //If we have a message to send to the k subgraph we 
            //take the lock
            if(!local_message_array[k].empty()){
                std::lock_guard<std::mutex> lk(message_lock[k]);
                for(int k_prime=0;k_prime<local_message_array[k].size();k_prime++){
                    MessageArray[k].push_back(local_message_array[k][k_prime]);
                }
            }
        }
        //Summing SendTags
        ProcessesDone[Gk->key] = 1;
        int exitFlag = 0;
        while(std::accumulate(ProcessesDone.begin(),ProcessesDone.end(),0) != num_threads){
            exitFlag = std::accumulate(sendTag.begin(),sendTag.end(),0.);
        }
        exitFlag = std::accumulate(sendTag.begin(),sendTag.end(),0.);
        //Sending messages or ending
        if(exitFlag){
            ProcessesDone[Gk->key] = 0;
            sendTag[Gk->key] = 0;
           
            std::lock_guard<std::mutex> lk(message_lock[Gk->key]);
            while(!(MessageArray[Gk->key].empty())){
                Edge e = MessageArray[Gk->key].back(); 
                MessageArray[Gk->key].pop_back();
                // m -> n with weight w
                int m = e.from->key; int n = e.to->key; unsigned int w = e.weight;
                if(n>m){
                    std::lock_guard<std::mutex> lok(lock_dist[n]); 
                    std::lock_guard<std::mutex> lok2(lock_dist[m]);
                    if(d[n]>d[m]+w){
                    d[n] = d[m] + w; Q.insert(Gk->ret_node_at(n));
                    }
                }
                else{
                    std::lock_guard<std::mutex> lok2(lock_dist[m]);
                    std::lock_guard<std::mutex> lok(lock_dist[n]); 
                    if(d[n]>d[m]+w){
                    d[n] = d[m] + w; Q.insert(Gk->ret_node_at(n));
                    }   
                }
            }
        }
        else{
            break;
        }
    }

}

void aux_SSSP(Graph* G, SubGraph* Gk, unsigned int* d,idx_t* part,bool& Done,
              std::vector<int>& sendTag,
              std::vector<int>& ProcessesDone,
              std::vector<std::vector<Edge>>& MessageArray,
              std::vector<std::mutex>& message_lock,std::vector<std::mutex>& lock_dist,
              int num_threads,int starting_key=0){

    TwoQueue Q; Node* start; start = Gk->ret_node_at(starting_key);
    if(start != NULL) Q.insert(start);
    std::vector<std::vector<Edge>> local_message_array(num_threads);
    // std::vector<int> local_ProcessesDone(num_threads);
    while(true){
        //Local SSSP
        sendTag[Gk->key] = 0;
        while(!Q.is_empty()){
        Node* i = Q.remove();
        // for each successor node j of i, in current subgraph
        std::vector<Edge> Succ = i->Neighbors;
        unsigned int curr_dis = d[i->key];
                    
        for(int j=0;j<Succ.size();j++){
            int neighbor_key = Succ[j].to->key; 
            if(d[neighbor_key]> curr_dis + Succ[j].weight){
                d[neighbor_key] = curr_dis + Succ[j].weight; Q.insert(Succ[j].to);
            }
        }
        
        //Dealing with Boundary Nodes
        Node* i_prime = Gk->getBoundaryNode(i->key);
        if(i_prime != NULL){
            Succ = i_prime->Neighbors;
            for(int j=0;j<Succ.size();j++){ //iterate over the neighbors of i in all graphs
                int neighbor_key = Succ[j].to->key;
                if(d[neighbor_key]> curr_dis + Succ[j].weight){
                    sendTag[Gk->key] = 1;
                    local_message_array[part[neighbor_key]].push_back(Succ[j]);//send the edge that connects the 2 subgraphs 
                    //to the subgraph of the neighbor 
                }  
            }
        }
        }
        //sending messages
        for(int k=0;k<local_message_array.size();k++){
            //If we have a message to send to the k subgraph we 
            //take the lock
            if(!local_message_array[k].empty()){
                std::lock_guard<std::mutex> lk(message_lock[k]);
                while(!local_message_array[k].empty()){
                    MessageArray[k].push_back(local_message_array[k].back());
                    local_message_array[k].pop_back();
                }
                   
            }
        }
        //Summing SendTags
        int exitFlag = 0;
        ProcessesDone[Gk->key] = 1;
        while(!Done){
            if(std::accumulate(ProcessesDone.begin(),ProcessesDone.end(),0)==num_threads) Done = true;
            
        }
        exitFlag = std::accumulate(sendTag.begin(),sendTag.end(),0.); ProcessesDone[Gk->key] = 0;
        while(Done){
            if(std::accumulate(ProcessesDone.begin(),ProcessesDone.end(),0)==0) Done = false;
        }
        
        //Sending messages or ending
        if(exitFlag){
            
            std::lock_guard<std::mutex> lk(message_lock[Gk->key]);
            while(!(MessageArray[Gk->key].empty())){
                Edge e = MessageArray[Gk->key].back(); 
                MessageArray[Gk->key].pop_back();
                // m -> n with weight w
                int m = e.from->key; int n = e.to->key;
                if(n>m){
                    std::lock_guard<std::mutex> lok(lock_dist[n]); 
                    std::lock_guard<std::mutex> lok2(lock_dist[m]);
                    if(d[n]>d[m]+e.weight){
                    d[n] = d[m] + e.weight; 
                    // Q.insert(e.to);
                    Node* node = Gk->ret_node_at(n);
                    Q.insert(node);
                    }
                }
                else{
                    std::lock_guard<std::mutex> lok2(lock_dist[m]);
                    std::lock_guard<std::mutex> lok(lock_dist[n]); 
                    if(d[n]>d[m]+e.weight){
                    d[n] = d[m] + e.weight; 
                    // Q.insert(e.to);
                    Node* node = Gk->ret_node_at(n);
                    Q.insert(node);
                    }   
                }
            }
        }   
        else{
            std::cout << "Im out :0" << std::endl;
            break;
        }
    }

}

unsigned int* Parallel_SSSP1(Graph* G,duration<double>& time_span2,int starting_key=0){
    int num_threads = 2; std::vector<std::thread> threads(num_threads);
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
        d[i] = std::numeric_limits<unsigned int>::max();
    }
    Node* start; start = G->ret_node_at(starting_key); d[start->key] = 0;

    // std::atomic<int> sendTag{0}; 
    bool Done = false;
    std::vector<int> sendTag(num_threads);
    // std::atomic<int> ProcessesDone{0};
    std::vector<int> ProcessesDone(num_threads);
    std::vector<std::vector<Edge>> MessageArray(num_threads);
    std::vector<std::mutex> lock(num_threads);//Only one thread can modify MessageArray[k] at a time
    std::vector<std::mutex> lock_dist(n); 
    std::condition_variable ProcessesDoneSignal;
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for(unsigned long i=0;i<(num_threads);++i)
    {
        threads[i]=std::thread(aux_SSSP,G,Graphs[i],d,part, std::ref(Done),
                                std::ref(sendTag),std::ref(ProcessesDone),std::ref(MessageArray),std::ref(lock),std::ref(lock_dist),
                                // std::ref(ProcessesDoneSignal),
                                num_threads,0);
    }
    
    for(unsigned long i=0;i<(num_threads);++i)
    {
        if(threads[i].joinable()) threads[i].join();
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    time_span2 = duration_cast<duration<double> >(t2 - t1);
    return d;
}
*/
