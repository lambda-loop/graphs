#include "ListaDeAdjacencia.h"
#include "MatrizDeAdjacencia.h"

using namespace std;

struct Conversoes{
    template <typename T>
    static MatrizDeAdjacencia<T> listaParaMatriz(ListaDeAdjacencia<T>& listaAdj){
        vector<T> nomes;

        // salvando o nome dos vertices
        for (const auto& [vertice, vizinhos] : listaAdj.adjacentes) {
            nomes.push_back(vertice);
        }

        int n = nomes.size();
        vector<vector<int>> matriz(n, vector<int>(n, 0));

        // criando a matriz de adjacencia vazia
        MatrizDeAdjacencia<T> matrizAdj(matriz, nomes);
        
        // para cada vertice da lista de adjacentes
        // marca como 1 os vertices adjacentes a ele
        for (const auto& [vertice, vizinhos] : listaAdj.adjacentes) {
            int i = matrizAdj.nomeParaIndice[vertice];
            for (const T& vizinho : vizinhos){
                int j = matrizAdj.nomeParaIndice[vizinho];
                matrizAdj.matriz[i][j] = 1;
            }
        }
        
        return matrizAdj;
    }

    template<typename T>
    static ListaDeAdjacencia<T> matrizParaLista(MatrizDeAdjacencia<T>& matrizAdj){
        ListaDeAdjacencia<T> listaAdj;

        for (int i = 0; i < matrizAdj.numVertices; i++){               // para cada linha i da matriz
            T primeiro = matrizAdj.indiceParaNome[i];                  // traduz o indice da linha para nome do vertice e registra o vertice
            for (int j = 0; j < matrizAdj.numVertices; j++){           // para cada coluna j da linha i
                if (matrizAdj.matriz[i][j] == 1){                      // se os vertices i e j forem vizinhos
                    T segundo = matrizAdj.indiceParaNome[j];           // traduz e salva o vertice j
                    listaAdj.adjacentes[primeiro].push_back(segundo);  // coloco o vertice j traduzido para a lista de adjacencia do vertici i traduzido
                }
            }
        }
        return listaAdj;
    }
};

int main(){

    MatrizDeAdjacencia<char> GRAFO1Matriz("./dados_trabalho_01/GRAFO_1.txt");
    ListaDeAdjacencia<char> GRAFO1Lista("./dados_trabalho_01/GRAFO_1.txt");

    MatrizDeAdjacencia<int> GRAFO2Matriz("./dados_trabalho_01/GRAFO_2.txt");
    ListaDeAdjacencia<int> GRAFO2Lista("./dados_trabalho_01/GRAFO_2.txt");


    // GRAFO 1

    cout << "-----------------GRAFO1 (Lista -> Matriz)-----------------" << endl;

    MatrizDeAdjacencia<char> GRAFO1ListaParaMatriz = Conversoes::listaParaMatriz<char>(GRAFO1Lista);
    GRAFO1ListaParaMatriz.imprimirGrafo();


    cout << "-----------------GRAFO1 (Matriz -> Lista)-----------------" << endl;

    ListaDeAdjacencia<char> GRAFO1MatrizParaLista = Conversoes::matrizParaLista<char>(GRAFO1Matriz);
    GRAFO1MatrizParaLista.imprimirGrafo();


    // GRAFO 2
    
    cout << "-----------------GRAFO2 (Lista -> Matriz)-----------------" << endl;

    MatrizDeAdjacencia<int> GRAFO2ListaParaMatriz = Conversoes::listaParaMatriz<int>(GRAFO2Lista);
    GRAFO2ListaParaMatriz.imprimirGrafo();

    cout << "-----------------GRAFO2 (Matriz -> Lista)-----------------" << endl;

    ListaDeAdjacencia<int> GRAFO2MatrizParaLista = Conversoes::matrizParaLista<int>(GRAFO2Matriz);
    GRAFO2MatrizParaLista.imprimirGrafo();

    return 0;
}
