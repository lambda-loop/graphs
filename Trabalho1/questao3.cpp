#include "MatrizDeIndicencia.h"

int main() {
  GrafoMatrizInc g(8);

  g.adicionarAresta('a', 'b');
  g.adicionarAresta('b', 'c');
  g.adicionarAresta('b', 'd');
  g.adicionarAresta('c', 'd');
  g.adicionarAresta('c', 'e');
  g.adicionarAresta('e', 'f');
  g.adicionarAresta('f', 'g');
  g.adicionarAresta('f', 'h');
  g.adicionarAresta('g', 'h');

  g.imprimirMatriz();

  return 0;
}
