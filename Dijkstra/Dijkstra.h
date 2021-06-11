#pragma once
#include<iostream>
#include<algorithm>
#include <vector>
#include<math.h>
#include <climits>
#include "../Graph.hpp"


class Dijkstra{
    public:
        unsigned int* distance;
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
            // print_matrix(this->graph, N);
            this->distance = new unsigned int[this->N];
            this->check = new bool[this->N];
        }
        int minDistance(){
            int min = INT_MAX; 
            int index=0;
            for (int i=0; i < this->N; i++){
                if(this->check[i]== false && this->distance[i] < min){
                    if (this->distance[i] > 0){
                        min = this->distance[i]; 
                        index = i;
                    }

                }
            }
            return index;
        }
        void compute(){
            for (int i=0; i < N; i++){
                this->distance[i] = INT_MAX; this->check[i] = false;
            }
            this->distance[this->source] = 0;
            // this->check[this->source] = true;
            for (int i=0; i < N -1; i++){
                // print_dist();
                int minindex = minDistance();
                this->check[minindex] = true;
                for (int j=0; j <N; j++){
                    // std::cout << this->graph[minindex + this->N*j] << " index: " << std::endl;
                    if(!this->check[j] && this->graph[index(minindex, j,N)] >0
                        &&this->distance[minindex] != INT_MAX && 
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

