#pragma once

#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

template <typename T> struct GrafoMatrizInc {
  int vertices;
  bool direcionado;
  std::vector<std::vector<double>> matriz;

  std::map<T, int> nomeParaIndice;
  std::vector<T> indiceParaNome;

  GrafoMatrizInc(int ver, bool dir = false) : vertices(ver), direcionado(dir) {
    indiceParaNome.resize(ver);
  }

  GrafoMatrizInc(std::string caminhoDoGrafo, bool dir = false)
      : direcionado(dir), vertices(0) {
    std::ifstream arquivo(caminhoDoGrafo);
    if (!arquivo.is_open()) {
      std::cerr << "Erro ao abrir o arquivo: " << caminhoDoGrafo << std::endl;
      return;
    }

    arquivo >> vertices;
    indiceParaNome.resize(vertices);

    T primeiro, segundo;
    double peso;
    int proximoIndice = 0;

    while (arquivo >> primeiro >> segundo >> peso) {

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

      int origem = nomeParaIndice[primeiro];
      int destino = nomeParaIndice[segundo];

      registrarConexao(origem, destino, peso);
    }
    arquivo.close();
  }

  void registrarConexao(int origem, int destino, double peso) {
    std::vector<double> novaAresta(vertices, 0.0);

    if (direcionado) {
      novaAresta[origem] = -peso;
      novaAresta[destino] = peso;
    } else {
      novaAresta[origem] = peso;
      novaAresta[destino] = peso;
    }

    matriz.push_back(novaAresta);
  }

  void imprimirMatriz() {
    int qtdArestas = matriz.size();

    if (vertices == 0)
      return;

    std::cout << "      ";
    for (int j = 0; j < vertices; ++j) {
      std::cout << "V" << indiceParaNome[j] << "   ";
    }
    std::cout << "\n    " << std::string(vertices * 7, '-') << "\n";

    for (int i = 0; i < qtdArestas; ++i) {
      std::cout << "A" << (i + 1) << " | ";
      for (int j = 0; j < vertices; ++j) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(4)
                  << matriz[i][j] << " ";
      }
      std::cout << "\n";
    }
  }
  void imprimirListaArestas() {
    std::cout << "\n--- Relacao de Arestas ---\n";

    if (matriz.empty()) {
      std::cout << "Nenhuma aresta encontrada.\n";
      return;
    }

    double custoTotal = 0.0;

    for (size_t i = 0; i < matriz.size(); ++i) {
      int origem = -1, destino = -1;
      double peso = 0.0;

      for (int j = 0; j < vertices; ++j) {
        if (matriz[i][j] < 0)
          origem = j;
        else if (matriz[i][j] > 0) {
          destino = j;
          peso = matriz[i][j];
        }
      }

      if (origem != -1 && destino != -1) {
        std::cout << "V" << indiceParaNome[origem] << " -> V"
                  << indiceParaNome[destino] << " \t(Custo: " << std::fixed
                  << std::setprecision(1) << peso << ")\n";
        custoTotal += peso;
      }
    }
    std::cout << "--------------------------\n";
    std::cout << "Custo Total da Arvore: " << custoTotal << "\n";
  }
};
