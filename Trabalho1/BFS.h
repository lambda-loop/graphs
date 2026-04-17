#include "ListaDeAdjacencia.h"
#include <iostream>
#include <map>
#include <queue>
#include <vector>

template <typename T> struct BFS {
public:
  void executar(ListaDeAdjacencia<T> &grafo, T verticeInicial) {
    std::map<T, bool> visited;
    std::queue<T> fila;
    std::vector<T> caminho;

    visited[verticeInicial] = true;
    caminho.push_back(verticeInicial);
    fila.push(verticeInicial);
    while (!fila.empty()) {
      T verticeAtual = fila.front();
      fila.pop();
      std::cout << "vertice atual:" << verticeAtual << std::endl;
      std::vector<T> vizinhos = grafo.adjacentes[verticeAtual];
      for (size_t i = 0; i < vizinhos.size(); i++) {
        if (!visited[vizinhos[i]]) {
          fila.push(vizinhos[i]);
          visited[vizinhos[i]] = true;
          caminho.push_back(vizinhos[i]);
          std::cout << "vertice atual:" << vizinhos[i] << std::endl;
        }
      }
    }
    std::cout << "caminho total: ";

    for (size_t i = 0; i < caminho.size(); i++) {
      std::cout << caminho[i] << ", ";
    }
    std::cout << endl;
  }
};
