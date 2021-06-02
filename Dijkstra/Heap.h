#include <vector>
#include <climits>
#include <algorithm>
#include <map>
#include "./btree/btree_set.h"
struct Element{
    int index;
    double value;
    Element(){}
    Element(int i, double val){this->index = i; this->value = val;}
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
    std::map<int, int> index_map;
    Heap() {}
    Heap(int N, std::vector<Element> init){
        this->queue.resize(N);
        for (int i=0; i< init.size(); i++){
            queue[i] = init[i];
            index_map[init[i].index] = i;
        }
        std::make_heap(this->queue.begin(), this->queue.end(), ElementComapre());
    }
    void push(Element item){
        queue.push_back(item);
        std::push_heap(this->queue.begin(), this->queue.end(),ElementComapre());
    }

    Element returnMin(){
        return this->queue.front();
    }

    void pop(){
        std::pop_heap(this->queue.begin(), this->queue.end(),ElementComapre());
        this->queue.pop_back();
    }

    void DecreaseKey(int key, int newvalue){
        for (int i = 0; i < this->queue.size(); i++){
            if (this->queue[i].index == key){
                this->queue[i].value = newvalue;
            }
        }
        std::make_heap(this->queue.begin(), this->queue.end(), ElementComapre());
    }

    bool isEmpty(){
        return this->queue.size();
    }
};
