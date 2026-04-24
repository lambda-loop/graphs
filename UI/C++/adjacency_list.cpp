#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include "graph.h"

using namespace std;

class AdjacencyList : public Graph {
private: 
  map<int, vector<int>> adj;
  bool isDirected;

public: 

  AdjacencyList(bool directed = false) : isDirected(directed) {
  }

  AdjacencyList(std::map<int, std::vector<int>> initialAdj, bool directed = false) 
        : adj(std::move(initialAdj)), isDirected(directed) {
  }

  void addVertex(int node) {
    // Ensure non-duplicate vertices
    // int node will be vertex's label
    if (adj.find(node) == adj.end()) {
      adj[node] = vector<int>();
    }
  }

  void addEdge(int from, int to) {
    // Ensure vertices exist before adding edges
    addVertex(from);
    addVertex(to);
    adj[from].push_back(to);
    if (!isDirected) {
      adj[to].push_back(from);
    }
  }

  void removeVertex(int node){
    // Remove vertex and all associated edges
    adj.erase(node);
    for (auto& [key, neighbors] : adj) {
      neighbors.erase(remove(neighbors.begin(), neighbors.end(), node), neighbors.end());
    }
  }

  void printGraph() {
    for (const auto& [node, neighbors] : adj) {
      cout << node << ": ";
      for (int neighbor : neighbors) {
        cout << neighbor << " ";
      }
      cout << endl;
    }
  }

  vector<int> getNeighbors(int node){
    return adj[node];
  }

};


