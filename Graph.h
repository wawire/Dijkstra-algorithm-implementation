#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"

class Graph{
    private:
        int numVertices;
        int** adjMatrix;
        Vertex* vertices;

    public:
        Graph(int n);
        ~Graph();
        void addEdge(int u, int v, int weight);
        void printAdjMatrix();
        void printOddDegreeNodes();
        void runDijkstraFromOddNodes();
        void dijkstra(int source);
        int* getOddDegreeNodes(int& count);
        void calculateDegrees();
};

#endif
