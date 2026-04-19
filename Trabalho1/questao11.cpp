#include "ListaDeAdjacencia.h"
#include "MatrizDeAdjacencia.h"
#include "MatrizDeIncidencia.h"
#include <fstream>
#include <iostream>

using namespace std;

void criarGrafosDeTeste() {
  // Grafo 1: Tudo conectado
  ofstream arq1("grafo_conexo.txt");
  arq1 << "4\n";
  arq1 << "A , B\n";
  arq1 << "B , C\n";
  arq1 << "C , D\n";
  arq1.close();

  // Grafo 2: Dividido em duas partes (A-B) e (C-D)
  ofstream arq2("grafo_desconexo.txt");
  arq2 << "4\n";
  arq2 << "A , B\n";
  arq2 << "C , D\n";
  arq2.close();
}

int main() {
  criarGrafosDeTeste();

  cout << "=== TESTE QUESTAO 11: GRAFO CONEXO ===\n\n";

  cout << "--- TESTANDO GRAFO CONEXO ---\n";
  MatrizDeIncidencia<char> mi1("grafo_conexo.txt");
  MatrizDeAdjacencia<char> ma1("grafo_conexo.txt");
  ListaDeAdjacencia<char> la1("grafo_conexo.txt");

  cout << "[Matriz Incidencia] Eh conexo? "
       << (mi1.verificarSeConexo() ? "Sim" : "Nao") << " (Esperado: Sim)\n";
  cout << "[Matriz Adjacencia] Eh conexo? "
       << (ma1.verificarSeConexo() ? "Sim" : "Nao") << " (Esperado: Sim)\n";
  cout << "[Lista Adjacencia]  Eh conexo? "
       << (la1.verificarSeConexo() ? "Sim" : "Nao") << " (Esperado: Sim)\n\n";

  cout << "--- TESTANDO GRAFO DESCONEXO ---\n";
  MatrizDeIncidencia<char> mi2("grafo_desconexo.txt");
  MatrizDeAdjacencia<char> ma2("grafo_desconexo.txt");
  ListaDeAdjacencia<char> la2("grafo_desconexo.txt");

  cout << "[Matriz Incidencia] Eh conexo? "
       << (mi2.verificarSeConexo() ? "Sim" : "Nao") << " (Esperado: Nao)\n";
  cout << "[Matriz Adjacencia] Eh conexo? "
       << (ma2.verificarSeConexo() ? "Sim" : "Nao") << " (Esperado: Nao)\n";
  cout << "[Lista Adjacencia]  Eh conexo? "
       << (la2.verificarSeConexo() ? "Sim" : "Nao") << " (Esperado: Nao)\n";

  return 0;
}
