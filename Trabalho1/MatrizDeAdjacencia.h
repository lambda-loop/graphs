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
    MatrizDeAdjacencia(vector<vector<T>> m)
        : matriz(move(m)), numVertices(static_cast<int>(matriz.size())){
            indiceParaNome.resize(numVertices) ;

            for (int i = 0; i < numVertices; i++){
                T nome = static_cast<T>(i);
                nomeParaIndice[nome] = i;
                indiceParaNome[i] = nome;
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

        arquivo >> numVertices;
        matriz.assign(numVertices, vector<int>(numVertices, 0));
        indiceParaNome.resize(numVertices);

        T primeiro, segundo;
        char virgula;
        int proximoIndice = 0;

        while(arquivo >> primeiro >> virgula >> segundo){

            // registra primeiro nó se for novo
            if(nomeParaIndice.find(primeiro) == nomeParaIndice.end()){
                nomeParaIndice[primeiro] = proximoIndice;
                indiceParaNome[proximoIndice] = primeiro;
                proximoIndice++;
            }

            //registra segundo nó se for novo
            if(nomeParaIndice.find(segundo) == nomeParaIndice.end()){
                nomeParaIndice[segundo] = proximoIndice;
                indiceParaNome[proximoIndice] = segundo;
                proximoIndice++;
            }

            // marca na matriz que o primeiro nó é adjacente ao segundo e vice versa
            int index1 = nomeParaIndice[primeiro];
            int index2 = nomeParaIndice[segundo];
            matriz[index1][index2] = 1;
            matriz[index2][index1] = 1;
        }
        arquivo.close();
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