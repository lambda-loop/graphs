// a definição do grafo como matriz de adjacencia esta no .h
#include "MatrizDeAdjacencia.h"

int main(){

    cout << "---------------- GRAFO1 ----------------" << endl;
    MatrizDeAdjacencia<char> GRAFO_1("./dados_trabalho_01/GRAFO_1.txt");
    GRAFO_1.imprimirGrafo();

    cout << "---------------- GRAFO2 ----------------" << endl;
    MatrizDeAdjacencia<int> GRAFO_2("./dados_trabalho_01/GRAFO_2.txt");
    GRAFO_2.imprimirGrafo();

    return 0;
}
