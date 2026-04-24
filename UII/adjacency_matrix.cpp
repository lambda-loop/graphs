
#include <set>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
// #include "graph.h"

// THATS TRASH!!!
// using namespace std;


// ADVICE: use snake_case_much_much_please :P
// please no 😡
template <typename T>
struct AdjacencyList /* : public Graph */ {
// private: 
  std::map<T, std::set<T>> data;
  bool is_directed;

// public: 

  AdjacencyList(bool directed = false) : isDirected(directed) {
  }

  AdjacencyList(std::map<int, std::set<T>> initial_data, bool directed = false) 
        : data(std::move(initial_data)), is_directed(directed) {
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


