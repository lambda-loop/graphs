#include "ListaDeAdjacencia.h"
#include "MatrizDeAdjacencia.h"
#include "MatrizDeIncidencia.h"

int main() {

  cout << "---------------- carregando GRAFO_1 para as estruturas de dados "
          "----------------"
       << endl;
  ListaDeAdjacencia<char> GRAFO_1_LISTA_ADJ("./dados_trabalho_01/GRAFO_1.txt");
  MatrizDeAdjacencia<char> GRAFO_1_MATRIZ_ADJ(
      "./dados_trabalho_01/GRAFO_1.txt");
  MatrizDeIncidencia<char> GRAFO_1_MATRIZ_INC(
      "./dados_trabalho_01/GRAFO_1.txt");
  char verticeRemovido = 'e';

  cout << "Removendo vértice 'e' na Lista de Adjacência:" << endl;
  cout << "Antes:" << endl;
  GRAFO_1_LISTA_ADJ.imprimirGrafo();
  cout << "Depois:" << endl;
  GRAFO_1_LISTA_ADJ.removerVertice(verticeRemovido);
  GRAFO_1_LISTA_ADJ.imprimirGrafo();

  cout << "Removendo vértice 'e' na Matriz de Adjacência:" << endl;
  cout << "Antes:" << endl;
  GRAFO_1_MATRIZ_ADJ.imprimirGrafo();
  cout << "Depois:" << endl;
  GRAFO_1_MATRIZ_ADJ.removerVertice(verticeRemovido);
  GRAFO_1_MATRIZ_ADJ.imprimirGrafo();

  cout << "Removendo vértice 'e' na Matriz de Incidência:" << endl;
  cout << "Antes:" << endl;
  GRAFO_1_MATRIZ_INC.imprimirGrafo();
  cout << "Depois:" << endl;
  GRAFO_1_MATRIZ_INC.removerVertice(verticeRemovido);
  GRAFO_1_MATRIZ_INC.imprimirGrafo();

  return 0;
}
