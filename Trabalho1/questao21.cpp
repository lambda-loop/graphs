/*

A implementação pensada: geração de um labirinto a partir
de um grafo, em que cada nó é uma célula do labirinto.

*/

#include "ListaDeAdjacencia.h"
#include <vector>
#include <algorithm>
#include <random>

using namespace std;


typedef std::pair<int, int> Coord;

// gerar labirinto funciona como uma dfs, que vai o mais fundo possivel para uma das direções
void gerarLabirinto(ListaDeAdjacencia<Coord>& grafo, int x, int y, int largura, int altura, set<Coord>& visitados) {

    visitados.insert({x, y});

    // cima, baixo esquerda, direita
    vector<Coord> direcoes = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

    // aleatorizando as direcoes para gerar labirintos aleatorios
    random_device rd;
    mt19937 g(rd());
    shuffle(direcoes.begin(), direcoes.end(), g);

    for (auto& dir : direcoes){
        int proximo_x = x + dir.first;
        int proximo_y = y + dir.second;
        Coord vizinho = {proximo_x, proximo_y};

        // verifica se o vizinho estra dentro dos limites e nao foi visitado
        if (proximo_x >= 0 && proximo_x < largura
            && proximo_y >= 0 && proximo_y < altura
            && visitados.find(vizinho) == visitados.end()){

                grafo.adjacentes[{x, y}].push_back(vizinho);
                grafo.adjacentes[vizinho].push_back({x, y});

                gerarLabirinto(grafo, proximo_x, proximo_y, largura, altura, visitados);
            }
    }
}

// resolver o labirinto funciona como uma dfs que vai o mais fundo possivel para achar a saida, e caso não consiga
// ele volta um vertice continuando a dfs
bool resolverLabirinto(ListaDeAdjacencia<Coord>& grafo, Coord atual, Coord destino, set<Coord>& visitados, vector<Coord>& caminho){

    visitados.insert(atual);
    caminho.push_back(atual);

    if (atual == destino) return true;

    for (const auto& vizinho : grafo.adjacentes[atual]){
        if (visitados.find(vizinho) == visitados.end() && resolverLabirinto(grafo, vizinho, destino, visitados, caminho)){
            return true;
        }
    }

    caminho.pop_back(); // se não encontrar saida, vai pro vertice anterior

    return false;

}



int main(){

    int largura = 10;
    int altura = 10;

    ListaDeAdjacencia<Coord> grafo;
    set<Coord> visitadosGeracao;

    // nesse caso estamos gerando um labirinto 10x10
    gerarLabirinto(grafo, 0, 0, largura, altura, visitadosGeracao);
    grafo.ordenarVizinhos();

    set<Coord> visitadosResolucao;
    vector<Coord> caminhoResolucao;

    Coord inicio = {0, 0};
    Coord fim = {largura - 1, altura - 1};

    // resolucao do labirinto em que o começo é no nó (0, 0) e o fim no nó (9, 9)
    if (resolverLabirinto(grafo, inicio, fim, visitadosResolucao, caminhoResolucao)){
        cout << "Caminho encontrado da entrada ate a saida:\n";
        for (auto p : caminhoResolucao){
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "O labirinto não tem solução para os pontos de começo e fim dados" << endl;
    }

    return 0;
}
