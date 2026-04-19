#include "ListaDeAdjacencia.h"
#include "MatrizDeAdjacencia.h"
#include "MatrizDeIncidencia.h"
#include <fstream>
#include <iostream>

using namespace std;

void criarGrafoDeTeste() {
  ofstream arquivo("grafo_teste8.txt");
  arquivo << "5\n"; // Número de vértices
  arquivo << "A , B\n";
  arquivo << "B , C\n";
  arquivo << "C , D\n";
  arquivo << "D , E\n";
  arquivo << "E , A\n"; // Forma um pentágono (5 arestas)
  arquivo.close();
}

int main() {
  criarGrafoDeTeste();

  cout << "=== TESTE QUESTAO 8: TOTAL DE ARESTAS ===\n";
  cout << "Grafo esperado: 5 arestas (A-B, B-C, C-D, D-E, E-A)\n\n";

  MatrizDeIncidencia<char> matInc("grafo_teste8.txt");
  cout << "[Matriz de Incidencia] Total de Arestas: "
       << matInc.obterTotalDeArestas() << endl;

  MatrizDeAdjacencia<char> matAdj("grafo_teste8.txt");
  cout << "[Matriz de Adjacencia] Total de Arestas: "
       << matAdj.obterTotalDeArestas() << endl;

  ListaDeAdjacencia<char> listAdj("grafo_teste8.txt");
  cout << "[Lista de Adjacencia]  Total de Arestas: "
       << listAdj.obterTotalDeArestas() << endl;

  return 0;
}
