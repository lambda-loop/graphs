// Determinação de articulações e blocos (biconectividade), utilizando obrigatoriamente a função lowpt.(GRAFO3)
#include <iostream>
#include <vector>
#include <functional>
#include "biconectividade.h"
#include "MatrizDeAdjacencia.h"

int main() {

    MatrizDeAdjacencia<char> g3("./dados_trabalho_01/GRAFO_3.txt"); 
    Biconectividade bico;

    auto getNeighbors = [&](int v) { 
        vector<int> n;
        for(int j=0; j<g3.numVertices; j++) 
            if(g3.matriz[v][j]) n.push_back(j);
        return n;
    };

    bico.encontrarBlocos(0, -1, getNeighbors);

    return 0;
}