#include "adjacency_matrix.h" // Importando a estrutura do seu grupo
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <string>
#include <limits> // Necessário para simular o std::math.inf(f32) do Zig

graph::Graph<short, float> generatePrimMST(std::string graph_file_path) {
    auto original_graph = graph::Graph<short, float>(graph_file_path);
    auto result_graph = graph::Graph<short, float>();

    if (original_graph.data.empty()) {
        return result_graph;
    }

    std::set<short> Z; 

    short V = original_graph.data.begin()->first;
    Z.insert(V);

    int num_keys = original_graph.data.size();

    while (Z.size() < num_keys) {
        float min_weight = std::numeric_limits<float>::infinity();
        short min_from = -1;
        short min_to = -1;
        bool edge_found = false;

        for (short green : Z) {
            auto it = original_graph.data.find(green);
            if (it == original_graph.data.end()) continue;

            const auto& from_green_edges = it->second;

            for (const auto& [orange_to, orange_weight] : from_green_edges) {
                
                if (Z.find(orange_to) == Z.end() && orange_weight < min_weight) {
                    min_weight = orange_weight;
                    min_from = green;
                    min_to = orange_to;
                    edge_found = true;
                }
            }
        }

        if (!edge_found) {
            std::cout << "Nao ha mais conexoes possiveis. Grafo desconexo!" << std::endl;
            break; 
        }

        Z.insert(min_to);
        
        result_graph.addEdge(min_from, min_to, min_weight);
        
    }

    return result_graph;
}

int main() {
    std::string arquivo = "grafo.txt";

    std::cout << "------------- Grafo Original (Prim) -------------" << std::endl;
    auto graph = graph::Graph<short, float>(arquivo);
    graph.printGraph();

    std::cout << "\n------------- Construindo Arvore Geradora Minima -------------" << std::endl;
    auto mst = generatePrimMST(arquivo);
    
    std::cout << "\n------------- Resultado Final (MST) -------------" << std::endl;
    mst.printGraph();
    
    // Calculando o custo total (exatamente como feito no Boruvka)
    float custo_total = 0;
    for (const auto& [src, vizinhos] : mst.data) {
        for (const auto& [dest, peso] : vizinhos) {
            if (src < dest) custo_total += peso;
        }
    }
    std::cout << "Custo Total da Arvore: " << custo_total << std::endl;

    return 0;
}
