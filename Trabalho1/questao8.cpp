#include "ListaDeAdjacencia.h"
#include "MatrizDeAdjacencia.h"
#include "MatrizDeIncidencia.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {

  cout << "=== TESTE GRAFO 1: TOTAL DE ARESTAS ===\n";
  MatrizDeIncidencia<char> matInc("./dados_trabalho_01/GRAFO_1.txt");
  cout << "[Matriz de Incidencia] Total de Arestas: "
       << matInc.obterTotalDeArestas() << endl;

  MatrizDeAdjacencia<char> matAdj("./dados_trabalho_01/GRAFO_1.txt");
  cout << "[Matriz de Adjacencia] Total de Arestas: "
       << matAdj.obterTotalDeArestas() << endl;

  ListaDeAdjacencia<char> listAdj("./dados_trabalho_01/GRAFO_1.txt");
  cout << "[Lista de Adjacencia]  Total de Arestas: "
       << listAdj.obterTotalDeArestas() << endl;

  cout << "=== TESTE GRAFO 1: TOTAL DE ARESTAS ===\n";
  MatrizDeIncidencia<char> matInc2("./dados_trabalho_01/GRAFO_2.txt");
  cout << "[Matriz de Incidencia] Total de Arestas: "
       << matInc2.obterTotalDeArestas() << endl;

  MatrizDeAdjacencia<char> matAdj2("./dados_trabalho_01/GRAFO_2.txt");
  cout << "[Matriz de Adjacencia] Total de Arestas: "
       << matAdj2.obterTotalDeArestas() << endl;

  ListaDeAdjacencia<char> listAdj2("./dados_trabalho_01/GRAFO_2.txt");
  cout << "[Lista de Adjacencia]  Total de Arestas: "
       << listAdj2.obterTotalDeArestas() << endl;
  
  return 0;
}
