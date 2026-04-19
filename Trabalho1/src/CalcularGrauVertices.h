
#pragma once

#include <iostream>
#include "MatrizDeAdjacencia.h" 

template <typename T>
struct CalculadorDeGrau {
    void calcularEImprimir(const MatrizDeAdjacencia<T>& grafo) {
        if (grafo.numVertices == 0) {
            std::cout << "Grafo vazio.\n";
            return;
        }

        std::cout << "\n=== GRAUS DOS VERTICES ===\n";

        // Percorre cada linha da matriz (cada vértice)
        for (int i = 0; i < grafo.numVertices; ++i) {
            int grauTotal = 0;

            // Percorre cada coluna para verificar as adjacências
            for (int j = 0; j < grafo.numVertices; ++j) {
                if (grafo.matriz[i][j] != 0) {
                    grauTotal++; 
                }
            }

            std::cout << "Vértice " << grafo.indiceParaNome[i] << " -> Grau: " << grauTotal << "\n";
        }
    }
};