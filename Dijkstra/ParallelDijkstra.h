#include "Dijkstra.h"
#include "Heap.h"
class DijkQueue{
    public:
        Heap in_queue;
        Heap out_queue;
};


class ParDijkstra{
    public:
        Heap tent;
        std::map<int,int> delta;

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