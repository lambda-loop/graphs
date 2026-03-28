#include <list>
#include <optional>
#include <set>
#include <stack>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include "graph.h"

struct DeepTree {
  int val;
  std::list<DeepTree*> sons; 
  std::list<DeepTree*> return_arrows;
};

class AdjacencyList : public Graph {
private: 
  std::vector<std::set<int>> adj;
  bool is_directed;

public: 

  AdjacencyList(std::vector<std::set<int>> initialAdj, bool directed = false) 
        : adj(std::move(initialAdj)), is_directed(directed) {
  }

  std::vector<int> getNeighbors(int node){
/*     return adj[node]; */
  }


  void deepFirstSearch_(int V) {
    int N = this->adj.size();

    using Iter = decltype(this->adj[0].begin());
    std::vector<std::optional<Iter>> visited(N, std::nullopt);

    std::vector<int> pred(N, -1);
    std::stack <int> P;

    P.push(V);
    std::cout << "empilha " << V << std::endl;
    visited[V] = std::make_optional(this->adj[V].begin());

    while (!P.empty()) {
      if (*visited[V] != this->adj[V].end()) {
        int w = **visited[V];
        std::cout << "visita" << w << std::endl;
        pred[w] = V;
        (*visited[V])++;

        if (!visited[w].has_value()) {
          std::cout << "empilha" << w << std::endl;
          P.push(w);
          visited[w] = std::make_optional(this->adj[w].begin());
          V = w;
        } // case is pred..?
      } else { 
        P.pop(); 
        if (!P.empty()) V = P.top();
        std::cout << "desempilha" << std::endl; 
      }
    }

  }

  void print() const {
    std::cout << "--- Lista de Adjacencia ---\n";
    for (size_t i = 0; i < adj.size(); ++i) {
      // Converte o índice de volta para o caractere correspondente
      char node_name = (i == 9) ? 's' : static_cast<char>(i + 'a');
      
      std::cout << "A(" << node_name << ") = { ";
      
      // Itera pelo set de vizinhos
      auto it = adj[i].begin();
      while (it != adj[i].end()) {
        char neighbor_name = (*it == 9) ? 's' : static_cast<char>(*it + 'a');
        std::cout << neighbor_name;
        
        ++it;
        if (it != adj[i].end()) {
          std::cout << ", ";
        }
      }
      std::cout << " }\n";
    }
    std::cout << "---------------------------\n";
  }
    
 };


AdjacencyList class_example() {
  std::map<char, int> dic;
  for (int c = 'a'; c <= 'i'; c++) {
    dic[c] = c-'a';
  } dic['s'] = 'j'-'a';

  std::set<int> E_s = { dic['a'], dic['g'], dic['b'] };
  std::set<int> E_a = { dic['c'], dic['d'], dic['s'] };
  std::set<int> E_b = { dic['s'] };
  std::set<int> E_c = { dic['a'], dic['d'], dic['e'] };
  std::set<int> E_d = { dic['a'], dic['c'], dic['e'] };
  std::set<int> E_e = { dic['c'], dic['d'], dic['f'] };
  std::set<int> E_f = { dic['e'] };
  std::set<int> E_g = { dic['s'], dic['h'] };
  std::set<int> E_h = { dic['g'], dic['i'] };
  std::set<int> E_i = { dic['h'] };

  std::vector<std::set<int>> v; 
  v.push_back(E_a);
  v.push_back(E_b);
  v.push_back(E_c);
  v.push_back(E_d);
  v.push_back(E_e);
  v.push_back(E_f);
  v.push_back(E_g);
  v.push_back(E_h);
  v.push_back(E_i);
  v.push_back(E_s);

  return AdjacencyList(v);
}

int main () {
  AdjacencyList g = class_example();
  g.print();
  g.deepFirstSearch_('j'-'a');


}


