#include "ListaDeAdjacencia.h"
#include "MatrizDeAdjacencia.h"
#include "MatrizDeIncidencia.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {

  cout << "=== TESTE GRAFO 1: TOTAL DE VERTICES ===\n";

  MatrizDeIncidencia<char> matInc("./dados_trabalho_01/GRAFO_1.txt");
  cout << "[Matriz de Incidencia] Total de Vertices: "
       << matInc.obterTotalDeVertices() << endl;

  MatrizDeAdjacencia<char> matAdj("./dados_trabalho_01/GRAFO_1.txt");
  cout << "[Matriz de Adjacencia] Total de Vertices: "
       << matAdj.obterTotalDeVertices() << endl;

  ListaDeAdjacencia<char> listAdj("./dados_trabalho_01/GRAFO_1.txt");
  cout << "[Lista de Adjacencia]  Total de Vertices: "
       << listAdj.obterTotalDeVertices() << endl;

  cout << "=== TESTE GRAFO 2: TOTAL DE VERTICES ===\n";

  MatrizDeIncidencia<char> matInc2("./dados_trabalho_01/GRAFO_2.txt");
  cout << "[Matriz de Incidencia] Total de Vertices: "
       << matInc2.obterTotalDeVertices() << endl;

  MatrizDeAdjacencia<char> matAdj2("./dados_trabalho_01/GRAFO_2.txt");
  cout << "[Matriz de Adjacencia] Total de Vertices: "
       << matAdj2.obterTotalDeVertices() << endl;

  ListaDeAdjacencia<char> listAdj2("./dados_trabalho_01/GRAFO_2.txt");
  cout << "[Lista de Adjacencia]  Total de Vertices: "
       << listAdj2.obterTotalDeVertices() << endl;

  return 0;
}
