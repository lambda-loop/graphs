#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename T> struct MatrizDeAdjacencia {
  vector<vector<int>> matriz;
  int numVertices;

  map<T, int> nomeParaIndice;
  vector<T> indiceParaNome;

  MatrizDeAdjacencia() : numVertices(0) {}

  MatrizDeAdjacencia(vector<vector<int>> m, vector<T> nomes)
      : matriz(move(m)), numVertices(static_cast<int>(matriz.size())),
        indiceParaNome(move(nomes)) {
    if (numVertices != (int)indiceParaNome.size()) {
      cerr << "Erro: O número de nomes fornecidos não coincide com o tamanho "
              "da matriz.";
      return;
    }
    for (int i = 0; i < numVertices; i++) {
      nomeParaIndice[indiceParaNome[i]] = i;
    }
  }

  MatrizDeAdjacencia(string caminhoDoGrafo) {
    ifstream arquivo(caminhoDoGrafo);

    arquivo >> numVertices;
    matriz.assign(numVertices, vector<int>(numVertices, 0));
    indiceParaNome.resize(numVertices);

    T primeiro, segundo;
    char virgula;
    int proximoIndice = 0;

    while (arquivo >> primeiro >> virgula >> segundo) {
      if (nomeParaIndice.find(primeiro) == nomeParaIndice.end()) {
        nomeParaIndice[primeiro] = proximoIndice;
        indiceParaNome[proximoIndice] = primeiro;
        proximoIndice++;
      }
      if (nomeParaIndice.find(segundo) == nomeParaIndice.end()) {
        nomeParaIndice[segundo] = proximoIndice;
        indiceParaNome[proximoIndice] = segundo;
        proximoIndice++;
      }
      int index1 = nomeParaIndice[primeiro];
      int index2 = nomeParaIndice[segundo];
      matriz[index1][index2] = 1;
      matriz[index2][index1] = 1;
    }
    arquivo.close();
  }

  void adicionarVertice(T novoVertice, vector<T> vizinhos) {
    int novoVerticeIdx = numVertices;
    nomeParaIndice[novoVertice] = novoVerticeIdx;
    indiceParaNome.push_back(novoVertice);

    for (auto &linha : matriz) {
      linha.push_back(0);
    }
    numVertices++;
    matriz.push_back(vector<int>(numVertices, 0));

    for (const auto &vizinho : vizinhos) {
      if (nomeParaIndice.count(vizinho)) {
        int vizinhoIdx = nomeParaIndice[vizinho];
        matriz[novoVerticeIdx][vizinhoIdx] = 1;
        matriz[vizinhoIdx][novoVerticeIdx] = 1;
      }
    }
  }

  void removerVertice(T vertice) {
    if (nomeParaIndice.find(vertice) == nomeParaIndice.end())
      return;

    int idx = nomeParaIndice[vertice];

    matriz.erase(matriz.begin() + idx);

    for (auto &linha : matriz) {
      linha.erase(linha.begin() + idx);
    }

    indiceParaNome.erase(indiceParaNome.begin() + idx);
    nomeParaIndice.erase(vertice);

    for (auto &pair : nomeParaIndice) {
      if (pair.second > idx) {
        pair.second--;
      }
    }
    numVertices--;
  }

  void imprimirGrafo() {
    if (numVertices == 0)
      return;

    cout << "  ";
    for (int i = 0; i < numVertices; i++) {
      cout << indiceParaNome[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < numVertices; i++) {
      cout << indiceParaNome[i] << " ";
      for (int j = 0; j < numVertices; j++) {
        cout << matriz[i][j] << " ";
      }
      cout << endl;
    }
  }

  /*
   (7) Função que determina o número total de vértices do grafo.
   A quantidade de vértices já é controlada pela variável numVertices.
   Complexidade de tempo: O(1).
   */
  int obterTotalDeVertices() const { return numVertices; }

  /*
   (8) Função que determina o número total de arestas do grafo.
   Na Matriz de Adjacência de um grafo não direcionado, a matriz é
   simétrica.
   Para evitar contar a mesma aresta duas vezes (ida e volta), iteramos
   apenas
   pela metade superior da matriz (j >= i).
   Complexidade de tempo: O(V^2).
   */
  int obterTotalDeArestas() const {
    int totalArestas = 0;
    for (int i = 0; i < numVertices; ++i) {
      for (int j = i; j < numVertices;
           ++j) { // Começa de 'i' para pegar diagonal e triângulo superior
        if (matriz[i][j] != 0) {
          totalArestas++;
        }
      }
    }
    return totalArestas;
  }

  /*
   (11) Função que determina se um grafo não direcionado é conexo.
   Utiliza Busca em Largura (BFS). Em uma matriz de adjacência, procuramos
   os vizinhos diretos (onde matriz[u][v] != 0) na linha do vértice atual.
   Complexidade de tempo: O(V^2).
   */
  bool verificarSeConexo() {
    if (numVertices <= 1)
      return true;

    vector<bool> visitados(numVertices, false);
    queue<int> fila;
    fila.push(0);
    visitados[0] = true;
    int qtdVisitados = 1;

    while (!fila.empty()) {
      int u = fila.front();
      fila.pop();

      for (int v = 0; v < numVertices; ++v) {
        if (matriz[u][v] != 0 && !visitados[v]) {
          visitados[v] = true;
          fila.push(v);
          qtdVisitados++;
        }
      }
    }

    return (qtdVisitados == numVertices);
  }
};
