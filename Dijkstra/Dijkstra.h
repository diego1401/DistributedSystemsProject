#include<iostream>
#include<algorithm>
#include <vector>
#include<math.h>
#include "../Graph.hpp"

class Dijkstra{
    public:
        int* distance;
        int source;
        int N;
        bool* check;
        // Graph* graph;
        int* graph;
        Dijkstra() {}
        Dijkstra(Graph *g, int src){
            this->graph = Adj_Matrix(g);
            this->source = src;
            this->N = g->Nodes.size();
            this->distance = new int[this->N];
            this->check = new bool[this->N];
        }
        int minDistance(int* dist, bool* c){
            int min = INFINITY; 
            int index;
            for (int i=0; i < this->N; i++){
                if(this->check[i]== false && this->distance[i] < min){
                    min = distance[i]; 
                    index = i;
                }
            }
            return index;
        }
        void compute(){
            for (int i=0; i < N; i++){
                this->distance[i] = INFINITY; this->check[i] = false;
            }
            this->distance[this->source] = 0;
            for (int i=0; i < N -1; i++){
                int minindex = minDistance(this->distance, this->check);
                this->check[minindex] = true;
                for (int j=0; j <N; j++){
                    if(!this->check[j] && this->graph[minindex + this->N*j] 
                        &&this->distance[minindex] != INFINITY && 
                        this->distance[minindex] + this->graph[minindex + this->N*j] < this->distance[j]) {
                            this->distance[j] = this->distance[minindex] + this->graph[minindex + this->N*j];
                        }
                }
            }
        }


};

