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

    // No Zig: var Z = std.AutoArrayHashMap(u32, void).init(self.allocator);
    // Em C++, um std::set faz exatamente o papel de um HashMap cujas chaves são os nós visitados.
    std::set<short> Z; 

    // Pega o primeiro vértice disponível (equivalente ao comentário "u pick the first vertice. Whatever..")
    short V = original_graph.data.begin()->first;
    Z.insert(V);

    int num_keys = original_graph.data.size();

    // while (Z.count() < NUM_KEYS)
    while (Z.size() < num_keys) {
        float min_weight = std::numeric_limits<float>::infinity();
        short min_from = -1;
        short min_to = -1;
        bool edge_found = false;

        // for (Z.keys()) |green| -> iterando pelos nós já visitados
        for (short green : Z) {
            auto it = original_graph.data.find(green);
            if (it == original_graph.data.end()) continue;

            const auto& from_green_edges = it->second;

            // for (from_green_edges.items) |orange| -> iterando pelas arestas do nó visitado
            for (const auto& [orange_to, orange_weight] : from_green_edges) {
                
                // if (!Z.contains(orange.to) and orange.weight < min)
                if (Z.find(orange_to) == Z.end() && orange_weight < min_weight) {
                    min_weight = orange_weight;
                    min_from = green;
                    min_to = orange_to;
                    edge_found = true;
                }
            }
        }

        // Se nenhuma aresta válida for encontrada, o grafo é desconexo.
        if (!edge_found) {
            std::cout << "Nao ha mais conexoes possiveis. Grafo desconexo!" << std::endl;
            break; 
        }

        // try Z.put(MIN_VERTICE.to, {});
        Z.insert(min_to);
        
        // try T.append(MIN_VERTICE); -> Ao invés de uma lista, já inserimos no grafo final
        result_graph.addEdge(min_from, min_to, min_weight);
        
        // Opcional: imprimir o progresso da mesma forma que o Boruvka
        // std::cout << " -> Aresta adicionada (" << min_from << ", " << min_to 
        //           << ") com peso: " << min_weight << std::endl;
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
