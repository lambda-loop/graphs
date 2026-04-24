
#include <set>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>



// ADVICE: use snake_case_ for variables much_much_please :P
//         use camelCase   for functions 

template <typename T>
struct AdjacencyList {
  std::map<T, std::set<T>> data;
  bool is_directed;


  AdjacencyList(bool directed = false) : is_directed(directed) {
  }

  AdjacencyList(std::map<int, std::set<T>> initial_data, bool directed = false) 
        : data(std::move(initial_data)), is_directed(directed) {
  }

  void safeAddVertex(int node) {
    // only if the vertice doesnt exist yet, it creates
    // it with an empty set
    if (data.find(node) == data.end()) {
      data[node] = std::set<int>();
    }
  }

  void addEdge(int from, int to) {
    // Ensure vertices exist before adding edges
    safeAddVertex(from);
    safeAddVertex(to);

    data[from].insert(to);
    if (!is_directed) data[to].insert(from);
  }

  // WARNING: NOT WORKING. Maybe impolement latter
  // void removeVertex(int node){
  //   // Remove vertex and all associated edges
  //   data.erase(node);
  //   for (auto& [key, neighbors] : data) {
  //     neighbors.erase(remove(neighbors.begin(), neighbors.end(), node), neighbors.end());
  //   }
  // }

  void printGraph() {
    for (const auto& [node, neighbors] : data) {
      std::cout << node << ": ";
      for (int neighbor : neighbors) {
        std::cout << neighbor << " ";
      }
      std::cout << std::endl;
    }
  }

};


