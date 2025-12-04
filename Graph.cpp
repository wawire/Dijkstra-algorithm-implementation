#include "Graph.h"
#include <iostream>
#include <climits>

Graph::Graph(int n){
    this->numVertices = n;

    // Allocate adjacency matrix
    this->adjMatrix = new int*[n];
    for(int i = 0; i < n; i++){
        this->adjMatrix[i] = new int[n];
        for(int j = 0; j < n; j++){
            this->adjMatrix[i][j] = 0;
        }
    }

    // Allocate vertices array
    this->vertices = new Vertex[n];
    for(int i = 0; i < n; i++){
        this->vertices[i].setIndex(i + 1); // 1-indexed for output
        this->vertices[i].setDegree(0);
    }
}

Graph::~Graph(){
    // Free adjacency matrix
    for(int i = 0; i < this->numVertices; i++){
        delete[] this->adjMatrix[i];
    }
    delete[] this->adjMatrix;

    // Free vertices array
    delete[] this->vertices;
}

void Graph::addEdge(int u, int v, int weight){
    // Convert from 1-indexed to 0-indexed
    int u_idx = u - 1;
    int v_idx = v - 1;

    // Undirected graph - add both directions
    this->adjMatrix[u_idx][v_idx] = weight;
    this->adjMatrix[v_idx][u_idx] = weight;
}

void Graph::printAdjMatrix(){
    std::cout << "The adjacency matrix of G is:" << std::endl;
    for(int i = 0; i < this->numVertices; i++){
        for(int j = 0; j < this->numVertices; j++){
            std::cout << this->adjMatrix[i][j];
            if(j < this->numVertices - 1){
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Graph::calculateDegrees(){
    for(int i = 0; i < this->numVertices; i++){
        int degree = 0;
        for(int j = 0; j < this->numVertices; j++){
            if(this->adjMatrix[i][j] != 0){
                degree++;
            }
        }
        this->vertices[i].setDegree(degree);
    }
}

int* Graph::getOddDegreeNodes(int& count){
    // First count how many odd degree nodes there are
    count = 0;
    for(int i = 0; i < this->numVertices; i++){
        if(this->vertices[i].getDegree() % 2 == 1){
            count++;
        }
    }

    // Allocate array for odd degree nodes
    int* oddNodes = new int[count];
    int idx = 0;
    for(int i = 0; i < this->numVertices; i++){
        if(this->vertices[i].getDegree() % 2 == 1){
            oddNodes[idx++] = this->vertices[i].getIndex();
        }
    }

    return oddNodes;
}

void Graph::printOddDegreeNodes(){
    int count = 0;
    int* oddNodes = getOddDegreeNodes(count);

    std::cout << "The nodes with odd degrees in G are:" << std::endl;
    std::cout << "O = { ";
    for(int i = 0; i < count; i++){
        std::cout << oddNodes[i];
        if(i < count - 1){
            std::cout << " ";
        }
    }
    std::cout << " }" << std::endl;

    delete[] oddNodes;
}

void Graph::dijkstra(int source){
    // Convert to 0-indexed
    int src = source - 1;

    // Initialize distances and visited array
    int* dist = new int[this->numVertices];
    bool* visited = new bool[this->numVertices];

    for(int i = 0; i < this->numVertices; i++){
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    // Dijkstra's algorithm
    for(int count = 0; count < this->numVertices - 1; count++){
        // Find minimum distance vertex not yet visited
        int minDist = INT_MAX;
        int minIdx = -1;

        for(int v = 0; v < this->numVertices; v++){
            if(!visited[v] && dist[v] < minDist){
                minDist = dist[v];
                minIdx = v;
            }
        }

        if(minIdx == -1) break;

        visited[minIdx] = true;

        // Update distances of adjacent vertices
        for(int v = 0; v < this->numVertices; v++){
            if(!visited[v] && this->adjMatrix[minIdx][v] != 0){
                int newDist = dist[minIdx] + this->adjMatrix[minIdx][v];
                if(newDist < dist[v]){
                    dist[v] = newDist;
                }
            }
        }
    }

    // Print results
    std::cout << "The shortest path lengths from Node " << source << " to all other nodes are:" << std::endl;
    for(int i = 0; i < this->numVertices; i++){
        std::cout << (i + 1) << ": " << dist[i] << std::endl;
    }

    delete[] dist;
    delete[] visited;
}

void Graph::runDijkstraFromOddNodes(){
    int count = 0;
    int* oddNodes = getOddDegreeNodes(count);

    for(int i = 0; i < count; i++){
        std::cout << std::endl;
        dijkstra(oddNodes[i]);
    }

    delete[] oddNodes;
}
