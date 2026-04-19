
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

#include "MatrizDeAdjacencia.h"
#include "CalcularGrauVertices.h" 

void processarGrafo(std::string nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cout << "\n[Erro] Nao foi possivel abrir: " << nomeArquivo << "\n";
        return;
    }

    std::cout << "\n>>> Lendo arquivo: " << nomeArquivo << " <<<\n";

    int qtdVertices;
    arquivo >> qtdVertices;

    // inicializando a Matriz de Adjacência usando std::string para aceitar letras e números
    MatrizDeAdjacencia<std::string> g;
    g.numVertices = qtdVertices;
    g.matriz.assign(qtdVertices, std::vector<int>(qtdVertices, 0));
    g.indiceParaNome.resize(qtdVertices);
    
    int proximoIndice = 0;

    // função lambda para adicionar arestas manualmente na matriz instanciada
    auto adicionarAresta = [&](std::string u, std::string v) {
        if (g.nomeParaIndice.find(u) == g.nomeParaIndice.end()) {
            g.nomeParaIndice[u] = proximoIndice;
            g.indiceParaNome[proximoIndice] = u;
            proximoIndice++;
        }
        if (g.nomeParaIndice.find(v) == g.nomeParaIndice.end()) {
            g.nomeParaIndice[v] = proximoIndice;
            g.indiceParaNome[proximoIndice] = v;
            proximoIndice++;
        }
        int index1 = g.nomeParaIndice[u];
        int index2 = g.nomeParaIndice[v];
        
        g.matriz[index1][index2] = 1;
        g.matriz[index2][index1] = 1; 
    };

    std::string linha;
    while (arquivo >> linha) {
        size_t pos = linha.find(',');
        if (pos == std::string::npos) continue;

        std::string s_origem = linha.substr(0, pos);
        std::string s_destino = linha.substr(pos + 1);

        if (std::isdigit(s_origem[0])) {
            // Se for número, converte e manda como string
            adicionarAresta(std::to_string(std::stoi(s_origem)), std::to_string(std::stoi(s_destino)));
        } else {
            // Se for char, pega o caractere e manda como string
            adicionarAresta(std::string(1, s_origem[0]), std::string(1, s_destino[0]));
        }
    }

    arquivo.close();

    CalculadorDeGrau<std::string> calc;
    calc.calcularEImprimir(g);
    
    std::cout << "\n------------------------------------------\n";
}

int main() {
    processarGrafo("./dados_trabalho_01/GRAFO_1.txt");
    processarGrafo("./dados_trabalho_01/GRAFO_2.txt");

    return 0;
}