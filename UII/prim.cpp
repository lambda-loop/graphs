
#include "adjacency_matrix.h"

// só mande grafos conexos!!!
template <typename T, typename W>
requires std::totally_ordered<T> && std::totally_ordered<W>
graph::Graph<T, W> prim (graph::Graph<T, W> &G, T V0) {
  // is it ordered necessary by weight?
  std::pair<T, W> lowest_edge = *G.data[V0].begin(); 
  std::set<T> visited = { V0 };
  std::set<std::tuple<T, T, W>> edges = { 
    std::make_tuple (
      V0, 
      lowest_edge.first, 
      lowest_edge.second 
    )
  };


  const size_t num_keys = G.data.size();

  T V = lowest_edge.second;
  std::map<T, > iters; 
  iters[V] = G[V].begin();


  while (visited.size() < num_keys) {


    // I WILL BE RIGHT BACK!



  }

    // ...
  // }




}

int main() {
    graph::Graph<int, int> meu_grafo; // Assumindo que seu construtor seja assim
    prim(meu_grafo, 1);
    return 0;
}
