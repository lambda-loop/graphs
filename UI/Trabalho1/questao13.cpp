#include "BFS.h"
#include "ListaDeAdjacencia.h"

int main() {
  ListaDeAdjacencia<char> GRAFO_1_LISTA_ADJ("./dados_trabalho_01/GRAFO_1.txt");
  ListaDeAdjacencia<char> GRAFO_3_LISTA_ADJ("./dados_trabalho_01/GRAFO_3.txt");
  BFS<char> BuscaLargura;

  BuscaLargura.executar(GRAFO_1_LISTA_ADJ, 'a');
  BuscaLargura.executar(GRAFO_3_LISTA_ADJ, 'a');
}
