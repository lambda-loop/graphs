
// 17 - Representação do grafo-direcionado a partir da matriz de incidencia
#include "GrafoMatrizInc.h"

int main() {
  GrafoMatrizInc g1(13, true);

  g1.adicionarAresta(1,2);
  g1.adicionarAresta(2,3);
  g1.adicionarAresta(3,1);
  g1.adicionarAresta(3,4);
  g1.adicionarAresta(4,5);
  g1.adicionarAresta(5,6);
  g1.adicionarAresta(5,8);
  g1.adicionarAresta(6,7);
  g1.adicionarAresta(7,6);
  g1.adicionarAresta(7,9);
  g1.adicionarAresta(8,4);
  g1.adicionarAresta(8,10);
  g1.adicionarAresta(9,8);
  g1.adicionarAresta(11,12);
  g1.adicionarAresta(12,13);
  g1.adicionarAresta(13,12);

  g1.imprimirMatriz();

  GrafoMatrizInc g2(13, true);

  g2.adicionarAresta(1,2);
  g2.adicionarAresta(1,2);
  g2.adicionarAresta(2,3);
  g2.adicionarAresta(3,1);
  g2.adicionarAresta(3,4);
  g2.adicionarAresta(4,5);
  g2.adicionarAresta(5,6);
  g2.adicionarAresta(5,8);
  g2.adicionarAresta(6,7);
  g2.adicionarAresta(7,6);
  g2.adicionarAresta(7,9);
  g2.adicionarAresta(8,4);
  g2.adicionarAresta(8,10);
  g2.adicionarAresta(9,8);
  g2.adicionarAresta(10,12);
  g2.adicionarAresta(11,12);
  g2.adicionarAresta(12,13);
  g2.adicionarAresta(13,12);

  g2.imprimirMatriz();
  return 0;
}
