#include "adjacency_matrix.h"
#include <iostream>
#include <utility>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <queue>

/*
Seja G um grafo, D sua matriz de pesos das arestas

Ordene todas as arestas de G em ordem crescente dos pesos no vetor H

T <- H.first
i <- 2

Enquanto T.tamanho < q. de arestas:

    se T ∪ hᵢ é acíclico, então:
        T <- T ∪ hᵢ 

    i <- i+1

Ao final, T será arvore geradora mínima

*/

template <typename T, typename W>
bool hasCycles(const std::map<T, std::set<std::pair<T, W>>>& adj_list, T src, T dest){

    if (adj_list.find(src) == adj_list.end() || adj_list.find(dest) == adj_list.end()) return false;

    std::stack<std::pair<T, T>> s;
    std::set<T> visited;

    s.push({src, src});

    while(!s.empty()){

        auto [current, parent] = s.top();
        s.pop();

        if (current == dest) return true;

        if (visited.find(current) == visited.end()){
            visited.insert(current);

            auto it = adj_list.find(current);
            if (it != adj_list.end()){
                for (const auto& [neighbor, weight] : it->second){
                    if (neighbor == parent) continue;
                    s.push({neighbor,current});
                }
            }
        }
    }

    return false;
}

template <typename T, typename W>
auto OrderEdgesByWeight(const std::map<T, std::set<std::pair<T, W>>>& data) {
    
    std::priority_queue<
        std::pair<W, std::pair<T, T>>,
        std::vector<std::pair<W, std::pair<T, T>>>,
        std::greater<std::pair<W, std::pair<T, T>>>
    > pq;

    for (const auto& [src, neighbors] : data) {
        for (const auto& [dest, weight] : neighbors) {
            if (src > dest) continue; //ignoring edge duplicates
            pq.push({weight,{src, dest}});
        }
    }

    return pq;
}

graph::Graph<short, float> generateMinimumSpanningTree(std::string graph_file_path){
    auto original_graph = graph::Graph<short,float>(graph_file_path);
    auto result_graph = graph::Graph<short,float>();

    auto ordered_edges = OrderEdgesByWeight(original_graph.data);

    size_t target_edges = original_graph.data.size() - 1;
    size_t current_edges = 0;

    while (!ordered_edges.empty() && current_edges < target_edges){

        auto [weight, vertices] = ordered_edges.top();
        auto [src, dest] = vertices;

        ordered_edges.pop();

        if (!hasCycles(result_graph.data, src, dest)){

            result_graph.addEdge(src, dest, weight);
            current_edges++;
        }
    }

    return result_graph;
}

int main(){

    std::cout << "-------------Original Graph-----------------" << std::endl;
    auto graph = graph::Graph<short, float>(std::string("grafo.txt"));
    graph.printGraph();

    std::cout << "---------------------------------------" << std::endl;
    std::cout << "-------------Minimum Spanning Tree-----------------" << std::endl;
    auto minimumSpanningTree = generateMinimumSpanningTree("grafo.txt");
    minimumSpanningTree.printGraph();

    float custo_total = 0;
    for (const auto& [src, vizinhos] : minimumSpanningTree.data) {
        for (const auto& [dest, peso] : vizinhos) {
            if (src < dest) custo_total += peso;
        }
    }
    std::cout << "Custo Total da Arvore: " << custo_total << std::endl;
    return 0;
}

