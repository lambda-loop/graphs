#include <iostream>
#include <string>

#include "MatrizDeAdjacencia.h"
#include "VerticesAdjacentes.h"

template <typename T>
void verificarTodasAdjacenciasDoArquivo(std::string arquivoGrafo) {
    std::cout << "\n>>> Lendo grafo de: " << arquivoGrafo << " <<<\n";

    MatrizDeAdjacencia<T> g(arquivoGrafo);

    std::cout << "--- Adjacências ---\n";
    
    VerticesAdjacentes<T> adjacentes;

    for (int i = 0; i < g.numVertices; ++i) {
        
        // começa o 'j' a partir de 'i + 1' para
        // nao testar o vértice com ele mesmo (ex: a com a)
        // nao testar a mesma coisa duas vezes (ex: se já testou 'a com b', não testa 'b com a')
        for (int j = i + 1; j < g.numVertices; ++j) {
            
            T vertice1 = g.indiceParaNome[i];
            T vertice2 = g.indiceParaNome[j];

            adjacentes.verificar(g, vertice1, vertice2);
        }
    }
    
    std::cout << "------------------------------------------\n";
}

int main() {
    verificarTodasAdjacenciasDoArquivo<char>("./dados_trabalho_01/GRAFO_1.txt");

    verificarTodasAdjacenciasDoArquivo<int>("./dados_trabalho_01/GRAFO_2.txt");

    return 0;
}