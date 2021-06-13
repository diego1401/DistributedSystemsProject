#include "graph_part.cpp"
#include "Dijkstra/Dijkstra.h"

void test_sequential(){
    Graph *gra =  new Graph;
    gra->random_nodes(10000,4);
    unsigned int* d;
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    d = Sequential_Dijkstra_Two_Queue(gra, 0);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span1 = duration_cast<duration<double> >(t2 - t1);

    Dijkstra dijk = Dijkstra(gra, 0);
    t1 = high_resolution_clock::now();
    dijk.compute();
    t2 = high_resolution_clock::now();
    duration<double> time_span2 = duration_cast<duration<double> >(t2 - t1);
     std::cout << "Comparing" << " ";
    for(int i=0;i<gra->number_nodes;i++){
        if(d[i]!=dijk.distance[i]){
            std::cout << "Fail!" ;
        }
    }
    std::cout <<"... Success!" << std::endl;
    std::cout << "Time TwoQ: " << time_span1.count() << " , Time Dijkstra: " << time_span2.count() << std::endl;
    // std::cout << "Original" << " ";
    // dijk.print_dist();
    // std::cout << std::endl;
    // std::cout << "TwoQueue" << " ";
    // for(int i=0;i<6;i++){
    //     std::cout << d[i] << " ";
    // }
    // std::cout << std::endl;
}

void test_fill_METIS_values(){
    // 0 - 1 - 2
    // |   |   |
    // 3 - 4 - 5
    Node* n0 = new Node(0); Node* n1 = new Node(1); Node* n2 = new Node(2);
    Node* n3 = new Node(3); Node* n4 = new Node(4); Node* n5 = new Node(5);

    Edge e0_1(n0,n1,1), e0_3(n0,n3,1),
         e1_0(n1,n0,1), e1_4(n1,n4,1), e1_2(n1,n2,1),
         e2_1(n2,n1,1), e2_5(n2,n5,1),
         e3_0(n3,n0,1), e3_4(n3,n4,1),
         e4_3(n4,n3,1), e4_1(n4,n1,1), e4_5(n4,n5,1),
         e5_2(n5,n2,1), e5_4(n5,n4,1);

    Graph* G = new Graph();
    G->add_node(n0); G->add_node(n1);G->add_node(n2);
    G->add_node(n3); G->add_node(n4);G->add_node(n5);

    G->Edges = {e0_1, e0_3, e1_0, e1_4, e1_2,
                e2_1, e2_5, e3_0, e3_4, e4_3, e4_1, e4_5,
                e5_2, e5_4};
    G->fill_neighbors();
    G->fill_METIS_values();
    
    std::cout << "xajd = ";
    for(int i=0;i<G->number_nodes;i++){
        std::cout << G->xadj[i] << ", ";
    }
    std::cout << G->xadj[G->number_nodes] << std::endl;

    std::cout << "adjncy = ";
    for(int i=0;i<G->Edges.size();i++){
        
        std::cout << G->adjncy[i];
        if(i!= G->Edges.size()-1) std::cout << ", ";
    }
    std::cout << std::endl;
    std::cout << "adjwgt = ";
    for(int i=0;i<G->Edges.size();i++){
        
        std::cout << G->adjwgt[i];
        if(i!= G->Edges.size()-1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void test_veryeasy_graph_part(){
    // 0 - 1 - 2
    // |   |   |
    // 3 - 4 - 5
    //init 
    Node* n0 = new Node(0); Node* n1 = new Node(1); Node* n2 = new Node(2);
    Node* n3 = new Node(3); Node* n4 = new Node(4); Node* n5 = new Node(5);

    Edge e0_1(n0,n1,1), e0_3(n0,n3,1),
        e1_0(n1,n0,1), e1_4(n1,n4,1), e1_2(n1,n2,1),
        e2_1(n2,n1,1), e2_5(n2,n5,1),
        e3_0(n3,n0,1), e3_4(n3,n4,1),
        e4_3(n4,n3,1), e4_1(n4,n1,1), e4_5(n4,n5,1),
        e5_2(n5,n2,1), e5_4(n5,n4,1);

    Graph* G = new Graph();
    G->add_node(n0); G->add_node(n1);G->add_node(n2);
    G->add_node(n3); G->add_node(n4);G->add_node(n5);

    G->Edges = {e0_1, e0_3, e1_0, e1_4, e1_2,
                e2_1, e2_5, e3_0, e3_4, e4_3, e4_1, e4_5,
                e5_2, e5_4};
    G->fill_neighbors();
    G->fill_METIS_values();
    using namespace std::chrono;
    duration<double> time_span2;
    unsigned int* d = Parallel_SSSP(G,time_span2);
    std::cout << "Graph Partionning result: " << " ";
    for(int i=0;i<G->number_nodes;i++){
        std::cout << d[i] << " ";
    }
    std::cout << std::endl;

}   

void test_seq_vs_graph_part(){
    Graph *gra =  new Graph;
    gra->random_nodes(1000,20);
    gra->fill_METIS_values();
    Dijkstra dijk = Dijkstra(gra, 0);
    using namespace std::chrono;
    unsigned int* d,*d1;
    duration<double> time_span2;
    d = Parallel_SSSP(gra,time_span2,0);
    // std::cout << "Finished Graph Partionning" << std::endl;
    //Dijk Seq
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    d1 = Sequential_Dijkstra_Two_Queue(gra, 0);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span1 = duration_cast<duration<double> >(t2 - t1);
    // std::cout << "Finished Seq" << std::endl;

    std::cout << "Comparing" << std::endl;
    double counter = 0;
    for(int i=0;i<gra->number_nodes;i++){
        if(d[i] == d1[i]){
            counter += 1;
        }
        else{
            std::cout << "Fail! : d = " << d[i] << " and d1 = "<< d1[i] << std::endl; 
        }
    }
    std::cout <<"... Success rate: "<<(double) counter/gra->number_nodes*100 << std::endl;
    std::cout << "Ratio = " << time_span2.count()/time_span1.count() << std::endl;
    std::cout << "Time TwoQ Seq: " << time_span1.count() << " , Time TwoQ Parallel: " << time_span2.count() << std::endl;
}