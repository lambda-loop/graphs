#include "MatrizDeIncidencia.h"

int main() {
  GrafoMatrizInc g(8);

  g.adicionarAresta(1, 2);
  g.adicionarAresta(1, 2);
  g.adicionarAresta(1, 2);
  g.adicionarAresta(1, 2);
  g.adicionarAresta(1, 2);


  g.imprimirMatriz();

  return 0;
}
