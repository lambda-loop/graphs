#include "ListaDeAdjacencia.h"
#include "MatrizDeAdjacencia.h"
#include "MatrizDeIncidencia.h"
#include <fstream>
#include <iostream>

using namespace std;

void criarGrafoDeTeste() {
  ofstream arquivo("grafo_teste7.txt");
  arquivo
      << "4\n"; // Número de vértices (lido pelas matrizes, ignorado pela lista)
  arquivo << "A , B\n";
  arquivo << "A , C\n";
  arquivo << "B , D\n";
  arquivo << "C , D\n";
  arquivo.close();
}

int main() {
  criarGrafoDeTeste();

  cout << "=== TESTE QUESTAO 7: TOTAL DE VERTICES ===\n";
  cout << "Grafo esperado: 4 vertices (A, B, C, D)\n\n";

  MatrizDeIncidencia<char> matInc("grafo_teste7.txt");
  cout << "[Matriz de Incidencia] Total de Vertices: "
       << matInc.obterTotalDeVertices() << endl;

  MatrizDeAdjacencia<char> matAdj("grafo_teste7.txt");
  cout << "[Matriz de Adjacencia] Total de Vertices: "
       << matAdj.obterTotalDeVertices() << endl;

  ListaDeAdjacencia<char> listAdj("grafo_teste7.txt");
  cout << "[Lista de Adjacencia]  Total de Vertices: "
       << listAdj.obterTotalDeVertices() << endl;

  return 0;
}
