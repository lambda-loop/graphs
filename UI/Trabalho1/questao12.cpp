#include "ListaDeAdjacencia.h"
#include <queue>

/*

Objetivo: checar se o grafo é bipartido

Estratégia: crio um map em que cada chave é um nó do grafo, e o valor sua cor. Faço a BFS
percorrendo o grafo e pintando os nós. Se o nó já estiver pintado, checar se esta na mesma cor que o nó atual, e
se estiver, o grafo não é bipartido, se não estiver incolor, pintamos da cor oposta do vértice atual. 
Se a BFS acabar sem nenhum conflito de cores, o grafo é bipartido.
Repetimos a BFS para todos os nós não pintados para tratar casos de grafos desconexos.

*/

string inversoCor(string cor){
    if (cor == "azul") return "vermelho"; 
    else if (cor == "vermelho") return "azul";
    else return "incolor";
}

template<typename T>
bool ehBipartido(ListaDeAdjacencia<T> grafo){

    // map para salvar a cor de cada nó
    map<T, string> cor;

    // colocando todos os vértices do grafo no map, sem cor
    for (const auto& [vertice, vizinhos] : grafo.adjacentes){
        cor[vertice] = "incolor";
    }

    // iterando em todos os vertices, para tratar casos de grafos desconexos
    for (const auto& [vertice, vizinhos] : grafo.adjacentes){

        // pulando a iteração caso o nó já tenha sido visitado
        if (cor[vertice] != "incolor") continue;

        // BFS
        queue<T> fila;
        cor[vertice] = "azul";
        fila.push(vertice);

        while (!fila.empty()){

            T atual = fila.front();
            fila.pop();

            for (const auto& vizinho : grafo.adjacentes[atual]){
                if (cor[vizinho] == cor[atual]){ // caso cores iguais = não bipartido
                    return false;
                }
                else if (cor[vizinho] == "incolor"){ // caso vizinho incolor, colore com a cor oposta
                    cor[vizinho] = inversoCor(cor[atual]);
                    fila.push(vizinho);
                }
            }
        }
    }
    return true; 
}

int main(){

    // grafos a seres checados
    ListaDeAdjacencia<char> GRAFO_1("./dados_trabalho_01/GRAFO_1.txt");

    ListaDeAdjacencia<int> GRAFO_2("./dados_trabalho_01/GRAFO_2.txt"); 

    printf("grafo 1 eh bipartido: %s\n", ehBipartido(GRAFO_1) ? "true" : "false");

    printf("grafo 2 eh bipartido: %s\n", ehBipartido(GRAFO_2) ? "true" : "false");

    return 0;
}