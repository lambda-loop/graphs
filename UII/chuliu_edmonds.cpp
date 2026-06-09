#include "incidence_matrix.h"
#include <algorithm>
#include <iostream>
#include <string>
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

// Execução principal do algoritmo
// Chama as fases 1 e 2 (implementadas acima)
// Bem como as fases seguintes
vector<int> chuLiuEdmondsRecursivo(GrafoMatrizInc<int> g, int raiz,
                                   vector<int> ids_originais) {

  // Fase 1
  vector<int> pai = construirVetorPai(g, raiz);

  // Fase 2
  vector<int> ciclo = encontrarCiclo(g.vertices, pai, raiz);

  // construirVetorPai retorna o nó
  // Queremos os IDs das arestas
  // Queremos os pesos das arestas
  vector<int> id_aresta_pai(g.vertices, -1);
  vector<double> peso_pai(g.vertices, 1e9);

  for (int v = 0; v < g.vertices; v++) {
    if (pai[v] != -1) {
      for (size_t e = 0; e < g.matriz.size(); e++) {
        // Encontra a aresta de pai[v] -> v
        if (g.matriz[e][pai[v]] < 0 && g.matriz[e][v] > 0) {
          if (g.matriz[e][v] < peso_pai[v]) {
            peso_pai[v] = g.matriz[e][v];
            id_aresta_pai[v] = e;
          }
        }
      }
    }
  }

  // Se nenhum ciclo for formado, G = <N, S> é uma árvore geradora mínima
  if (ciclo.empty()) {
    vector<int> arcos_selecionados;
    for (int i = 0; i < g.vertices; ++i) {
      if (i != raiz && id_aresta_pai[i] != -1) {
        arcos_selecionados.push_back(ids_originais[id_aresta_pai[i]]);
      }
    }
    return arcos_selecionados;
  }
  // Caso contrário, continue

  // Fase 3
  // Transforma cada ciclo em um pseudo-nó 'k'
  int pseudo_no_k = ciclo[0];
  vector<int> map_node(g.vertices);
  for (int i = 0; i < g.vertices; i++)
    map_node[i] = i;
  for (int u : ciclo)
    map_node[u] = pseudo_no_k;

  // Encontra a aresta de menor peso
  double min_custo_ciclo = 1e9;
  for (int r : ciclo) {
    if (peso_pai[r] < min_custo_ciclo)
      min_custo_ciclo = peso_pai[r];
  }

  // Depois de transformar cada ciclo, podemos modificar o custo de cada arco
  // Aqui está sendo criado uma matriz nova para refletir essa mudança
  GrafoMatrizInc<int> g_contraido = g;
  g_contraido.matriz.clear();
  vector<int> novos_ids;

  for (size_t e = 0; e < g.matriz.size(); e++) {
    int u = -1, v = -1;
    double peso = 0;

    for (int i = 0; i < g.vertices; i++) {
      if (g.matriz[e][i] < 0)
        u = i;
      if (g.matriz[e][i] > 0) {
        v = i;
        peso = g.matriz[e][i];
      }
    }
    if (u == -1 || v == -1)
      continue;

    int map_u = map_node[u];
    int map_v = map_node[v];

    if (map_u == map_v)
      continue;

    double novo_peso = peso;

    // Equação: c(i,k) = c(i,j) - [c(x(j), j) - min{r} <c <x(r), r>]
    if (map_u != pseudo_no_k && map_v == pseudo_no_k) {
      novo_peso = peso - (peso_pai[v] - min_custo_ciclo);
    }

    std::vector<double> nova_linha(g.vertices, 0.0);
    nova_linha[map_u] = -1;
    nova_linha[map_v] = novo_peso;

    g_contraido.matriz.push_back(nova_linha);
    novos_ids.push_back(ids_originais[e]);
  }

  // Vá para o Passo 2 com o grafo contraído
  vector<int> mst_contraida =
      chuLiuEdmondsRecursivo(g_contraido, raiz, novos_ids);

  // Reconstrução do ciclo original removendo a aresta redundante
  vector<int> resultado_final = mst_contraida;

  // Identifica qual aresta que entra no ciclo (pseudo_no_k) foi selecionada na
  // MST contraída. O nó 'v' que recebe essa aresta é o ponto onde o ciclo
  // original será "quebrado".
  int no_quebrado_j = -1;
  for (int id_sel : mst_contraida) {
    int idx_local = -1;
    // Dado um id, Compara grafo(id) com grafo contraido (id)
    for (size_t e = 0; e < ids_originais.size(); e++) {
      if (ids_originais[e] == id_sel) {
        idx_local = e;
        break;
      }
    }
    if (idx_local != -1) {
      int u = -1, v = -1;
      // Identifica origem e destino da aresta original
      for (int i = 0; i < g.vertices; i++) {
        if (g.matriz[idx_local][i] < 0)
          u = i;
        if (g.matriz[idx_local][i] > 0)
          v = i;
      }
      // Verifica se esta aresta entra no ciclo contraído
      // Ou seja, verifica se a origem 'u' está fora do ciclo (pseudo_no_k)
      // Ou seja, não é uma aresta redundante
      if (map_node[u] != pseudo_no_k && map_node[v] == pseudo_no_k) {
        no_quebrado_j = v;
      }
    }
  }

  // Adiciona todas as arestas, menos as redundantes
  for (int u : ciclo) {
    if (u != no_quebrado_j) {
      resultado_final.push_back(ids_originais[id_aresta_pai[u]]);
    }
  }

  return resultado_final;
}

// Funçãozinha para:
// Carregar o arquivo,
// Inicializar os IDs,
// Chamar a recursão,
// Limpar a matriz manualmente e
// Tratar vetores de arestas.
GrafoMatrizInc<int> generateMinimumSpanningTree(const string &arquivo,
                                                int raiz = 0) {
  GrafoMatrizInc<int> grafo_original(arquivo, true);

  if (grafo_original.vertices == 0) {
    return grafo_original;
  }

  vector<int> ids_iniciais(grafo_original.matriz.size());
  for (size_t i = 0; i < ids_iniciais.size(); i++) {
    ids_iniciais[i] = i;
  }

  vector<int> arestas_finais_ids =
      chuLiuEdmondsRecursivo(grafo_original, raiz, ids_iniciais);

  GrafoMatrizInc<int> mst = grafo_original;
  mst.matriz.clear();

  for (size_t e = 0; e < grafo_original.matriz.size(); ++e) {
    if (find(arestas_finais_ids.begin(), arestas_finais_ids.end(),
             static_cast<int>(e)) != arestas_finais_ids.end()) {
      mst.matriz.push_back(grafo_original.matriz[e]);
    }
  }

  return mst;
}

int main() {
  std::cout << "-------------Original Graph-----------------" << std::endl;
  auto graph = GrafoMatrizInc<int>("grafo_chuliu.txt", true);
  graph.imprimirMatriz();

  std::cout << "---------------------------------------" << std::endl;
  std::cout << "-------------Minimum Spanning Tree-----------------"
            << std::endl;
  auto minimumSpanningTree = generateMinimumSpanningTree("grafo_chuliu.txt", 0);

  minimumSpanningTree.imprimirMatriz();
  minimumSpanningTree.imprimirListaArestas();
  return 0;
}
