#pragma once
#include "Dijkstra.h"
#include "Heap.h"
#include <thread>
#include <atomic>
#include <algorithm>
#include <vector>
#include<set>
// #define DEBUG
// #define DEBUG2
std::map<int,int> minOutDistance(int *g, int N){
    std::map<int,int> dist;
    for (int i= 0; i < N ; i++ ){
        int minweight = INT_MAX;
            for (int j = 0; j < N; j++){
                // if (j == i) continue;
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
        std::map<int,int> delta;
        int begin, end, n, N;
        std::set<int> R;
        std::vector<std::tuple<int,int>> Req;
        int *graph;
        // Heap tent;
        DijkQueue() {}
        DijkQueue(unsigned int *tentative, int beg, int end, std::map<int,int> delta, int *gra, int N){
            this->begin = beg; this->end = end;
            // this->n = end-beg - 1;
            // this->queue.queue.resize(this->N); this->queue_star.queue.resize(this->N);
            this->delta = delta;
            this->graph = gra;
            this->N = N;
            setqueue(tentative);
        }
        void setqueue(unsigned int * tent){
            std::vector<Element> q, qstar;
            for (int i= 0; i < this->N; i++ ){
                Element ele = Element(this->begin + i, tent[begin+ i]);
                int starvalue;
                if (tent[begin + i] == INT_MAX){
                    starvalue = INT_MAX;
                } else starvalue = tent[begin+ i]+ this->delta[begin+i];
                Element elestar = Element(this->begin + i, starvalue);
                q.push_back(ele);
                qstar.push_back(elestar);
            }
            this->queue = Heap(this->N, q);
            this->queue_star = Heap(this->N, qstar);
        }
        void push(Element item){
            this->queue.push(item);
            this->queue_star.push(item);
        }
        void pop(){
            this->queue.pop();
            this->queue_star.pop();
        }
        void remove_tent(int bound){
            for (int i = 0; i < this->queue.queue.size(); i++){
                if (this->queue.returnMin().value <= bound){
                    // this->R.push_back(this->queue.returnMin());
                    this->R.insert(this->queue.returnMin().index);
                    this->queue.pop();
                }
                else break;
            }
            for (int i = 0; i < this->queue_star.queue.size(); i++){
                if (this->queue_star.returnMin().value <= bound){
                    // this->R.push_back(this->queue_star.returnMin());
                    this->R.insert(this->queue.returnMin().index);
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
                    Req.push_back(std::make_tuple(j,glbtent[ind] + graph[k]));
                }
            }

            // for (int i = 0; i< R.size(); i++){
            //     Element v = R[i]; int ind = v.index;
            //     for (int j = 0; j < N; j++){
            //         int k = index(ind, j,N);
            //         Req.push_back(std::make_tuple(j,v.value + graph[k]));
            //     }
            // }
            #ifdef DEBUG2
            std::cout << "Values of Req of size: " << R.size() << std::endl;
            for (int i = 0; i< Req.size(); i++){
                int w, x; std::tie(w,x) = Req[i];
                std::cout << x << " of key " << w << std::endl;
            }
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
        }
};


class ParDijkstra{
    public:
        std::map<int,int> delta;
        size_t num_threads;
        std::vector<std::thread>  threads;
        int source;
        int N;
        int * graph;
        unsigned int *glbtent; // Global distance array. Gonna need to lock when updating 
        ParDijkstra(){}
        ParDijkstra(Graph *g, int src){
            this->source = src;
            this->N = g->Nodes.size();
            this->graph = Adj_Matrix(g);
            this->delta = minOutDistance(this->graph, this->N);
            this->glbtent = new unsigned int[this->N];
            std::fill_n(this->glbtent,this->N, INT_MAX);
            this->glbtent[this->source] = 0;
        }
        
        //L is our global minimum of all elements in all Q_star
        void compute(){
            // std::vector<std::thread> thread(num_threads - 1);
            int L = INT_MAX;
            DijkQueue ParQueue = DijkQueue(glbtent, 0, N, delta, graph, N);

            #ifdef DEBUG
            // ParQueue.printqueue();
            print_deltamap();
            #endif
            //Later needs to initialise this ParQueue correctly
            // Element src = Element(this->source, this->graph[this->source]);
            // ParQueue.push(src);
            while (ParQueue.isEmpty()){
                if (ParQueue.queue_star.returnMin().value < L){
                    // L.store(ParQueue.queue_star.returnMin().value);
                    // std::cout << ParQueue.queue_star.returnMin().value << std::endl;
                    L = ParQueue.queue_star.returnMin().value;
                }
                #ifdef DEBUG
                std::cout << L << std::endl;
                ParQueue.printqueue();
                #endif
                ParQueue.remove_tent(L);
                ParQueue.find_distances(this->glbtent);
                for (int i=0; i < ParQueue.Req.size(); i++) {
                    int w, x;
                    std::tie(w,x)= ParQueue.Req[i];
                    #ifdef DEBUG
                    std::cout << "w = " << w  << " x = " << x << std::endl;
                    #endif
                    if ( x < this->glbtent[w]){
                        glbtent[w] = x;
                    }
                    ParQueue.queue.DecreaseKey(w, x);
                    ParQueue.queue_star.DecreaseKey(w, x+ delta[w]);
                }
                L = INT_MAX;
                ParQueue.R.clear();
                ParQueue.Req.clear();
                // print_dist();
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


