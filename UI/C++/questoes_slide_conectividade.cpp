#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <set>

class GrafoDFS {
    int numVertices;
    std::vector<std::vector<int>> adj;
    int tempo; //marcar a ordem de chegada dos vertices
    std::vector<int> td; //pra saber se o vertice foi visitado
    std::vector<int> lowpt; //valores de lowpt
    std::stack<std::pair<int, int>> pilha_arestas;

    void DFS_Recursiva(int verticeAtual, int predecessor) {
        tempo++;
        td[verticeAtual] = tempo;
        lowpt[verticeAtual] = tempo; //tempo menor significa q tá mais perto da raiz da árvore

        for (int vizinho : adj[verticeAtual]) {
            if (vizinho == predecessor) continue;
            if (td[vizinho] == -1) {
                pilha_arestas.push({verticeAtual, vizinho});
                DFS_Recursiva(vizinho, verticeAtual); //vizinho vira o vertice atual e o vertice atual vira o predecessor
                lowpt[verticeAtual] = std::min(lowpt[verticeAtual], lowpt[vizinho]);

            if (lowpt[vizinho] >= td[verticeAtual]) {
                // cria o conjunto para guardar os vértices sem repetir
                std::set<int> vertices_do_bloco; 

                // tira as arestas da pilha e joga os vértices dentro do conjunto
                while (!pilha_arestas.empty()) {
                    std::pair<int, int> aresta = pilha_arestas.top();
                    pilha_arestas.pop();

                    vertices_do_bloco.insert(aresta.first);
                    vertices_do_bloco.insert(aresta.second);

                    if (aresta.first == verticeAtual && aresta.second == vizinho) {
                        break;
                    }
                }

                // agora imprimimos o conjunto formatado bonitinho
                std::cout << "Bloco: {";
                bool primeiro = true;
                for (int v : vertices_do_bloco) {
                    if (!primeiro) std::cout << ", ";
                    std::cout << v;
                    primeiro = false;
                }
                std::cout << "}\n";
            }
            } else {
                if (td[vizinho] < td[verticeAtual]) { //so empilha se o vizinho foi descoberto antes do atual
                    pilha_arestas.push({verticeAtual, vizinho});
                }
                lowpt[verticeAtual] = std::min(lowpt[verticeAtual], td[vizinho]);
            }
        }
    }

    //dfs ignorando uma aresta específica
    bool temCaminhoAlternativo(int atual, int destino, int ignora_u, int ignora_v, std::vector<bool>& visitado) {
        //marcamos onde estamos
        visitado[atual] = true;

        if (atual == destino) {
            return true;
        }

        //procurando nos vizinhos
        for (int vizinho : adj[atual]) {
            if ((atual == ignora_u && vizinho == ignora_v) || (atual == ignora_v && vizinho == ignora_u)) {
                continue;
            }

            //se o vizinho não foi visitado, desce a busca por ele
            if (!visitado[vizinho]) {
                if (temCaminhoAlternativo(vizinho, destino, ignora_u, ignora_v, visitado)) {
                    return true;
                }
            }

        }
        //se nenhum caminho alternativo chegou no destino
        return false;
    }

public:
    GrafoDFS(int vertices) : numVertices(vertices) {
        adj.resize(vertices);
    }

    void adicionarAresta(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Grafo não direcionado
    }

    void encontrarBlocos() {
        tempo = 0;
        td.assign(numVertices, -1);
        lowpt.assign(numVertices, -1);

        for (int i = 0; i < numVertices; i++) {
            if (td[i] == -1) {
                DFS_Recursiva(i, -1); //esse i é o vertice atual
            }
        }
    }

    bool ehPonte(int u, int v) {
        std::vector<bool> visitado(numVertices, false);

        //tentamos ir de 'u' para 'v', proibindo o algoritmo de usar a aresta direta (u, v)
        bool desvioEncontrado = temCaminhoAlternativo(u, v, u, v, visitado);

        //se encontrou desvio, NÃO é ponte (falso). Se NÃO encontrou desvio, É ponte (verdadeiro).
        return !desvioEncontrado;
    }
    
};

int main() {
    // Montando um grafo de teste
    GrafoDFS g(9);
    g.adicionarAresta(0, 1);
    g.adicionarAresta(0, 2);
    g.adicionarAresta(2, 3);
    g.adicionarAresta(3, 5);
    g.adicionarAresta(2, 5);
    g.adicionarAresta(1, 2);
    g.adicionarAresta(2, 4);
    g.adicionarAresta(4, 6);
    g.adicionarAresta(4, 7);
    g.adicionarAresta(6, 8);
    g.adicionarAresta(6, 7);
    g.adicionarAresta(7, 8);

    g.encontrarBlocos();

    if (g.ehPonte(2,4)) {
        std::cout << "eh ponte\n";
    } else {
        std::cout << "não eh ponte\n";
    }

    return 0;
}