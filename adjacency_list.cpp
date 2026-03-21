
#include <list>
#include <vector>

template <size_t N>
class AdjacencyMatrix {
private: 
  std::array<std::list<int>, N> edges{};

public: 
  template <typename Iter>
  static AdjacencyMatrix mkDirected (Iter begin, Iter end) {
    AdjacencyMatrix graph;
    for (auto it = begin; it != end; ++it) {
    }

    return graph;
  }

  template <typename Iter>
  static AdjacencyMatrix mkNDirected(Iter begin, Iter end) {
    AdjacencyMatrix graph;
    for (auto it = begin; it != end; ++it) {
    }

    return graph;
  }

  int get(int i, int j) {
  }
};


