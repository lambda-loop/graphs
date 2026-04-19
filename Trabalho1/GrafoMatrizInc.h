#include <cctype>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

struct GrafoMatrizInc {
  int vertices;
  bool direcionado;
  std::vector<std::vector<int>> matriz;
  bool usarLetrasNaImpressao;

  // função que faz o trabalho real usando os índices do computador (0, 1, 2...)
  void registrarConexao(int origem, int destino) {
    // cria uma nova aresta com o tamanho dos vértices, toda zerada
    std::vector<int> novaAresta(vertices, 0);

    if (direcionado) {
      novaAresta[origem] = -1;
      novaAresta[destino] = 1;
    } else {
      novaAresta[origem] = 1;
      novaAresta[destino] = 1;
    }

    matriz.push_back(novaAresta);
  }

  GrafoMatrizInc(int ver, bool dir = false)
      : vertices(ver), direcionado(dir), usarLetrasNaImpressao(false) {}

  // versao com numeros
  void adicionarAresta(int origem_usuario, int destino_usuario) {
    // para que o usuario faça as ligações entre vértices começando do 1
    int origem = origem_usuario - 1;
    int destino = destino_usuario - 1;

    registrarConexao(origem, destino);
  }

  // versao com letras
  void adicionarAresta(char origem_usuario, char destino_usuario) {
    // pra imprimir as letras na matriz
    usarLetrasNaImpressao = true;

    int origem = std::tolower(origem_usuario) - 'a';
    int destino = std::tolower(destino_usuario) - 'a';

    registrarConexao(origem, destino);
  }

  void adicionarVertice() {}

  void imprimirMatriz() {
    int qtdArestas = matriz.size();

    std::cout << "     ";
    for (int j = 0; j < vertices; ++j) {
      if (usarLetrasNaImpressao) {
        // converte 0, 1, 2 para A, B, C...
        char nomeVertice = 'a' + j;
        std::cout << "V" << nomeVertice << "  ";
      } else {
        std::cout << "V" << (j + 1) << "  ";
      }
    }
    std::cout << "\n    " << std::string(vertices * 4, '-') << "\n";

    for (int i = 0; i < qtdArestas; ++i) {
      std::cout << "A" << i + 1 << " | ";
      for (int j = 0; j < vertices; ++j) {
        std::cout << std::setw(2) << matriz[i][j] << "  ";
      }
      std::cout << "\n";
    }
  }
  /*
     (7) Função que determina o número total de vértices do grafo.
     A quantidade de vértices já é armazenada na variável interna 'vertices'.
     Complexidade de tempo: O(1).
     */
  int obterTotalDeVertices() const { return vertices; }

  /**
   (8) Função que determina o número total de arestas do grafo.
   Na Matriz de Incidência desta implementação, cada linha da 'matriz'
   representa uma nova aresta registrada.
   Complexidade de tempo: O(1).
   */
  int obterTotalDeArestas() const { return matriz.size(); }

  /**
   (11) Função que determina se um grafo não direcionado é conexo.
   Utiliza Busca em Largura (BFS). Na matriz de incidência (Aresta x Vértice),
   encontra as arestas conectadas ao vértice atual, e então varre a
   aresta para encontrar o vértice vizinho.
   Complexidade de tempo: O(V * E).
   */
  bool verificarSeConexo() {
    int qtdVertices = vertices;
    int qtdArestas = matriz.size();

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

      // Percorre todas as arestas (linhas) procurando onde 'u' está conectado
      for (int i = 0; i < qtdArestas; ++i) {
        // matriz[aresta][vertice] -> matriz[i][u]
        if (matriz[i][u] == 1 || matriz[i][u] == -1) {

          // Aresta 'i' achada. Agora vamos achar o outro vértice 'v' nessa
          // mesma aresta
          for (int v = 0; v < qtdVertices; ++v) {
            // matriz[aresta][vertice] -> matriz[i][v]
            if (v != u && (matriz[i][v] == 1 || matriz[i][v] == -1)) {

              if (!visitados[v]) {
                visitados[v] = true;
                fila.push(v);
                qtdVisitados++;
              }
              break; // Achou o par da aresta, vai para a próxima
            }
          }
        }
      }
    }

    return (qtdVisitados == qtdVertices);
  }
};