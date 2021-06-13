#pragma once
#include "Dijkstra.h"
#include "Heap.h"
#include <atomic>
#include <algorithm>
#include <vector>
#include<set>
#include <condition_variable>
#include <functional>
#include <iostream>
#include<thread>
// #include "threadsafeq.h"
// #define DEBUGMODE
#ifdef DEBUGMODE
#define DEBUG
// #define DEBUG2
// #define QueueDebug
#define LDEBUG
#define INFLOOP
#endif

std::map<int,unsigned int> minOutDistance(unsigned int *g, int N, Graph *gra){
    std::map<int,unsigned int> dist;
    for (int i= 0; i < N ; i++ ){
        unsigned int minweight = std::numeric_limits<unsigned int>::max();
        Node *node = gra->Nodes[i];
            for (int j = 0; j < node->Neighbors.size(); j++){
                int k = index(i, j,N);
                if( node->Neighbors[j].weight < minweight && node->Neighbors[j].weight > 0){
                    minweight = node->Neighbors[j].weight;
                }
            }
        if (minweight == std::numeric_limits<unsigned int>::max()) minweight = 0;
        dist[i] = minweight;
    }
    return dist;
}
class DijkQueue{
    public:
        Heap queue;
        Heap queue_star;
        std::map<int,unsigned int> delta;
        int begin, end, n, N;
        std::set<Node*> R;
        std::vector<std::tuple<int,unsigned int>> Req;
        std::mutex lock;
        Graph *gra;
        unsigned int *graph;
        DijkQueue(const DijkQueue &other){
            this->queue = other.queue;
            this->queue_star = other.queue_star;
            this->delta = other.delta;
            this->begin = other.begin;
            this->end = other.end;
            this->n = other.n;
            this->N = other.N;
            this->R = other.R;
            this->Req = other.Req;
            this->graph = other.graph;
            this->gra = other.gra;

        }
        DijkQueue() {}
        DijkQueue(unsigned int *tentative, int beg, int end, std::map<int,unsigned int> delta, unsigned int *gra, int N, Graph *g){
            this->begin = beg; this->end = end;
            this->n = end-beg ;
            this->delta = delta;
            this->graph = gra;
            this->N = N;
            this->gra = g;
            setqueue(tentative);
        }
        // ~DijkQueue() {}
        void setqueue(unsigned int * tent){
            std::vector<Element> q, qstar;
            for (int i= 0; i < this->n; i++ ){
                Element ele = Element(this->gra->Nodes[begin + i]->key, tent[this->gra->Nodes[begin + i]->key], this->gra->Nodes[begin+i]);
                unsigned int starvalue;
                if (tent[this->gra->Nodes[begin + i]->key] == std::numeric_limits<unsigned int>::max()){
                    starvalue = std::numeric_limits<unsigned int>::max();
                } else starvalue = tent[this->gra->Nodes[begin + i]->key]+ this->delta[this->gra->Nodes[begin + i]->key];
                Element elestar = Element(this->gra->Nodes[begin + i]->key, starvalue, this->gra->Nodes[begin+i]);
                q.push_back(ele);
                qstar.push_back(elestar);
            }
            this->queue = Heap(this->n, q);
            this->queue_star = Heap(this->n, qstar);

            #ifdef DEBUG2
            this->printqueue();
            #endif
        }
        void remove_tent(unsigned int bound){
            for (int i = 0; i < this->queue.queue.size(); i++){
                if (this->queue.returnMin().value <= bound){
                    this->R.insert(this->queue.returnMin().node);
                    this->queue.pop();
                }
                else break;
            }
            for (int i = 0; i < this->queue_star.queue.size(); i++){
                if (this->queue_star.returnMin().value <= bound){
                    this->R.insert(this->queue_star.returnMin().node);
                    this->queue_star.pop();
                }
                else break;
            }
            #ifdef DEBUG2
            std::cout << "Values of R: " << std::endl;
            std::set<int>::iterator itr;
            for (itr = this->R.begin(); itr!= this->R.end(); itr++){
                std::cout << *itr << std::endl;
            }
            #endif
        }
        void find_distances(unsigned int *glbtent){
            std::set<Node*>::iterator itr;
            for (itr = this->R.begin(); itr!= this->R.end(); itr++){
                Node *ind = *itr;
                for (int j=0; j < ind->Neighbors.size(); j++){
                    // int k = index(ind,j,this->N);
                    // std::cout << ind->key << " and " <<ind->Neighbors[j].weight << std::endl;
                    unsigned int reqval;
                    if (glbtent[ind->key] == std::numeric_limits<unsigned int>::max()) reqval = std::numeric_limits<unsigned int>::max();
                    else reqval = glbtent[ind->key] + ind->Neighbors[j].weight;
                    Req.push_back(std::make_tuple(ind->Neighbors[j].to->key,reqval));
                }
            }
            #ifdef DEBUG2
            std::cout << "Values of Req of size: " << R.size() << std::endl;
            for (int i = 0; i< Req.size(); i++){
                int w, x; std::tie(w,x) = Req[i];
                std::cout << x << " of key " << w << std::endl;
            }
            std::cout << "Done" << std::endl;
            #endif
        }
        bool isEmpty(){
            // std::cout<< this->queue.queue.size() << std::endl;
            // std::cout<< this->queue_star.isEmpty() << std::endl;
            return this->queue.isEmpty() || this->queue_star.isEmpty();
        }
        void printqueue(){
            std::cout << "Printing queue: " << std::endl;
            this->queue.printqueue();
            std::cout << "Printing queue star" << std::endl;
            this->queue_star.printqueue();
            std::cout << std::endl;
        }
};


