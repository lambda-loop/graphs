#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
// using namespace std;

template <typename T> struct ListaDeAdjacencia {
  std::map<T, std::vector<T>> adjacentes;

    ListaDeAdjacencia(std::map<T, std::vector<T>> m) : adjacentes(move(m)){
        ordenarVizinhos();
    }

    ListaDeAdjacencia(std::string caminhoDoGrafo) {
      std::ifstream arquivo(caminhoDoGrafo);
        T primeiro, segundo;
        char virgula;
    std::string linha;
        getline(arquivo, linha);
        while (arquivo >> primeiro >> virgula >> segundo) {
            adjacentes[primeiro].push_back(segundo);
            adjacentes[segundo].push_back(primeiro);
        }
        ordenarVizinhos();
    }

    void ordenarVizinhos(){
        for (auto& [vertice, vizinhos] : adjacentes){
            sort(vizinhos.begin(), vizinhos.end());
        }
    }

    void adicionarVertice(T novoVertice, std::vector<T> listaVizinhos) {
        adjacentes[novoVertice] = listaVizinhos;
    }

    void removerVertice(T vertice) {
        for (auto &vizinho : adjacentes[vertice]) {
            auto &vizinhosDoVizinho = adjacentes[vizinho];
            vizinhosDoVizinho.erase(std::remove(vizinhosDoVizinho.begin(),
                                                vizinhosDoVizinho.end(), vertice),
                                    vizinhosDoVizinho.end());
        }
        adjacentes.erase(vertice);
    }

    void imprimirGrafo() {
        for (const auto &[vertice, vizinhos] : adjacentes) {
      std::cout << vertice << ": ";
            for (const auto &vizinho : vizinhos) {
        std::cout << vizinho << " ";
            }
      std::cout << std::endl;
        }
    }
};
