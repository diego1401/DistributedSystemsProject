#pragma once

#include "../Graph.hpp"
// #define MAT_DEBUG

class Dijkstra{
    public:
        unsigned int* distance;
        int source;
        int N;
        bool* check;
        // Graph* graph;
        unsigned int* graph;
        Dijkstra() {}
        Dijkstra(Graph *g, int src){
            this->graph = Adj_Matrix(g);
            this->source = src;
            this->N = g->number_nodes;
            this->distance = new unsigned int[this->N];
            this->check = new bool[this->N];

            #ifdef MAT_DEBUG
            print_matrix(this->graph, N);
            #endif
        }
        int minDistance(){
            int min = std::numeric_limits<unsigned int>::max(); 
            int index=0;
            for (int i=0; i < this->N; i++){
                if(this->check[i]== false && this->distance[i] < min){
                    min = this->distance[i]; 
                    index = i;

                }
            }
            return index;
        }
        void compute(){
            for (int i=0; i < N; i++){
                this->distance[i] = std::numeric_limits<unsigned int>::max(); this->check[i] = false;
            }
            this->distance[this->source] = 0;
            // this->check[this->source] = true;
            for (int i=0; i < N -1; i++){
                // print_dist();
                int minindex = minDistance();
                this->check[minindex] = true;
                for (int j=0; j <N; j++){
                    // std::cout << this->graph[minindex + this->N*j] << " index: " << std::endl;
                    if(!this->check[j]
                        &&this->distance[minindex] != std::numeric_limits<unsigned int>::max() && 
                        this->graph[index(minindex,j,N)] != std::numeric_limits<unsigned int>::max() &&
                        this->distance[minindex] + this->graph[index(minindex,j,N)] < this->distance[j]) {
                            // std::cout << minindex << std::endl;
                            // std::cout << N<< std::endl;
                            // std::cout << this->graph[index(minindex, j,N)] << " index: " << j << std::endl;

                            this->distance[j] = this->distance[minindex] + this->graph[index(minindex, j,N)];
                        }
                }
            }
        }
        void print_dist(){
            for (int i=0; i < this->N; i++){
                std::cout << this->distance[i] << " ";
            }
            std::cout << std::endl;
        }


};

