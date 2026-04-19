// Busca em Profundidade, a partir de um vértice em específico(GRAFO1, GRAFO3, Vértice inicial).
#include <iostream>
#include <vector>
#include <functional>
#include "MatrizDeAdjacencia.h"
#include "DFSFunction.h" 

using namespace std;

int main() {
    cout << "--- DFS GRAFO 1 ---" << endl;
    MatrizDeAdjacencia<char> GRAFO_1("./dados_trabalho_01/GRAFO_1.txt");

    char verticeInicial1 = 'a';
    int posicaoInicial1 = GRAFO_1.nomeParaIndice[verticeInicial1];

    /*
    Precisei colocar esse output de legenda porque a função de DFS feita por outra pessoa e implementada aqui está 
    em inglês e usando números ao invés de letras, para alterar teria que mexer na função original e estou com um pouco
    de medo de causar um bug 
    */ 
    cout << "Legenda: ";
    for(int i = 0; i < GRAFO_1.numVertices; i++)
        cout << "[" << i << "=" << GRAFO_1.indiceParaNome[i] << "] ";
    cout << "\nIniciando busca em: " << verticeInicial1 << endl;

    // A função DFS é agnóstica então implementei matriz de adjacência para checar os vizinhos
    auto vizinhos1 = [&](int u) -> vector<int> {
        vector<int> lista;
        for (int i = 0; i < GRAFO_1.numVertices; i++) {
            if (GRAFO_1.matriz[u][i] == 1) {
                lista.push_back(i);
            }
        }
        return lista;
    };

    DFS(posicaoInicial1, vizinhos1);

    // Essa seção segue a exata mesma estrutura do grafo 1. 
    cout << "\n--- DFS GRAFO 3 ---" << endl;
    MatrizDeAdjacencia<char> GRAFO_3("./dados_trabalho_01/GRAFO_3.txt");

    char verticeInicial3 = 'a';
    int posicaoInicial3 = GRAFO_3.nomeParaIndice[verticeInicial3];

    cout << "Legenda: ";
    for(int i = 0; i < GRAFO_3.numVertices; i++)
        cout << "[" << i << "=" << GRAFO_3.indiceParaNome[i] << "] ";
    cout << "\nIniciando busca em: " << verticeInicial3 << endl;

    auto vizinhos3 = [&](int u) -> vector<int> {
        vector<int> lista;
        for (int i = 0; i < GRAFO_3.numVertices; i++) {
            if (GRAFO_3.matriz[u][i] == 1) {
                lista.push_back(i);
            }
        }
        return lista;
    };

    DFS(posicaoInicial3, vizinhos3);

    return 0;
}