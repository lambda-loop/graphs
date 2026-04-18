// Representação do Digrafo a partir da Matriz de Adjacências(DIGRAFO1, DIGRAFO2)
#include <iostream>
#include <vector>
#include <functional>
#include "MatrizDeAdjacenciaDigrafo.h" 

int main() {
    cout << "--- DIGRAFO 1 ---" << endl;
    MatrizDeAdjacenciaDigrafo<int> digrafo1("./dados_trabalho_01/DIGRAFO1.txt");
    digrafo1.imprimirGrafo();

    cout << "\n--- DIGRAFO 2 ---" << endl;
    MatrizDeAdjacenciaDigrafo<int> digrafo2("./dados_trabalho_01/DIGRAFO2.txt");
    digrafo2.imprimirGrafo();

    return 0;
}