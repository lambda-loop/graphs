#include <vector>

template <size_t N>
class AdjacencyMatrix {
private: 
  std::array<std::array<int, N>, N> edges{};
public: 
  template <typename Iter>
  static AdjacencyMatrix mkDirected (Iter begin, Iter end) {
    AdjacencyMatrix graph;
    for (auto it = begin; it != end; ++it) {
      graph->edges[it->first][it->second] = 1;
    }

    return graph;
  }

  template <typename Iter>
  static AdjacencyMatrix mkNDirected(Iter begin, Iter end) {
    AdjacencyMatrix graph;
    for (auto it = begin; it != end; ++it) {
      graph->edges[it->first][it->second] = 1;
      graph->edges[it->second][it->first] = 1;
    }

    return graph;
  }

  int get(int i, int j) {
    return edges[i][j];
  }
};


