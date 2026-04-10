#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;

// Implementação de grafo (não direcionado)
template <typename T> struct ListaDeAdjacencia{
    map<T, vector<T>> adjacentes;
    
    // construtor vazio
    ListaDeAdjacencia(){}

    // gerando lista de adjacencia a partir de um map já montado
    ListaDeAdjacencia(map<T, vector<T>> m) : adjacentes(move(m)){
        ordenarVizinhos();
    }

    // gerando lista de adjacencia a partir dos arquivos disponibilizados
    // pelo professor
    ListaDeAdjacencia(string caminhoDoGrafo){
        ifstream arquivo(caminhoDoGrafo);
        T primeiro, segundo;
        char virgula;

        if (!arquivo.is_open()){
            cerr << "Erro ao abrir o arquivo: " << caminhoDoGrafo << endl;
            return;
        }

        string linha;

        // jogando fora a primeira linha com o tamanho do grafo
        getline(arquivo, linha); 

        while (arquivo >> primeiro >> virgula >> segundo){
            adjacentes[primeiro].push_back(segundo);
            adjacentes[segundo].push_back(primeiro);
        }

        // função para garantir a ordem lexicografica dos adjacentes
        // (necessario para as buscas)
        ordenarVizinhos();
    }

    void ordenarVizinhos(){
        for (auto& [vertice, vizinhos] : adjacentes){
            sort(vizinhos.begin(), vizinhos.end());
        }
    }

    void imprimirGrafo(){
        for (const auto& [vertice, vizinhos] : adjacentes) {
            cout << vertice << ": ";
            for (const auto& vizinho : vizinhos) {
                cout << vizinho << " ";
            }
            cout << endl;
        }
    }
};