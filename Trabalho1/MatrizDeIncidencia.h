#pragma once

#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

template <typename T> struct MatrizDeIncidencia {
  std::map<T, int> nomeParaIndice;
  std::vector<T> indiceParaNome;
  std::vector<std::vector<int>> matriz;

  MatrizDeIncidencia() = default;

  MatrizDeIncidencia(std::string caminhoDoGrafo) {
    std::ifstream arquivo(caminhoDoGrafo);
    if (!arquivo.is_open()) {
      std::cerr << "Erro ao abrir o arquivo." << std::endl;
      return;
    }

    int numVertices;
    arquivo >> numVertices;
    T v1, v2;
    char virgula;

    while (arquivo >> v1 >> virgula >> v2) {
      adicionarAresta(v1, v2);
    }

    arquivo.close();
  }

  void adicionarVertice(T novoVertice, std::vector<T> vizinhos = {}) {
    if (nomeParaIndice.find(novoVertice) == nomeParaIndice.end()) {
      nomeParaIndice[novoVertice] = indiceParaNome.size();
      indiceParaNome.push_back(novoVertice);

      int numArestas = matriz.empty() ? 0 : matriz[0].size();
      matriz.push_back(std::vector<int>(numArestas, 0));
    }

    for (const T &vizinho : vizinhos) {
      adicionarAresta(novoVertice, vizinho);
    }
  }

  void adicionarAresta(T v1, T v2) {
    adicionarVertice(v1);
    adicionarVertice(v2);

    int idx1 = nomeParaIndice[v1];
    int idx2 = nomeParaIndice[v2];

    for (auto &linha : matriz) {
      linha.push_back(0);
    }

    int novaArestaIdx = matriz[0].size() - 1;
    matriz[idx1][novaArestaIdx] = 1;
    matriz[idx2][novaArestaIdx] = 1;
  }

  void removerVertice(T nome) {
    if (nomeParaIndice.find(nome) == nomeParaIndice.end())
      return;

    int idx = nomeParaIndice[nome];

    std::vector<bool> colunasParaRemover(matriz[0].size(), false);
    for (size_t j = 0; j < matriz[0].size(); j++) {
      if (matriz[idx][j] != 0)
        colunasParaRemover[j] = true;
    }

    matriz.erase(matriz.begin() + idx);

    for (int j = matriz[0].size() - 1; j >= 0; j--) {
      if (colunasParaRemover[j]) {
        for (auto &linha : matriz) {
          linha.erase(linha.begin() + j);
        }
      }
    }

    indiceParaNome.erase(indiceParaNome.begin() + idx);
    nomeParaIndice.clear();
    for (size_t i = 0; i < indiceParaNome.size(); i++) {
      nomeParaIndice[indiceParaNome[i]] = i;
    }
  }

  void imprimirGrafo() {
    if (matriz.empty())
      return;

    std::cout << "    ";
    for (size_t j = 0; j < matriz[0].size(); j++) {
      std::cout << "A" << j << " ";
    }
    std::cout << "\n";

    for (size_t i = 0; i < matriz.size(); i++) {
      if (indiceParaNome[i] == ',')
        continue;

      std::cout << indiceParaNome[i] << " | ";
      for (int val : matriz[i]) {
        std::cout << val << "  ";
      }
      std::cout << "\n";
    }
  }

  /*
   (7) Função que determina o número total de vértices do grafo.
   A quantidade de vértices corresponde ao tamanho do vetor indiceParaNome
   (linhas da matriz).
   Complexidade de tempo: O(1).
   */
  int obterTotalDeVertices() const { return indiceParaNome.size(); }

  /**
   (8) Função que determina o número total de arestas do grafo.
   Na Matriz de Incidência desta implementação, as colunas da 'matriz'
   representam as arestas distintas.
   omplexidade de tempo: O(1).
   */
  int obterTotalDeArestas() const {
    if (matriz.empty())
      return 0;
    return matriz[0].size();
  }

  /**
   (11) Função que determina se um grafo não direcionado é conexo.
   Utiliza Busca em Largura (BFS). Na matriz de incidência
   encontra as arestas conectadas ao vértice atual, e então varre a
   aresta para encontrar o vértice vizinho.
   Complexidade de tempo: O(V * E).
   */
  bool verificarSeConexo() {
    int qtdVertices = indiceParaNome.size();
    int qtdArestas = matriz.empty() ? 0 : matriz[0].size();

    if (qtdVertices <= 1)
      return true;
    if (qtdArestas == 0 && qtdVertices > 1)
      return false;

    std::vector<bool> visitados(qtdVertices, false);
    std::queue<int> fila;

    fila.push(0);
    visitados[0] = true;
    int qtdVisitados = 1;

    while (!fila.empty()) {
      int u = fila.front();
      fila.pop();

      for (int i = 0; i < qtdArestas; ++i) {
        if (matriz[u][i] == 1 || matriz[u][i] == -1) {

          for (int v = 0; v < qtdVertices; ++v) {
            if (v != u && (matriz[v][i] == 1 || matriz[v][i] == -1)) {

              if (!visitados[v]) {
                visitados[v] = true;
                fila.push(v);
                qtdVisitados++;
              }
              break;
            }
          }
        }
      }
    }

    return (qtdVisitados == qtdVertices);
  }
};