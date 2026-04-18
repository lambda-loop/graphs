#pragma once

#include <iostream>
#include "MatrizDeIncidencia.h"

struct CalculadorDeGrau {
    void calcularEImprimir(const GrafoMatrizInc& grafo) {
        // Quantidade de arestas na matriz
        int qtdArestas = grafo.matriz.size();
        
        std::cout << "\n=== GRAUS DOS VERTICES ===\n";

        // Percorre cada vértice
        for (int j = 0; j < grafo.vertices; ++j) {
            int grauTotal = 0;

            for (int i = 0; i < qtdArestas; ++i) {
                if (grafo.matriz[i][j] == 1) {
                    grauTotal++;
                }
            }

            // Identificação do Vértice (Letra ou Número)
            std::cout << "V";
            if (grafo.usarLetrasNaImpressao) {
                std::cout << (char)('A' + j); 
            } else {
                std::cout << (j + 1);
            }

            std::cout << " -> Grau: " << grauTotal << "\n";
        }
    }
};