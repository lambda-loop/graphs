#include "ListaDeAdjacencia.h"
#include "MatrizDeAdjacencia.h"
#include <vector>

int main() {

  cout << "---------------- carregando GRAFO_1 para as estruturas de dados "
          "----------------"
       << endl;
  ListaDeAdjacencia<char> GRAFO_1_LISTA_ADJ("./dados_trabalho_01/GRAFO_1.txt");
  MatrizDeAdjacencia<char> GRAFO_1_MATRIZ_ADJ(
      "./dados_trabalho_01/GRAFO_1.txt");
  char novoVertice = 'g';
  vector<char> listaVizinhos = {'e', 'f'};

  cout << "Adicionando vértice 'g' na Lista de Adjacência:" << endl;
  cout << "Antes:" << endl;
  GRAFO_1_LISTA_ADJ.imprimirGrafo();
  cout << "Depois:" << endl;
  GRAFO_1_LISTA_ADJ.adicionarVertice(novoVertice, listaVizinhos);
  GRAFO_1_LISTA_ADJ.imprimirGrafo();

  cout << "Adicionando vértice 'g' na Matriz de Adjacência:" << endl;
  cout << "Antes:" << endl;
  GRAFO_1_MATRIZ_ADJ.imprimirGrafo();
  cout << "Depois:" << endl;
  GRAFO_1_MATRIZ_ADJ.adicionarVertice(novoVertice, listaVizinhos);
  GRAFO_1_MATRIZ_ADJ.imprimirGrafo();

  return 0;
}
