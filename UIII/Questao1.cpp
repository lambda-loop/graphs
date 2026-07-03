#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <limits>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

struct Instance {
    std::string name;
    std::vector<std::vector<double>> matrix;
    int n;
};

/**
 Função auxiliar para ler um arquivo CSV e retornar uma instância contendo a matriz de custos.
 */
Instance parseCsvFile(const std::string& filePath, const std::string& fileName) {
    Instance inst;
    inst.name = fileName;
    
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir: " << filePath << std::endl;
        inst.n = 0;
        return inst;
    }

    std::vector<std::vector<double>> rawMatrix;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;

        std::vector<double> row;
        std::string token = "";
        bool in_quotes = false;
        bool valid_row = true;

        for (size_t i = 0; i <= line.size(); ++i) {
            char c = (i < line.size()) ? line[i] : ',';
            
            if (c == '"') {
                in_quotes = !in_quotes; // Liga/desliga o modo de aspas
            } 
            else if (c == ',' && !in_quotes) {
                if (!token.empty()) {
                    try {
                        row.push_back(std::stod(token));
                    } catch (...) {
                        valid_row = false;
                        break; 
                    }
                }
                token = "";
            } 
            else if (c == ',' && in_quotes) {
                token += '.';
            } 
            else {
                if (c != ' ') token += c;
            }
        }
        if (valid_row && !row.empty()) {
            rawMatrix.push_back(row);
        }
    }
    file.close();

    if (rawMatrix.empty()) {
        inst.n = 0;
        return inst;
    }

    int numRows = rawMatrix.size();
    bool hasIndexColumn = true;
    for (int i = 0; i < numRows; ++i) {
        if (rawMatrix[i].size() != (size_t)(numRows + 1)) {
            hasIndexColumn = false;
            break;
        }
    }
    
    if (hasIndexColumn) {
        for (int i = 0; i < numRows; ++i) {
            rawMatrix[i].erase(rawMatrix[i].begin());
        }
    }

    inst.matrix = rawMatrix;
    inst.n = rawMatrix.size();

    for (int i = 0; i < inst.n; ++i) {
        if (inst.matrix[i].size() != (size_t)inst.n) {
            inst.n = 0;
            break;
        }
    }

    return inst;
}

double calculateTourCost(const std::vector<int>& tour, const std::vector<std::vector<double>>& matrix) {
    double totalCost = 0.0;
    int n = tour.size();
    for (int i = 0; i < n; ++i) {
        int u = tour[i];
        int v = tour[(i + 1) % n];
        totalCost += matrix[u][v];
    }
    return totalCost;
}

std::vector<int> NearestNeighbor(const std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    std::vector<int> tour;
    std::vector<bool> visited(n, false);
    
    int current = 0; 
    tour.push_back(current);
    visited[current] = true;
    
    for (int step = 1; step < n; ++step) {
        int nextNode = -1;
        double minCost = std::numeric_limits<double>::max();
        
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && matrix[current][i] < minCost) {
                minCost = matrix[current][i];
                nextNode = i;
            }
        }
        
        if (nextNode == -1) {
            for (int i = 0; i < n; ++i) {
                if (!visited[i]) { nextNode = i; break; }
            }
        }
        
        current = nextNode;
        tour.push_back(current);
        visited[current] = true;
    }
    return tour;
}

/*
Essa busca local apaga 2 arestas de cada vez,
e tenta religar os vértices de forma diferente,
verificando se o custo da rota diminui.
*/
std::vector<int> localSearch2Opt(const std::vector<int>& initialTour, const std::vector<std::vector<double>>& matrix) {
    int n = initialTour.size();
    std::vector<int> bestTour = initialTour;
    double bestCost = calculateTourCost(bestTour, matrix);
    bool improved = true;
    
    while (improved) {
        improved = false;
        for (int i = 0; i < n - 1; ++i) { //escolhemos a linha da aresta ser cortada
            for (int j = i + 2; j < n; ++j) { //escolhemos a coluna da aresta ser cortada
                
                // retirando o caso do corte que inverteria o tour inteiro
                if (i == 0 && j == n - 1) continue; 
                
                std::vector<int> newTour = bestTour;

                //aqui revertemos a seção que foi cortada,
                //criando uma nova rota
                std::reverse(newTour.begin() + i + 1, newTour.begin() + j + 1);
                
                //checamos se a nova rota é melhor que a anterior
                double newCost = calculateTourCost(newTour, matrix);
                if (newCost < bestCost - 1e-5) {
                    bestTour = newTour;
                    bestCost = newCost;
                    improved = true;
                }
            }
        }
    }
    //retornamos a melhor rota encontrada
    return bestTour;
}

