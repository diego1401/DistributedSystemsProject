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
        std::map<int,int> delta;
        int begin, end, n, N;
        std::vector<Element> R;
        std::vector<std::tuple<int,int>> Req;
        int *graph;
        // Heap tent;
        DijkQueue() {}
        DijkQueue(unsigned int *tentative, int beg, int end, std::map<int,int> delta, int *gra, int N){
            this->begin = beg; this->end = end;
            this->n = end-beg - 1;
            this->queue.queue.resize(this->n); this->queue_star.queue.resize(this->n);
            this->delta = delta;
            this->graph = gra;
            this->N = N;
            setqueue(tentative);
        }
        void setqueue(unsigned int * tent){
            for (int i= 0; i < this->n; i++ ){
                Element ele = Element(this->begin + i, tent[begin+ i]);
                Element elestar = Element(this->begin + i, tent[begin+ i]+ this->delta[begin+i]);
                this->queue.push(ele);
                this->queue_star.push(elestar);
            }
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
            while(this->queue.returnMin().value <= bound){
                R.push_back(this->queue.returnMin());
                this->queue.pop();
            }
            while(this->queue_star.returnMin().value <= bound){
                R.push_back(this->queue_star.returnMin());
                this->queue.pop();
            }
        }
        void find_distances(){
            for (int i = 0; i< R.size(); i++){
                Element v = R[i]; int ind = v.index;
                for (int j = 0; j < N; j++){
                    int k = index(ind, j,N);
                    Req.push_back(std::make_tuple(j,v.value + graph[k]));
                }
            }
        }
        bool isEmpty(){
            return this->queue.isEmpty() || this->queue_star.isEmpty();
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
            //Later needs to initialise this ParQueue correctly
            // Element src = Element(this->source, this->graph[this->source]);
            // ParQueue.push(src);
            while (ParQueue.isEmpty()){
                if (ParQueue.queue_star.returnMin().value < L){
                    L.store(ParQueue.queue_star.returnMin().value);
                }
                ParQueue.remove_tent(L);
                ParQueue.find_distances();
                for (int i=0; i < ParQueue.Req.size(); i++) {
                    int w, x;
                    std::tie(w,x)= ParQueue.Req[i];
                    if ( x < this->glbtent[w]){
                        glbtent[w] = x;
                    }
                    ParQueue.queue.DecreaseKey(w, x);
                    ParQueue.queue_star.DecreaseKey(w, x+ delta[w]);
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
