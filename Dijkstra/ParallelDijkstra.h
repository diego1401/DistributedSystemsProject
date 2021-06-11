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
#define DEBUG2
#define QueueDebug
#define LDEBUG
#define INFLOOP
#endif

std::map<int,unsigned int> minOutDistance(unsigned int *g, int N){
    std::map<int,unsigned int> dist;
    for (int i= 0; i < N ; i++ ){
        int minweight = INT_MAX;
            for (int j = 0; j < N; j++){
                int k = index(i, j,N);
                if( g[k] < minweight && g[k] > 0){
                    minweight = g[k];
                }
            }
        if (minweight == INT_MAX) minweight = 0;
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
        std::set<int> R;
        std::vector<std::tuple<int,unsigned int>> Req;
        std::mutex lock;
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

        }
        DijkQueue() {}
        DijkQueue(unsigned int *tentative, int beg, int end, std::map<int,unsigned int> delta, unsigned int *gra, int N){
            this->begin = beg; this->end = end;
            this->n = end-beg ;
            this->delta = delta;
            this->graph = gra;
            this->N = N;
            setqueue(tentative);
        }
        // ~DijkQueue() {}
        void setqueue(unsigned int * tent){
            std::vector<Element> q, qstar;
            for (int i= 0; i < this->n; i++ ){
                Element ele = Element(this->begin + i, tent[begin+ i]);
                int starvalue;
                if (tent[begin + i] == INT_MAX){
                    starvalue = INT_MAX;
                } else starvalue = tent[begin+ i]+ this->delta[begin+i];
                Element elestar = Element(this->begin + i, starvalue);
                q.push_back(ele);
                qstar.push_back(elestar);
            }
            this->queue = Heap(this->n, q);
            this->queue_star = Heap(this->n, qstar);

            #ifdef DEBUG2
            this->printqueue();
            #endif
        }
        // void push(Element item){
        //     this->queue.push(item);
        //     this->queue_star.push(item);
        // }
        // void pop(){
        //     this->queue.pop();
        //     this->queue_star.pop();
        // }
        void remove_tent(int bound){
            for (int i = 0; i < this->queue.queue.size(); i++){
                if (this->queue.returnMin().value <= bound){
                    this->R.insert(this->queue.returnMin().index);
                    this->queue.pop();
                }
                else break;
            }
            for (int i = 0; i < this->queue_star.queue.size(); i++){
                if (this->queue_star.returnMin().value <= bound){
                    this->R.insert(this->queue_star.returnMin().index);
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
            std::set<int>::iterator itr;
            for (itr = this->R.begin(); itr!= this->R.end(); itr++){
                int ind = *itr;
                for (int j=0; j < this->N; j++){
                    int k = index(ind,j,this->N);
                    unsigned int reqval;
                    if (glbtent[ind] == INT_MAX) reqval = INT_MAX;
                    else reqval = glbtent[ind] + graph[k];
                    Req.push_back(std::make_tuple(j,reqval));
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
        std::map<int,unsigned int> delta;
        size_t num_threads;
        std::vector<std::thread>  threads;
        int source;
        int N, queue_size;
        unsigned int * graph;
        unsigned int *glbtent; 
        // std::mutex lock_list;
        std::vector<DijkQueue> Queues;
        ParDijkstra(){}
        ParDijkstra(Graph *g, int src, int num_threads){
            this->source = src;
            this->N = g->Nodes.size();
            this->num_threads = num_threads;
            this->queue_size = (N+num_threads - 1)/num_threads;
            this->graph = Adj_Matrix(g);
            this->delta = minOutDistance(this->graph, this->N);
            this->glbtent = new unsigned int[this->N];
            this->threads.resize(this->num_threads);
            std::fill_n(this->glbtent,this->N, INT_MAX);
            this->glbtent[this->source] = 0;

            setqueue();
        }
        void setqueue(){
            for (int i=0; i < this->num_threads; i++){
                int begin = i*queue_size;
                int end;
                if (begin + queue_size > N) end = this->N;
                else end = begin + queue_size;
                
                DijkQueue dq = DijkQueue(this->glbtent, begin, end, this->delta, this->graph, this->N);
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
            int min = INT_MAX;
            for (int i=0; i < this->Queues.size(); i++) {

                #ifdef LDEBUG
                std::cout << "i is " << i << std::endl;
                this->Queues[i].queue_star.printqueue();
                std::cout << "Empty " <<  this->Queues[i].queue_star.isEmpty() << std::endl;
                std::cout << this->Queues[i].queue_star.queue.front().value << std::endl;
                std::cout << std::endl;
                #endif
                int tempmin;
                if (!this->Queues[i].queue_star.isEmpty()){
                    tempmin = INT_MAX;
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
            while (this->isEmpty()){
                int L = this->returnMin(); //L is our global minimum of all elements in all Q_star
                #ifdef DEBUG
                if (counter > 3) break;
                std::cout << L << std::endl;
                if (L == INT_MAX) std::cout << "Error: Min value L not set properly" << std::endl;
                // ParQueue.printqueue();
                #endif
                
                for (int i=0; i < this->num_threads; i++){
                    this->threads[i] = std::thread(&ParDijkstra::parcompute, this, i, L);
                }

                std::for_each(this->threads.begin(),this->threads.end(),std::mem_fn(&std::thread::join));
                #ifdef INFLOOP
                counter +=1;
                if (counter > 3) break;
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
    this->Queues[i].find_distances(this->glbtent);
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