class ParDijkstra{
    public:
        std::mutex lock;
        std::map<int,unsigned int> delta;
        size_t num_threads;
        std::vector<std::thread>  threads;
        int source;
        int N, queue_size;
        unsigned int * graph;
        unsigned int *glbtent; 
        // std::mutex lock_list;
        std::vector<DijkQueue> Queues;
        Graph *g;
        ParDijkstra(){}
        ParDijkstra(Graph *g, int src, int num_threads){
            this->source = src;
            this->g = g;
            this->N = g->Nodes.size();
            this->num_threads = num_threads;
            this->queue_size = (N+num_threads - 1)/num_threads;
            this->graph = Adj_Matrix(g);
            this->delta = minOutDistance(this->graph, this->N, this->g);
            this->glbtent = new unsigned int[this->N];
            this->threads.resize(this->num_threads);
            std::fill_n(this->glbtent,this->N, std::numeric_limits<unsigned int>::max());
            this->glbtent[this->source] = 0;

            setqueue();
        }
        void setqueue(){
            for (int i=0; i < this->num_threads; i++){
                int begin = i*queue_size;
                int end;
                if (begin + queue_size > N) end = this->N;
                else end = begin + queue_size;
                
                DijkQueue dq = DijkQueue(this->glbtent, begin, end, this->delta, this->graph, this->N, this->g);
                this->Queues.push_back(dq);
            }
        }
        bool isEmpty(){
            bool res;
            for (int i=0; i < this->Queues.size(); i++) {
                res = Queues[i].isEmpty();
                if (res == true) return true;
            }
            return false;
        }

        int returnMin(){
            unsigned int min = std::numeric_limits<unsigned int>::max();
            for (int i=0; i < this->Queues.size(); i++) {

                #ifdef LDEBUG
                std::cout << "i is " << i << std::endl;
                this->Queues[i].queue_star.printqueue();
                std::cout << "Empty " <<  this->Queues[i].queue_star.isEmpty() << std::endl;
                std::cout << this->Queues[i].queue_star.queue.front().value << std::endl;
                std::cout << std::endl;
                #endif
                unsigned int tempmin;
                if (!this->Queues[i].queue_star.isEmpty()){
                    tempmin = std::numeric_limits<unsigned int>::max();
                }else{
                    tempmin = this->Queues[i].queue_star.returnMin().value;
                }
                // this->Queues[i].queue_star.printqueue();
                // std::cout << tempmin << std::endl;
                if (tempmin < min) min = tempmin;
            }
            return min;
        }
        void parcompute(int i, int L);
        
        void compute(){

            #ifdef DEBUG
            // ParQueue.printqueue();
            // print_deltamap();
            #endif
            int counter = 0;
            while (this->isEmpty()){
                unsigned int L = this->returnMin(); //L is our global minimum of all elements in all Q_star
                #ifdef DEBUG
                if (counter > 3) break;
                std::cout << L << std::endl;
                if (L == std::numeric_limits<unsigned int>::max()) std::cout << "Error: Min value L not set properly" << std::endl;
                // ParQueue.printqueue();
                #endif
                
                for (int i=0; i < this->num_threads; i++){
                    this->threads[i] = std::thread(&ParDijkstra::parcompute, this, i, L);
                }

                std::for_each(this->threads.begin(),this->threads.end(),std::mem_fn(&std::thread::join));
                #ifdef INFLOOP
                counter +=1;
                if (counter > 10) break;
                #endif
            }

        }
        void print_dist(){
            std::cout << "Printing distance map:" << std::endl; 
            for (int i=0; i < this->N; i++){
                std::cout << this->glbtent[i] << " ";
            }
            std::cout << std::endl;
        }

        void print_deltamap(){
            std::cout << "Printing delta map:" << std::endl;
            for (int i=0; i < this->delta.size(); i++){
                std::cout << "Key = " << i << " w = " << this->delta[i] << std::endl;
            }
            std::cout << std::endl;
        }

};


void ParDijkstra::parcompute(int i, int L){
    
    this->Queues[i].remove_tent(L);
    this->lock.lock();
    this->Queues[i].find_distances(this->glbtent);
    this->lock.unlock();
    for (int j=0; j < this->Queues[i].Req.size(); j++) {
        int w; unsigned int x;
        std::tie(w,x)= this->Queues[i].Req[j];
        if ( x < this->glbtent[w]){
            glbtent[w] = x;
            int qind = (int)w/this->queue_size;
            this->Queues[qind].lock.lock();
            this->Queues[qind].queue.DecreaseKey(w, x);
            this->Queues[qind].queue_star.DecreaseKey(w, x+ delta[w]);
            this->Queues[qind].lock.unlock();
        }  
    }
    this->Queues[i].R.clear();
    this->Queues[i].Req.clear();
}

void testcomp(const unsigned int * dist, const unsigned int * dist2, int N){
    bool res = true;
    for (int i=0; i < N; i++){
        if (dist[i] != dist2[i]){
            res = false;
            break;
        }
    }
    if (res){
        std::cout << "Parallel Dijkstra ran successfully with " << N << " nodes" << std::endl;
    }
    else {
        std::cout << "Error: Parallel Dijkstra returns different result from sequential version" << std::endl;
    }
}