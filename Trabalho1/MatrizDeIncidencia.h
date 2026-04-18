#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

template <typename T> struct MatrizDeIncidencia {
  std::map<T, int> nomeParaIndice;
  std::vector<T> indiceParaNome;
  std::vector<std::vector<int>> matriz;

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
};
