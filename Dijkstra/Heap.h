#pragma once
#include <climits>
#include <algorithm>
#include <map>
// #include "./btree/btree_set.h"

struct Element{
    int index;
    double value;
    Node *node;
    Element(){}
    Element(int i, double val, Node *node){this->index = i; this->value = val; this->node =node; }
};

class ElementComapre{
    public:
        bool operator()(const Element &a, const Element &b){
            if (a.value > b.value) return true;
            return false;
        }
};

class Heap{
    public:
    std::vector<Element> queue;
    // std::map<int, int> index_map;
    Heap() {}
    Heap(int N, std::vector<Element> init){
        this->queue.resize(N);
        for (int i=0; i< init.size(); i++){
            queue[i] = init[i];
            // index_map[init[i].index] = i;
        }
        std::make_heap(this->queue.begin(), this->queue.end(), ElementComapre());
    }
    void push(Element item){
        queue.push_back(item);
        std::push_heap(this->queue.begin(), this->queue.end(),ElementComapre());
    }

    Element returnMin(){
        // std::cout << this->queue.front().index << " value = " << this->queue.front().value << std::endl;
        return this->queue.front();
    }

    void pop(){
        std::pop_heap(this->queue.begin(), this->queue.end(),ElementComapre());
        this->queue.pop_back();
    }

    void DecreaseKey(int key, int newvalue){
        int k;
        for (int i = 0; i < this->queue.size(); i++){
            if (this->queue[i].index == key){
                this->queue[i].value = newvalue;
                // std::cout << index_map[key] << " and " << queue[i].index << std::endl;
                k = i;
                break;
                // this->queue[i].value = INT_MAX;
            }
        }
        // this->queue[index_map[key]].value = newvalue;
        // std::push_heap(this->queue.begin(), this->queue.begin() + index_map[key]+ 1, ElementComapre());
        // this->push(Element(key, newvalue));
        std::push_heap(this->queue.begin(), this->queue.begin() + k+ 1, ElementComapre());
        // std::make_heap(this->queue.begin(), this->queue.end(), ElementComapre());
    }

    bool isEmpty(){
        return this->queue.size();
    }
    void printqueue(){
        for (int i=0; i< this->queue.size(); i++){
            std::cout << "Index = " << queue[i].index << " and value = " << queue[i].value << std::endl;
        }
    }
};
