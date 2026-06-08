
#include "adjacency_matrix.h"

#include <concepts>
#include <iostream>
#include <optional>
#include <set>
#include <string>
#include <tuple>
#include <vector>

template <typename T, typename W>
graph::Graph<T, W> prim(graph::Graph<T, W> &graph_ref, T start_vertex) {
  graph::Graph<T, W> mst;

  std::vector<T> visited_order = {start_vertex};
  std::set<T> visited_lookup = {start_vertex};

  while (visited_lookup.size() < graph_ref.data.size()) {
    std::optional<std::tuple<T, T, W>> best_edge;

    for (const T &from : visited_order) {
      const auto &neighbors = graph_ref.data.at(from);

      for (const auto &[to, weight] : neighbors) {
        if (visited_lookup.find(to) != visited_lookup.end()) {
          continue;
        }

        if (!best_edge.has_value() || weight < std::get<2>(*best_edge)) {
          best_edge = std::make_tuple(from, to, weight);
        }
      }
    }

    if (!best_edge.has_value()) {
      break;
    }

    const auto &[from, to, weight] = *best_edge;
    mst.addEdge(from, to, weight);
    visited_lookup.insert(to);
    visited_order.push_back(to);
  }

  return mst;
}

template <typename T, typename W>
graph::Graph<T, W> generateMinimumSpanningTree(const std::string &graph_file_path) {
  graph::Graph<T, W> original_graph(graph_file_path);

  if (original_graph.data.empty()) {
    return graph::Graph<T, W>();
  }

  return prim(original_graph, original_graph.data.begin()->first);
}

template <typename T, typename W>
W totalWeight(const graph::Graph<T, W> &graph_ref) {
  W total = W{};

  for (const auto &[from, neighbors] : graph_ref.data) {
    for (const auto &[to, weight] : neighbors) {
      if (from < to) {
        total += weight;
      }
    }
  }

  return total;
}

int main() {
  const std::string arquivo = "grafo.txt";

  std::cout << "------------- Grafo Original (Prim) -------------" << std::endl;
  graph::Graph<short, float> graph(arquivo);
  graph.printGraph();

  std::cout << "\n------------- Construindo Arvore Geradora Minima -------------" << std::endl;
  auto mst = generateMinimumSpanningTree<short, float>(arquivo);

  std::cout << "\n------------- Resultado Final (MST) -------------" << std::endl;
  mst.printGraph();
  std::cout << "Custo Total da Arvore: " << totalWeight(mst) << std::endl;

  return 0;
}
