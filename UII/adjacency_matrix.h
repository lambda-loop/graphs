#pragma once 

#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <concepts>
#include <fstream>
#include <string>

// ADVICE: use snake_case_ for variables much_much_please :P
//         use camelCase   for functions 
namespace graph {

template <typename T, typename W>
requires std::totally_ordered<T> && std::totally_ordered<W>
struct Graph {
  std::map<T, std::set<std::pair<T, W>>> data;
  bool is_directed;

  Graph(bool directed = false) : is_directed(directed) { }

  Graph(std::map<T, std::set<std::pair<T, W>>> initial_data, bool directed = false) 
  : data(std::move(initial_data)), is_directed(directed) { }

  void safeAddVertex(T node) {
    // only if the vertice doesnt exist yet, it creates
    // it with an empty set
    if (data.find(node) == data.end()) {
      data[node] = std::set<std::pair<T, W>>();
    }
  }

  void addEdge(T from, T to, W weight) {
    data.try_emplace(from);
    data.try_emplace(to);

    data[from].emplace(to, weight);
    if (!is_directed) {
      data[to].emplace(from, weight);
    }
  }

  void printGraph() const {
    for (const auto& [node, neighbors] : data) {
      std::cout << node << ": ";
      for (const auto& [neighbor, weight] : neighbors) {
        std::cout << "(" << neighbor << ", " << weight << ") ";
      }
      std::cout << '\n';
    }
  }

  Graph(std::string graph_file_path, bool directed = false) : is_directed(directed){
    std::ifstream file_stream(graph_file_path);

    if (!file_stream.is_open()){
      std::cerr << "Error: Could not open graph file: " << graph_file_path << std::endl;
      return;
    }

    int total_vertices = 0;

    if(!(file_stream >> total_vertices)){
      return;
    }

    T from;
    T to;
    W weight;

    while(file_stream >> from >> to >> weight){
      addEdge(from, to, weight);
    }
  }

};

};



