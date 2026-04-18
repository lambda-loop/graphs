#ifndef BICONECTIVIDADE_H
#define BICONECTIVIDADE_H

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <stack>

using namespace std;

struct Biconectividade {
    map<int, int> num;    
    map<int, int> lowpt;  
    stack<pair<int, int>> pilhaArestas;
    int contador = 0;

    void encontrarBlocos(int v, int pai, function<vector<int>(int)> getNeighbors) {
        /*
        PASSO INICIAL: Identificar demarcadores e articulações de G, através de uma busca 
        em profundidade que produz a árvore T
        */
        num[v] = lowpt[v] = ++contador;

        vector<int> neighbors = getNeighbors(v);
        int filhosDaRaiz = 0;

        for (int w : neighbors) {
            // Caso seja aresta pai: ignora
            if (w == pai) continue; 

            // Caso w seja aresta de árvore: salva ela (pode ser um bloco)
            if (num[w] == 0) { 
                filhosDaRaiz++;
                pilhaArestas.push({v, w}); 

                // Repete e atualiza lowpt
                encontrarBlocos(w, v, getNeighbors);
                lowpt[v] = min(lowpt[v], lowpt[w]);

                /*
                PASSO GERAL: Escolher demarcador w tal que a subárvore T de T, não possui articulações de G.
                Se Lowpt(w) >= num(v), então w é demarcador de v
                */ 
                if (lowpt[w] >= num[v]) {
                    // v é articulação se: não for raiz ou for raiz com > 1 filho
                    if (pai != -1 || filhosDaRaiz > 1) {
                        cout << "Articulacao detectada: " << v << endl;
                    }

                    // Forma bloco, pois, satisfez (lowpt[w] >= num[v])
                    cout << "Bloco: ";
                    while (true) {
                        pair<int, int> aresta = pilhaArestas.top();
                        pilhaArestas.pop();
                        cout << "(" << aresta.first << "," << aresta.second << ") ";
                        if (aresta.first == v && aresta.second == w) break;
                    }
                    cout << endl;
                }
            }
            // Caso w seja uma aresta de retorno: atualiza o lowpt 
            else if (num[w] < num[v]) {
                pilhaArestas.push({v, w});
                lowpt[v] = min(lowpt[v], num[w]);
            }
        }
    }
};

#endif