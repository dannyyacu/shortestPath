#include "Graph.h"
#include "Timer.h"
#include <queue>
#include <iomanip>

using namespace std;

typedef pair<int, int> iPair;

vector<int> computeShortestPath(Graph g, int node){

  vector<int> D(g.size(), numeric_limits<int>::max());

  D[node] = 0;

  priority_queue<iPair, vector<iPair>,  greater<iPair > > pq;

  pq.push(make_pair(0, node));

  int u;

  while (pq.size() != 0){

    u = pq.top().second; 
    pq.pop(); 

    list<int> adjacentVertexes = g.getConnectedNodes(u);
    list<int>::iterator it;

    for (it = adjacentVertexes.begin(); it != adjacentVertexes.end(); it++){
      int z = *it;
      int w = g.getEdgeWeight(u, z);

      if ( D[u] + w < D[z] ) { 
        D[z] = D[u] + w; 
        pq.push(make_pair(D[z], z)); 
      } 
    }
  }

  return D;

};

vector<vector<int> > computeAllPairsShortestPath(Graph g){

  vector<vector<int> > shortestPath;
  for(int i=0; i<g.size(); i++){
    shortestPath.push_back(computeShortestPath(g, i));
  }

  return shortestPath;

};

Matrix computeAllPairsShortestPathDynamicProgramming(Graph g){
  int n = g.size();

  vector<vector<vector<int> > > D(n, vector<vector<int> >(n, vector<int>(n)));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        D[0][i][i] = 0;
      } 

      if (g.connected(i,j)) {
        D[0][i][j] = g.getEdgeWeight(i,j);
      } 

      else {
        D[0][i][j] = numeric_limits<int>::max();
      }
    }
  }

  for (int k = 1; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        D[k][i][j] = min(D[k-1][i][j], D[k-1][i][k] + D[k-1][k][j]);
      }
    }
  }

  return D[n - 1];

};

bool compareResults(Graph g, Matrix a, Matrix b){

  for(int i=0; i<g.size(); i++){
    for(int j=0; j<g.size(); j++){
      if(a[i][j] != b[i][j]){
        return false;
      }
    }
  }

  return true;
}


int main(){

  //create graph as a random matrix
  Graph g(10,10);
  cout << "Graph generated " << endl;

  //compute shortest path
  Timer time;
  time.start();
  Matrix a = computeAllPairsShortestPath(g);
  time.stop();
  cout << "Time with Dijkstra's algorithm: " << time.getElapsedTimeInSec() << endl;

  // compute all possible shortest paths
  time.start();
  Matrix b = computeAllPairsShortestPathDynamicProgramming(g);
  time.stop();
  cout << "Time with Dynamic programming: " << time.getElapsedTimeInSec() << endl;

  //compute by dynamic programming approach
  if(compareResults(g,a,b)){
    cout << "They are the same" << endl;
  }
  else{
    cout << "Different" << endl;
  }

}