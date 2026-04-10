#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <typename T> struct ListaDeAdjacencia {
    map<T, vector<T>> adjacentes;

    ListaDeAdjacencia(map<T, vector<T>> m) : adjacentes(move(m)){
        ordenarVizinhos();
    }

    ListaDeAdjacencia(string caminhoDoGrafo) {
        ifstream arquivo(caminhoDoGrafo);
        T primeiro, segundo;
        char virgula;
        string linha;
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

    void adicionarVertice(T novoVertice, vector<T> listaVizinhos) {
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
            cout << vertice << ": ";
            for (const auto &vizinho : vizinhos) {
                cout << vizinho << " ";
            }
            cout << endl;
        }
    }
};