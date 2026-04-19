// 20 - Busca em PROFUNDIDADE (DFS), com determinação de profuindidade de entrada e de saída de cada vértice e definição de arestas de árvore, retorno, avanço ou cruzamento. 


#include <iostream>
#include <set>
#include <map>
#include <vector>

#include "DFS.h" 

// --- Função auxiliar para imprimir os resultados da sua DFS (Versão INT) ---
void imprimeDFS(DFS* no_atual, std::set<int>& impressos) {
    if (impressos.count(no_atual->val)) return;
    impressos.insert(no_atual->val);

    std::cout << "\n[ Vertice " << no_atual->val << " ]\n";
    std::cout << "  -> Filhos (Arvore): ";
    for (auto* filho : no_atual->sons) std::cout << filho->val << " ";
    std::cout << "\n  -> Retorno: ";
    for (auto* ret : no_atual->return_edges) std::cout << ret->val << " ";
    std::cout << "\n  -> Avanco: ";
    for (auto* fwd : no_atual->forward_edges) std::cout << fwd->val << " ";
    std::cout << "\n  -> Cruzamento: ";
    for (auto* cross : no_atual->cross_edges) std::cout << cross->val << " ";
    std::cout << "\n";

    for (auto* filho : no_atual->sons) {
        imprimeDFS(filho, impressos);
    }
}

// --- Função auxiliar com Gambi-Design para imprimir CHARS ---
void imprimeDFS2(DFS* no_atual, std::set<int>& impressos) {
    if (impressos.count(no_atual->val)) return;
    impressos.insert(no_atual->val);

    std::cout << "\n[ Vertice '" << (char)no_atual->val << "' ]\n";
    std::cout << "  -> Filhos (Arvore): ";
    for (auto* filho : no_atual->sons) std::cout << (char)filho->val << " ";
    std::cout << "\n  -> Retorno: ";
    for (auto* ret : no_atual->return_edges) std::cout << (char)ret->val << " ";
    std::cout << "\n  -> Avanco: ";
    for (auto* fwd : no_atual->forward_edges) std::cout << (char)fwd->val << " ";
    std::cout << "\n  -> Cruzamento: ";
    for (auto* cross : no_atual->cross_edges) std::cout << (char)cross->val << " ";
    std::cout << "\n";

    for (auto* filho : no_atual->sons) {
        imprimeDFS2(filho, impressos);
    }
}

int main() {
    // ==========================================
    // GRAFO 2 (Números)
    // ==========================================
    std::map<int, std::vector<int>> mapa2 = {
        {1, {2}}, {2, {3}}, {3, {1, 4}}, {4, {5}},
        {5, {6, 8}}, {6, {7}}, {7, {6, 9}}, {8, {4, 10}},
        {9, {8}}, {10, {12}}, {11, {12}}, {12, {13}}, {13, {12}}
    };

    std::cout << "=======================================\n";
    std::cout << "RODANDO DFS NO MAPA 2 (NUMEROS)\n";
    std::cout << "=======================================\n";
    ListaDeAdjacencia<int> g2(mapa2);
    DFS raiz_dfs2(g2, 1); // Começando no vértice 1

    std::set<int> impressos2;
    imprimeDFS(&raiz_dfs2, impressos2);

    // O REQUISITO DO ENUNCIADO AQUI:
    std::cout << "\n>>> Tempos de Entrada (PES) e Saida (PSS) <<<\n";
    for (auto const& [vertice, tempo_entrada] : raiz_dfs2.PES) {
        std::cout << "Vertice " << vertice 
                  << " | Entrada: " << tempo_entrada 
                  // Pega a saída no PSS (se o nó foi finalizado, ele está lá)
                  << " | Saida: " << (raiz_dfs2.PSS.count(vertice) ? std::to_string(raiz_dfs2.PSS[vertice]) : "N/A") 
                  << "\n";
    }

    // ==========================================
    // GRAFO 3 (Letras convertidas pra INT)
    // ==========================================
    std::map<int, std::vector<int>> mapa3 = {
        {'a', {'b', 'e', 'f'}}, {'b', {'c'}}, {'c', {'a'}}, {'d', {'c'}},
        {'f', {'e', 'g'}}, {'g', {'d'}}, {'h', {'i', 'l'}}, {'i', {'j'}},
        {'j', {'g', 'k'}}, {'k', {'i'}}, {'l', {'k', 'm'}}, {'m', {'h'}},
        {'n', {'o', 'p', 'q'}}, {'o', {'m'}}, {'p', {'q'}}, {'q', {'n'}}
    };

    std::cout << "\n\n=======================================\n";
    std::cout << "RODANDO DFS NO MAPA 3 (LETRAS ASCII)\n";
    std::cout << "=======================================\n";
    ListaDeAdjacencia<int> g3(mapa3);
    DFS raiz_dfs3(g3, 'n'); // Começando no vértice 'n' que alcança todo mundo

    std::set<int> impressos3;
    imprimeDFS2(&raiz_dfs3, impressos3);

    // O REQUISITO DO ENUNCIADO AQUI:
    std::cout << "\n>>> Tempos de Entrada (PES) e Saida (PSS) <<<\n";
    for (auto const& [vertice, tempo_entrada] : raiz_dfs3.PES) {
        std::cout << "Vertice '" << (char)vertice 
                  << "' | Entrada: " << tempo_entrada 
                  << " | Saida: " << (raiz_dfs3.PSS.count(vertice) ? std::to_string(raiz_dfs3.PSS[vertice]) : "N/A") 
                  << "\n";
    }

    return 0;
}
