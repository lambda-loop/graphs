
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include "MatrizDeIncidencia.h"

// foi criado um tipo customizado aqui. ele age como uma string, mas burla a limitação do C++ com o caractere ','.
struct Vertice {
    std::string valor;

    Vertice() = default;
    Vertice(std::string v) : valor(v) {}

    // necessário para a matriz organizar os itens dentro do std::map
    bool operator<(const Vertice& outro) const {
        return valor < outro.valor;
    }

    // ensina o cpp a comparar  Vertice com o ',' do header
    bool operator==(char c) const {
        return valor.length() == 1 && valor[0] == c;
    }
};

// ensina o std::cout a imprimir o  Vertice na função imprimirGrafo()
std::ostream& operator<<(std::ostream& os, const Vertice& v) {
    os << v.valor;
    return os;
}

// ensina o std::cin a ler o Vertice (caso o construtor original do header seja compilado)
std::istream& operator>>(std::istream& is, Vertice& v) {
    is >> v.valor;
    return is;
}

void processarGrafo(std::string nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cout << "\n[Erro] Nao foi possivel abrir: " << nomeArquivo << "\n";
        return;
    }

    std::cout << "\n>>> Lendo arquivo: " << nomeArquivo << " <<<\n";

    int qtdVertices;
    arquivo >> qtdVertices;

    // instancia a matriz com o tipo customizado em vez de std::string
    MatrizDeIncidencia<Vertice> g; 

    std::string s_origem, s_destino;
    std::string linha;
    
    while (arquivo >> linha) {
        size_t pos = linha.find(',');
        if (pos == std::string::npos) continue;

        std::string s_origem = linha.substr(0, pos);
        std::string s_destino = linha.substr(pos + 1);

        // encapsula a string dentro do Vertice()
        if (std::isdigit(s_origem[0])) {
            g.adicionarAresta(Vertice(std::to_string(std::stoi(s_origem))), 
                              Vertice(std::to_string(std::stoi(s_destino))));
        } else {
            g.adicionarAresta(Vertice(std::string(1, s_origem[0])), 
                              Vertice(std::string(1, s_destino[0])));
        }
    }

    arquivo.close();

    g.imprimirGrafo();
    
    std::cout << "\n------------------------------------------\n";
}

int main() {
    processarGrafo("./dados_trabalho_01/GRAFO_1.txt");
    processarGrafo("./dados_trabalho_01/GRAFO_2.txt");

    return 0;
}