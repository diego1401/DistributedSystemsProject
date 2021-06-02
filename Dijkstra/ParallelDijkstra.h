#include "Dijkstra.h"
#include "Heap.h"
#include <thread>
#include <atomic>
#include <algorithm>
#include <vector>

class DijkQueue{
    public:
        Heap queue;
        Heap queue_star;
        Heap tent;
        DijkQueue() {}
        // DijkQueue(int src, Graph *gra){
        //     Element source = Element(src, 0);
        //     this->tent.push(source);
        //     for (int i= 0; i < gra->Nodes.size(); i++){
        //         if ((gra->Nodes[i]->key) == src) continue;
        //         else{
        //             Element ele = Element(gra->Nodes[i]->key, INT_MAX);
        //             this->tent.push(ele);
        //         }

        //     }
        // }
        void push(Element item){
            this->queue.push(item);
            this->queue_star.push(item);
        }
        void pop(){
            this->queue.pop();
            this->queue_star.pop();
        }

        bool isEmpty(){
            return this->queue.isEmpty() || this->queue_star.isEmpty();
        }
};


class ParDijkstra{
    public:
        std::map<int,int> delta;
        int num_threads;
        int source;
        int N;
        int * graph;
        unsigned int *glbtent; // Global distance array. Gonna need to lock when updating 
        ParDijkstra(){}
        ParDijkstra(Graph *g, int src){
            this->source = src;
            this->delta = minOutDistance(g);
            this->N = g->Nodes.size();
            this->graph = Adj_Matrix(g);
            this->glbtent = new unsigned int[this->N];
            std::fill_n(this->glbtent,this->N, INT_MAX);
            this->glbtent[this->source] = 0;
        }
        
        //L is our global minimum of all elements in all Q_star
        void compute(std::atomic<int> &L){
            // std::vector<std::thread> thread(num_threads - 1);
            DijkQueue ParQueue;
            Element src = Element(this->source, this->graph[this->source]);
            ParQueue.push(src);
            while (ParQueue.isEmpty()){
                if (ParQueue.queue_star.queue.front().value < L){
                    L.store(ParQueue.queue_star.queue.front().value);
                }

            }

        }

};

std::map<int,int> minOutDistance(Graph *g){
    std::map<int,int> dist;
    for (int i= 0; i < g->Nodes.size() ; i++ ){
        Node *node = g->Nodes[i];
        int minweight = INT_MAX;
        if (node->Neighbors.size() == 0) minweight = 0;
        else {
            for (int j = 0; j < node->Neighbors.size(); j++){
                if( node->Neighbors[i].weight < minweight){
                    minweight = node->Neighbors[i].weight;
                }
            }
        }
        dist[node->key] = minweight;
    }
    return dist;
}
