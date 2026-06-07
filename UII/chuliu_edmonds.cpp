#include "incidence_matrix.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Constroi um vetor com os melhores "pais" de cada nó.
// Busca as arestas de menor custo que incidem em cada nó.
// Primeira fase do algoritmo de chuliu
std::vector<int> construirVetorPai(const GrafoMatrizInc<int> &g, int raiz) {
  std::vector<int> pai(g.vertices, -1);

  for (int v = 0; v < g.vertices; ++v) {

    if (v == raiz)
      continue;

    double menorPeso = 0.0;
    int melhorPai = -1;

    for (size_t e = 0; e < g.matriz.size(); ++e) {

      if (g.matriz[e][v] > 0) {
        double pesoAresta = g.matriz[e][v];

        if (melhorPai == -1 || pesoAresta < menorPeso) {
          menorPeso = pesoAresta;

          for (int u = 0; u < g.vertices; ++u) {
            if (g.matriz[e][u] < 0) {
              melhorPai = u;
              break;
            }
          }
        }
      }
    }

    pai[v] = melhorPai;
  }
  return pai;
}

// DFS com coloração para encontrar ciclos na árvore geradora do algorimto de
// chuliu Essa é a segunda fase do algoritmo
vector<int> encontrarCiclo(int n, const vector<int> &pai, int raiz) {
  // Define 3 estados possíveis:
  // - 0 não visitado
  // - 1 na pilha
  // - 2 visitado (concluído)
  vector<int> estado(n, 0);

  vector<int> caminho_atual;

  // define raiz logo como concluido
  estado[raiz] = 2;

  for (int i = 0; i < n; ++i) {
    if (estado[i] != 0)
      continue;

    int atual = i;
    caminho_atual.clear();

    // Vai empilhando os nós seguindo o ponteiro do nó pai até encontrar um
    // ciclo ou nó já concluído
    while (atual != -1 && estado[atual] == 0) {
      estado[atual] = 1;
      caminho_atual.push_back(atual);
      atual = pai[atual];
    }

    // Caso após o loop o nó atual ainda está com estado 1 (na pilha), significa
    // que um ciclo foi encontrado
    if (atual != -1 && estado[atual] == 1) {
      vector<int> ciclo;
      auto it = find(caminho_atual.begin(), caminho_atual.end(), atual);
      ciclo.assign(it, caminho_atual.end());
      return ciclo;
    }

    // Conclui todos os nós no caminho encontrado pela DFS
    for (int u : caminho_atual) {
      estado[u] = 2;
    }
  }

  // Caso contrário, nenhum ciclo foi encontado
  return {};
}

// Função de teste só para mostrar funcionando a função de encontrar as menores
// aretsas e a de detectar ciclos
void testeChuLiuEdmondsFase1e2() {
  // Carrega um caso de uso com dois ciclos adicionados além dos propostos no
  // enunciado para que não seja trivial:
  // 4 -> 8 -> 7 -> 4
  // 11 -> 12 -> 15 -> 11
  GrafoMatrizInc<int> g("grafo_chuliu.txt", true);

  if (g.vertices == 0) {
    cout << "Grafo vazio ou erro ao ler o arquivo.\n";
    return;
  }

  int raiz = 0;

  vector<int> pai = construirVetorPai(g, raiz);

  cout << "Arestas mais baratas encontradas por construirVetorPai (melhores "
          "pais):\n";
  for (int i = 0; i < g.vertices; i++) {
    if (i == raiz) {
      cout << "V" << g.indiceParaNome[i] << " e a RAIZ.\n";
    } else if (pai[i] != -1) {
      cout << "V" << g.indiceParaNome[pai[i]] << " -> V" << g.indiceParaNome[i]
           << "\n";
    } else {
      cout << "V" << g.indiceParaNome[i]
           << " esta inacessivel (sem arestas de entrada).\n";
    }
  }
  cout << "---------------------------------------------------\n\n";

  // Vai mostrar somente o primeiro ciclo que aparece (4 -> 8 -> 7 -> 4)
  vector<int> ciclo = encontrarCiclo(g.vertices, pai, raiz);

  // Se quiser testar com o arquivo grafo.txt ao inves de grafo_chuliu.txt, vai
  // mostrar isso aqui
  if (ciclo.empty()) {
    cout << "Nenhum ciclo detectado!\n";
  } else {
    cout << "Caminho do ciclo: ";

    for (auto it = ciclo.rbegin(); it != ciclo.rend(); ++it) {
      cout << g.indiceParaNome[*it] << " -> ";
    }
    cout << g.indiceParaNome[ciclo.back()] << " (fecha ciclo)\n";
  }
}

// Falta implementar as etapas 3 e 4 do algoritmo, que são:
//
// 3. Contrair os ciclos: considera o ciclo encontrado um pseudo nó k, isto é,
//
// considera todos os nós pertencentes ao ciclo como um nó só, e vai alterando
// os custos com a seguinte equação:
// c(i,k) = c(i,j) - [c(x(j), j) - min{r}(c(x(r)), r)]
//
// 4. Expansão do ciclo: transforma o ciclo anteriormente considerado um nó só
// novamente em 3 nós mas dessa vez substitui uma das arestas do ciclo pela
// aresta encontrada pelo passo 3, quebrando assim o ciclo da árvore geradora
int main() {
  testeChuLiuEdmondsFase1e2();
  return 0;
}
