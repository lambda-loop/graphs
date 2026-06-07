#include "adjacency_matrix.h" // Importando a estrutura do seu grupo
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>

struct UnionFind {
    std::map<short, short> pai;
    std::map<short, short> rank;

    UnionFind(const std::map<short, std::set<std::pair<short, float>>>& data) {
        for (const auto& [node, neighbors] : data) {
            pai[node] = node;
            rank[node] = 0;
        }
    }

    //descobre a qual componente (raiz) um vértice pertence
    short encontrar(short i) {
        if (pai[i] == i) return i;
        return pai[i] = encontrar(pai[i]); 
    }

    //une dois componentes diferentes em um só
    void unir(short i, short j) {
        short raiz_i = encontrar(i);
        short raiz_j = encontrar(j);

        if (raiz_i != raiz_j) {
            //une as árvores balanceando a altura
            if (rank[raiz_i] < rank[raiz_j]) pai[raiz_i] = raiz_j;
            else if (rank[raiz_i] > rank[raiz_j]) pai[raiz_j] = raiz_i;
            else {
                pai[raiz_j] = raiz_i;
                rank[raiz_i]++;
            }
        }
    }
};

graph::Graph<short, float> generateBoruvkaMST(std::string graph_file_path) {
    auto original_graph = graph::Graph<short, float>(graph_file_path);
    auto result_graph = graph::Graph<short, float>();

    UnionFind uf(original_graph.data);
    
    //começa com n componentes
    int num_componentes = original_graph.data.size();
    
    if (num_componentes == 0) return result_graph;

    int iteracao = 1;

    //o loop continua até todos os componentes se fundirem em 1 só
    while (num_componentes > 1) {
        std::cout << "\n=== Iniciando Iteracao " << iteracao << " ===" << std::endl;
        
        //estrutura para guardar a aresta "mais barata" de cada componente
        //chave: ID do componente raiz - valor: <origem, destino, peso>
        std::map<short, std::tuple<short, short, float>> mais_barata;

        bool grafo_tem_arestas = false;

        // PASSO 1: FASE DE BUSCA
        // varremos o grafo inteiro para cada componente achar sua melhor ponte
        for (const auto& [src, vizinhos] : original_graph.data) {
            for (const auto& [dest, peso] : vizinhos) {
                
                // evita olhar a mesma conexão de "volta"
                if (src > dest) continue; 
                
                short comp1 = uf.encontrar(src);
                short comp2 = uf.encontrar(dest);

                // só avaliamos se a aresta conecta componentes diferente (ou seja nao forma ciclo)
                if (comp1 != comp2) {
                    grafo_tem_arestas = true;
                    
                    // se o componente 1 ainda não escolheu nada, ou se essa aresta for mais barata que a atual dele: atualiza!
                    if (mais_barata.find(comp1) == mais_barata.end() || std::get<2>(mais_barata[comp1]) > peso) {
                        mais_barata[comp1] = {src, dest, peso};
                    }
                    
                    // mesma lógica para o componente 2
                    if (mais_barata.find(comp2) == mais_barata.end() || std::get<2>(mais_barata[comp2]) > peso) {
                        mais_barata[comp2] = {src, dest, peso};
                    }
                }
            }
        }

        // se passamos por tudo e não há como interligar os restantes, o grafo é quebrado/desconexo
        if (!grafo_tem_arestas) {
            std::cout << "Nao ha mais conexoes. Grafo desconexo!" << std::endl;
            break;
        }

        bool adicionou_nesta_rodada = false;

        // PASSO 2: FASE DE FUSÃO
        // pegamos as arestas escolhidas no passo 1 e construímos a árvore
        for (const auto& [comp, aresta] : mais_barata) {
            auto [src, dest, peso] = aresta;
            
            // precisamos checar novamente a raiz, pois um componente pode já ter sido unido a outro nesta mesma iteração
            short raiz1 = uf.encontrar(src);
            short raiz2 = uf.encontrar(dest);

            if (raiz1 != raiz2) { 
                uf.unir(raiz1, raiz2); // cola os dois no Union-Find
                result_graph.addEdge(src, dest, peso); // adiciona na resposta oficial
                
                num_componentes--; // reduz a contagem de "ilhas" isoladas
                adicionou_nesta_rodada = true;
                
                std::cout << " -> Componentes unidos via aresta (" << src << ", " << dest 
                          << ") com peso: " << peso << std::endl;
            }
        }

        // se nada for adicionado quebramos para evitar loop infinito
        if (!adicionou_nesta_rodada) break; 
        
        if (num_componentes == 1) {
            std::cout << "-> Arvore pronta!" << std::endl;
        } else {
            std::cout << "-> Restam " << num_componentes << " componentes soltos." << std::endl;
        }

        iteracao++;
    }

    return result_graph;
}

int main() {
    std::string arquivo = "grafo.txt";

    std::cout << "------------- Grafo Original (Boruvka) -------------" << std::endl;
    auto graph = graph::Graph<short, float>(arquivo);
    graph.printGraph();

    std::cout << "\n------------- Construindo Arvore Geradora Minima -------------" << std::endl;
    auto mst = generateBoruvkaMST(arquivo);
    
    std::cout << "\n------------- Resultado Final (MST) -------------" << std::endl;
    mst.printGraph();
    
    // calculando o custo total
    float custo_total = 0;
    for (const auto& [src, vizinhos] : mst.data) {
        for (const auto& [dest, peso] : vizinhos) {
            if (src < dest) custo_total += peso;
        }
    }
    std::cout << "Custo Total da Arvore: " << custo_total << std::endl;

    return 0;
}