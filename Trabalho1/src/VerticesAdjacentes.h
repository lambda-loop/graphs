#pragma once

#include "MatrizDeAdjacencia.h"

template <typename T>

struct VerticesAdjacentes {
    void verificar(const MatrizDeAdjacencia<T>& grafo, T u, T v) {
        //verificar se os vertices existem no grafo
        if (grafo.nomeParaIndice.count(u) == 0 || grafo.nomeParaIndice.count(v) == 0) {
            std::cout << "Um ou ambos os vertices (" << u << ", " << v << ") nao existem no grafo.\n";
            return;
        }

        int idxU = grafo.nomeParaIndice.at(u);
        int idxV = grafo.nomeParaIndice.at(v);

        if (grafo.matriz[idxU][idxV] == 1) {
            std::cout << "Os vertices " << u << " e " << v << " SAO adjacentes.\n";
        } 
        /*else {
            std::cout << "Os vertices " << u << " e " << v << " NAO sao adjacentes.\n";
        }*/
    }
};