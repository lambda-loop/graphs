#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
// using namespace std;

template <typename T> struct ListaDeAdjacencia {
  std::map<T, std::vector<T>> adjacentes;

  ListaDeAdjacencia(std::map<T, std::vector<T>> m) : adjacentes(move(m)) {
    ordenarVizinhos();
  }

  ListaDeAdjacencia() {}
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

  void ordenarVizinhos() {
    for (auto &[vertice, vizinhos] : adjacentes) {
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

  /*
(7) Função que determina o número total de vértices do grafo.
A quantidade de vértices é simplesmente o tamanho do map 'adjacentes'.
Complexidade de tempo: O(1).
*/
  int obterTotalDeVertices() const { return adjacentes.size(); }

  /*
    (8) Função que determina o número total de arestas do grafo.
    Em uma lista de adjacência de um grafo não direcionado, a soma do
    grau de todos os vértices é igual ao dobro do número de arestas.
    Portanto, somamos o tamanho de todas as listas de vizinhos e dividimos
    por 2.
    Complexidade de tempo: O(V).
   */
  int obterTotalDeArestas() const {
    int somaGraus = 0;
    for (const auto &par : adjacentes) {
      somaGraus += par.second.size();
    }
    return somaGraus / 2;
  }

  /*
    (11) Função que determina se um grafo não direcionado é conexo.
    Utiliza Busca em Largura (BFS). Começamos por um vértice qualquer e
    navegamos por seus vizinhos usando as listas de adjacência.
    Complexidade de tempo: O(V + E).
   */
  bool verificarSeConexo() {
    if (adjacentes.size() <= 1)
      return true;

    std::set<T> visitados;
    std::queue<T> fila;

    auto iteradorInicial = adjacentes.begin();
    T verticeInicial = iteradorInicial->first;

    fila.push(verticeInicial);
    visitados.insert(verticeInicial);

    while (!fila.empty()) {
      T u = fila.front();
      fila.pop();

      for (const T &vizinho : adjacentes.at(u)) {
        if (visitados.find(vizinho) == visitados.end()) {
          visitados.insert(vizinho);
          fila.push(vizinho);
        }
      }
    }

    return (visitados.size() == adjacentes.size());
  }
};
