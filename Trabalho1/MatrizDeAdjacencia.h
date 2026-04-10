#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <utility>
#include <string>

using namespace std;

// Implementação de grafo (não direcionado)

template <typename T> struct MatrizDeAdjacencia {
    vector<vector<int>> matriz;
    int numVertices;

    // precisamos disso para englobar os casos em que os nós não são números naturais
    // exemplo: nó 'a'   -> indice 0
    // exemplo: indice 0 -> nó 'a'
    map<T, int> nomeParaIndice;
    vector<T> indiceParaNome;

    // construtor vazio
    MatrizDeAdjacencia() : numVertices(0){}

    // gerando lista de adjacencia a partir de uma matriz já montada
    // Note que a matriz tem que ser quadrada
    MatrizDeAdjacencia(vector<vector<int>> m, vector<T> nomes)
        : matriz(move(m)), numVertices(static_cast<int>(matriz.size())), indiceParaNome(move(nomes)) {

            if(numVertices != (int)indiceParaNome.size()){
                cerr << "Erro: O número de nomes fornecidos não coincide com o tamanho da matriz.";
                return;
            }

            for (int i = 0; i < numVertices; i++){
                nomeParaIndice[indiceParaNome[i]] = i;
            }
        }
    
    // gerando matriz de adjacencia a partir dos arquivos disponibilizados
    // pelo professor
    MatrizDeAdjacencia(string caminhoDoGrafo){
        ifstream arquivo(caminhoDoGrafo);

        if (!arquivo.is_open()){
            cerr << "Erro ao abrir o arquivo: " << caminhoDoGrafo << endl;
            return;
        }

        // Lendo número de vértices
        arquivo >> numVertices;

        
        // Lendo arestas e nomes únicos
        struct Aresta {T primeiro, segundo;};
        vector<Aresta> conexoes;

        // usando map para armazenar os nomes em ordem lexicografica
        map<T, int> nomesOrdenados;

        T primeiro, segundo;
        char virgula;
        while(arquivo >> primeiro >> virgula >> segundo){
            conexoes.push_back({primeiro, segundo});
            nomesOrdenados[primeiro] = 0;
            nomesOrdenados[segundo]  = 0;
        }
        arquivo.close();


        // atribuindo índices baseados na ordem lexicográfica do map
        matriz.assign(numVertices, vector<int>(numVertices, 0));
        indiceParaNome.resize(numVertices);

        int indiceAtual = 0;
        for (auto& par : nomesOrdenados){
            T nome = par.first;
            nomeParaIndice[nome] = indiceAtual;
            indiceParaNome[indiceAtual] = nome;
            indiceAtual++;
        }

        // preenchendo a matrix com as conexões
        for (const auto& aresta : conexoes){
            int indice1 = nomeParaIndice[aresta.primeiro];
            int indice2 = nomeParaIndice[aresta.segundo];
            matriz[indice1][indice2] = 1;
            matriz[indice2][indice1] = 1;
        }

        // DEPRECATED:
        
        // arquivo >> numVertices;
        // matriz.assign(numVertices, vector<int>(numVertices, 0));
        // indiceParaNome.resize(numVertices);

        // T primeiro, segundo;
        // char virgula;
        // int proximoIndice = 0;
        
        // while(arquivo >> primeiro >> virgula >> segundo){

        //     // registra primeiro nó se for novo
        //     if(nomeParaIndice.find(primeiro) == nomeParaIndice.end()){
        //         nomeParaIndice[primeiro] = proximoIndice;
        //         indiceParaNome[proximoIndice] = primeiro;
        //         proximoIndice++;
        //     }

        //     //registra segundo nó se for novo
        //     if(nomeParaIndice.find(segundo) == nomeParaIndice.end()){
        //         nomeParaIndice[segundo] = proximoIndice;
        //         indiceParaNome[proximoIndice] = segundo;
        //         proximoIndice++;
        //     }

        //     // marca na matriz que o primeiro nó é adjacente ao segundo e vice versa
        //     int index1 = nomeParaIndice[primeiro];
        //     int index2 = nomeParaIndice[segundo];
        //     matriz[index1][index2] = 1;
        //     matriz[index2][index1] = 1;
        // }
        // arquivo.close();
    }

    void imprimirGrafo(){
        if (numVertices == 0) return;

        cout << "  ";
        for (int i = 0; i < numVertices; i++){
            cout << indiceParaNome[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < numVertices; i++){
            cout << indiceParaNome[i] << " ";
            for (int j = 0; j < numVertices; j++){
                cout << matriz[i][j] << " ";
            }
            cout << endl;
        }
    }
};