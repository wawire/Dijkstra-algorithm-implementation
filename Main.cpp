#include "Edge.h"
#include "Graph.h"
#include <iostream>

int main(){

    // start of the initial pipeline that loads the test case file stream from std::cin

    int numOfVertices;
    int numOfEdges;

    if(!std::cin.eof()){
        std::cin >> numOfVertices;
        std::cin >> numOfEdges;
    }
    else{
        std::cout<<"Input not found!"<<std::endl;
        return 1;
    }

    // Create graph
    Graph* graph = new Graph(numOfVertices);

    // Read edges and build graph
    for(int i = 0; i < numOfEdges; i++){
        int startVertice;
        int endVertice;
        int weight;
        std::cin >> startVertice;
        std::cin >> endVertice;
        std::cin >> weight;
        graph->addEdge(startVertice, endVertice, weight);
    }

    // Task 1: Print adjacency matrix
    graph->printAdjMatrix();

    // Calculate degrees for all vertices
    graph->calculateDegrees();

    // Task 2: Print odd degree nodes
    std::cout << std::endl;
    graph->printOddDegreeNodes();

    // Task 3: Run Dijkstra from all odd degree nodes
    graph->runDijkstraFromOddNodes();

    delete graph;

    return 0;
}