int main() {
    std::string folderPath = "./dados/tabelas"; 
    
    std::cout << "=== Buscando arquivos CSV na pasta '" << folderPath << "' ===" << std::endl;
    
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "Erro: A pasta '" << folderPath << "' nao existe ou nao e um diretorio valido." << std::endl;
        return 1;
    }

    std::vector<Instance> instances;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".csv") {
            Instance inst = parseCsvFile(entry.path().string(), entry.path().filename().string());
            if (inst.n >= 6) { 
                instances.push_back(inst);
            } else {
                std::cerr << "[Aviso] Arquivo " << entry.path().filename().string() << " ignorado (Matriz invalida ou N < 6)." << std::endl;
            }
        }
    }

    if (instances.empty()) {
        std::cerr << "Nenhum arquivo .csv com matriz quadrada valida (N >= 6) foi encontrado na pasta." << std::endl;
        return 1;
    }

    std::sort(instances.begin(), instances.end(), [](const Instance& a, const Instance& b) {
        return a.name < b.name;
    });
    
    std::cout << "Sucesso! Foram processados " << instances.size() << " arquivos CSV.\n" << std::endl;
    
    std::ofstream txtOut("resultados_questao1.txt");
    std::string headerStr = "=== RESUMO DOS RESULTADOS (VIZINHO MAIS PRÓXIMO DETERMINÍSTICO + BUSCA LOCAL 2-OPT) ===";
    
    std::cout << headerStr << "\n" << std::endl;
    if (txtOut.is_open()) txtOut << headerStr << "\n\n";
    
    for (const auto& inst : instances) {
        std::stringstream ss;
        ss << "========================================================\n";
        ss << "Instância Arquivo: " << inst.name << " (Tamanho N = " << inst.n << " Cidades)\n";
        ss << "========================================================\n";
        
        double totalDurationMs = 0.0;
        
        // Vetores para armazenar as rotas
        std::vector<int> rawTour;
        std::vector<int> finalTour;
        
        for (int run = 0; run < 20; ++run) {
            auto startClock = std::chrono::high_resolution_clock::now();

            rawTour = NearestNeighbor(inst.matrix);
            finalTour = localSearch2Opt(rawTour, inst.matrix);
            
            auto endClock = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = endClock - startClock;
            
            totalDurationMs += duration.count();
        }

        // Calcula o custo das rotas geradas
        auto rawTourCost = calculateTourCost(rawTour, inst.matrix);
        auto finalTourCost = calculateTourCost(finalTour, inst.matrix);
        
        // O tempo médio computacional nas 20 rodadas
        double avgTimeMs = totalDurationMs / 20.0;
        
        ss << "Vizinho Mais Próximo Puro (Sem Busca Local): " << std::fixed << std::setprecision(2) << rawTourCost << "\n";
        ss << "  -> MENOR VALOR ENCONTRADO (Com busca 2opt): " << finalTourCost << "\n";
        ss << "  -> TEMPO MÉDIO DE EXECUÇÃO:               " << avgTimeMs << " ms\n";
        ss << "  -> Rota do Circuito: ";
        
        for (size_t i = 0; i < finalTour.size(); ++i) {
            ss << finalTour[i] + 1 << (i == finalTour.size() - 1 ? "" : " -> ");
        }
        ss << " -> " << finalTour[0] + 1 << " (Retorno)\n\n";
        
        std::cout << ss.str();
        if (txtOut.is_open()) txtOut << ss.str();
    }
    
    if (txtOut.is_open()) {
        txtOut.close();
        std::cout << "Resumo gerado no arquivo 'resultados_questao1.txt'." << std::endl;
    }
    
    return 0;
}