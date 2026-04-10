#include <iostream>
#include <vector>
#include <iomanip>
#include <cctype>

struct GrafoMatrizInc {
    int vertices;
    bool direcionado;
    std::vector<std::vector<int>> matriz;
    bool usarLetrasNaImpressao;

    //função que faz o trabalho real usando os índices do computador (0, 1, 2...)
    void registrarConexao(int origem, int destino) {
        //cria uma nova aresta com o tamanho dos vértices, toda zerada
        std::vector<int> novaAresta(vertices, 0);

        if (direcionado) {
            novaAresta[origem] = -1;
            novaAresta[destino] = 1;
        } else {
            novaAresta[origem] = 1;
            novaAresta[destino] = 1;
        }

        matriz.push_back(novaAresta);
    }

    GrafoMatrizInc(int ver, bool dir = false) : vertices(ver), direcionado(dir), usarLetrasNaImpressao(false) {}

    //versao com numeros
    void adicionarAresta(int origem_usuario, int destino_usuario) {
        //para que o usuario faça as ligações entre vértices começando do 1
        int origem = origem_usuario - 1;
        int destino = destino_usuario - 1;

        registrarConexao(origem, destino);
    }

    //versao com letras
    void adicionarAresta(char origem_usuario, char destino_usuario) {
        //pra imprimir as letras na matriz
        usarLetrasNaImpressao = true;

        int origem = std::tolower(origem_usuario) - 'a';
        int destino = std::tolower(destino_usuario) - 'a';

        registrarConexao(origem, destino);
    }

    void imprimirMatriz() {
        int qtdArestas = matriz.size();
        
        std::cout << "     ";
        for (int j = 0; j < vertices; ++j) {
            if (usarLetrasNaImpressao) {
                //converte 0, 1, 2 para A, B, C...
                char nomeVertice = 'a' + j; 
                std::cout << "V" << nomeVertice << "  ";
            } else {
                std::cout << "V" << (j + 1) << "  ";
            }
        }
        std::cout << "\n    " << std::string(vertices * 4, '-') << "\n";

        for (int i = 0; i < qtdArestas; ++i) {
            std::cout << "A" << i + 1 << " | ";
            for (int j = 0; j < vertices; ++j) {
                std::cout << std::setw(2) << matriz[i][j] << "  ";
            }
            std::cout << "\n";
        }
    }
};

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
