// a definição do grafo como lista de adjacencia esta no .h
#include "ListaDeAdjacencia.h"

using namespace std;

int main(){

    cout << "---------------- GRAFO1 ----------------" << endl;
    ListaDeAdjacencia<char> GRAFO_1("./dados_trabalho_01/GRAFO_1.txt");
    GRAFO_1.imprimirGrafo();


    cout << "---------------- GRAFO2 ----------------" << endl;
    ListaDeAdjacencia<int> GRAFO_2("./dados_trabalho_01/GRAFO_2.txt");
    GRAFO_2.imprimirGrafo();

    return 0;
}