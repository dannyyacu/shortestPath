#include <stdio.h>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

typedef vector<vector<int> > Matrix;

class Graph{

  Matrix graph;

public:
  Graph(int nNodes, int nEdges){
    // you don't have to change anything here. This function will generate a random weighted graph given the
    // desired parameters (number of nodes and number of edges)
    srand (time(NULL));

    graph = Matrix(nNodes, vector<int>(nNodes,0));

    for(int i=0; i<nEdges; i++){
      //random weight
      int weight = 0;
      while(weight == 0) weight = rand()%(101);
      int node1, node2;

      do{
        node1 = rand()%(nNodes);
        node2 = rand()%(nNodes);
      }while(node1 == node2 && !connected(node1,node2));

      graph[node1][node2] = graph[node2][node1] = weight;
    }

  }

  int size(){
   return graph.size();
  }

  list<int> getConnectedNodes(int n){
    list<int> connectedNodes;

    for(int i=0; i < graph.size(); i++){
      if (connected(n, i)){
        connectedNodes.push_back(i);
      }
    }

    return connectedNodes;
  }

  int getEdgeWeight(int n, int n2){
    return graph[n][n2];
  }

  bool connected(int n, int n2){
    if (graph[n][n2] == graph[n2][n])
      return true;
    return false;
  }

  void print_graph(){}
  
};
