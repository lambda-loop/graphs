#include "incidence_matrix.h"
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  GrafoMatrizInc<int> grafo("grafo.txt", false);
  grafo.imprimirMatriz();
}
