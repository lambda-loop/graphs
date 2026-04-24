#include <vector>

template <size_t N, size_t M>
class IncidenceMatrix{
private: 
  std::array<std::array<int, N>, M> edges{};
public: 
  template <typename Iter>
  static IncidenceMatrix mkDirected (Iter begin, Iter end) {
    IncidenceMatrix graph;
    int count = 0;
    for (auto it = begin; it != end; ++it) {
      graph->edges[count][it->first]  = 1;
      graph->edges[count][it->second] = 1;
      count++;
    }

    return graph;
  }

  template <typename Iter>
  static IncidenceMatrix mkNDirected(Iter begin, Iter end) {
    IncidenceMatrix graph;
    int count = 0;
    for (auto it = begin; it != end; ++it) {
      graph->edges[count][it->first]  = -1;
      graph->edges[count][it->second] =  1;
      count++;
    }

    return graph;
  }

  std::pair<int, int> get(int i, int j) {
    // Assuming no repetitions or more than two
    for (int a = 0; a < N; a++) {
      int v1 = edges[a][i], v2 = edges[a][j];
      if (v1 != 0 && v2 != 0) {
        return std::make_pair(v1, v2);
      }
    }
    
    return std::make_pair(0, 0);
  }
};


