#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include "MatrizDeIncidencia.h"
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

    GrafoMatrizInc g(qtdVertices, false); 

    std::string s_origem, s_destino;
    char virgula;

    std::string linha;
    // lê a linha inteira
    while (arquivo >> linha) {
        // encontra a posição da vírgula
        size_t pos = linha.find(',');
        if (pos == std::string::npos) continue; // pula se não tiver vírgula

        // separa o que vem antes e o que vem depois da vírgula
        std::string s_origem = linha.substr(0, pos);
        std::string s_destino = linha.substr(pos + 1);

        // verifica se origem e destino é dígito. se sim ele converte pra int
        if (std::isdigit(s_origem[0])) {
            g.adicionarAresta(std::stoi(s_origem), std::stoi(s_destino));
        } else {
            g.adicionarAresta(s_origem[0], s_destino[0]);
        }
    }

    arquivo.close();

    CalculadorDeGrau calc;
    calc.calcularEImprimir(g);
    
    std::cout << "\n------------------------------------------\n";
}

int main() {
    processarGrafo("./dados_trabalho_01/GRAFO_1.txt");
    processarGrafo("./dados_trabalho_01/GRAFO_2.txt");

    return 0;
}