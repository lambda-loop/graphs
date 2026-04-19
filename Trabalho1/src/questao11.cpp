#include "ListaDeAdjacencia.h"
#include "MatrizDeAdjacencia.h"
#include "MatrizDeIncidencia.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {

  cout << "=== TESTE GRAFO1 ===\n\n";
  MatrizDeIncidencia<char> mi1("./dados_trabalho_01/GRAFO_1.txt");
  MatrizDeAdjacencia<char> ma1("./dados_trabalho_01/GRAFO_1.txt");
  ListaDeAdjacencia<char> la1("./dados_trabalho_01/GRAFO_1.txt");

  cout << "[Matriz Incidencia] Eh conexo? "
       << (mi1.verificarSeConexo() ? "Sim" : "Nao") << "\n";
  cout << "[Matriz Adjacencia] Eh conexo? "
       << (ma1.verificarSeConexo() ? "Sim" : "Nao") << "\n";
  cout << "[Lista Adjacencia]  Eh conexo? "
       << (la1.verificarSeConexo() ? "Sim" : "Nao") << "\n\n";

  cout << "--- TESTE GRAFO 2 ---\n";
  MatrizDeIncidencia<char> mi2("./dados_trabalho_01/GRAFO_2.txt");
  MatrizDeAdjacencia<char> ma2("./dados_trabalho_01/GRAFO_2.txt");
  ListaDeAdjacencia<char> la2("./dados_trabalho_01/GRAFO_2.txt");

  cout << "[Matriz Incidencia] Eh conexo? "
       << (mi2.verificarSeConexo() ? "Sim" : "Nao") << "\n";
  cout << "[Matriz Adjacencia] Eh conexo? "
       << (ma2.verificarSeConexo() ? "Sim" : "Nao") << "\n";
  cout << "[Lista Adjacencia]  Eh conexo? "
       << (la2.verificarSeConexo() ? "Sim" : "Nao") << "\n";

  return 0;
}
