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
#include <dirent.h> // Substitui pois o <filesystem> estava com um bug de compilação na minha máquina | Ao compilar, adicionar a flag de linkagem "-lstdc++fs"
#include <random>

struct Instance {
    std::string name;
    std::vector<std::vector<double>> matrix;
    int n;
};

// ============================================================================
// FUNÇÕES DE LEITURA E CÁLCULO BASE (Reaproveitadas da Q1 / Q3)
// ============================================================================

/**
 * @brief Lê um arquivo CSV e retorna uma instância contendo a matriz de custos.
 * Formato de entrada: arquivo .csv contendo uma matriz quadrada de distâncias
 * (podendo ter uma coluna extra de índice na primeira coluna, que é removida
 * automaticamente caso detectada).
 * @param filePath Caminho do arquivo.
 * @param fileName Nome do arquivo (usado apenas para exibição/organização).
 * @return Estrutura Instance populada com a matriz e o tamanho N. Caso o
 * arquivo seja inválido, retorna uma instância com n = 0.
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
                in_quotes = !in_quotes;
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

/**
 * @brief Calcula o custo total de uma rota (ciclo fechado).
 * Entrada: vetor com a sequência de vértices (tour) e a matriz de custos.
 * Saída: soma dos custos das arestas percorridas, incluindo o retorno ao
 * vértice inicial.
 */
double calculateTourCost(const std::vector<int>& tour, const std::vector<std::vector<double>>& matrix) {
    double cost = 0.0;
    int n = tour.size();
    for (int i = 0; i < n; ++i) {
        int u = tour[i];
        int v = tour[(i + 1) % n];
        cost += matrix[u][v];
    }
    return cost;
}

/**
 * @brief Heurística Construtiva Farthest Insertion para o TSP.
 * Substitui o Vizinho Mais Próximo (Q4 original) para gerar o indivíduo
 * "bom" da população inicial (elitismo inicial), em linha com a
 * modificação feita na nova versão da Q3.
 * @param matrix Matriz de custos/distâncias do problema.
 * @return Uma rota estruturada contendo todas as cidades visitadas uma única
 * vez.
 */
std::vector<int> farthestInsertion(const std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    if (n == 0) return {};
    if (n == 1) return {0};

    std::vector<bool> inTour(n, false);
    std::vector<int> tour;
    tour.reserve(n);

    // encontra o par de cidades mais distante para iniciar
    int firstCity = 0;
    int secondCity = 0;
    double maxDist = -1.0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (matrix[i][j] > maxDist) {
                maxDist = matrix[i][j];
                firstCity = i;
                secondCity = j;
            }
        }
    }

    tour.push_back(firstCity);
    tour.push_back(secondCity);
    inTour[firstCity] = true;
    inTour[secondCity] = true;

    while (tour.size() < (size_t)n) {
        int farthestCity = -1;
        double maxMinDistance = -1.0;

        // encontra a cidade fora da rota cuja distância mínima para qualquer
        // cidade já na rota seja a maior possível
        for (int i = 0; i < n; ++i) {
            if (!inTour[i]) {
                double minDistanceToTour = std::numeric_limits<double>::max();
                for (int cityInTour : tour) {
                    if (matrix[i][cityInTour] < minDistanceToTour) {
                        minDistanceToTour = matrix[i][cityInTour];
                    }
                }

                if (minDistanceToTour > maxMinDistance) {
                    maxMinDistance = minDistanceToTour;
                    farthestCity = i;
                }
            }
        }

        // encontrar a melhor aresta (i, j) na rota atual para inserir a cidade
        int bestInsertionIndex = -1;
        double minInsertionCost = std::numeric_limits<double>::max();

        for (size_t i = 0; i < tour.size(); ++i) {
            int u = tour[i];
            int v = tour[(i + 1) % tour.size()];

            double insertionCost =
                matrix[u][farthestCity] + matrix[farthestCity][v] - matrix[u][v];
            if (insertionCost < minInsertionCost) {
                minInsertionCost = insertionCost;
                bestInsertionIndex = i + 1;
            }
        }

        tour.insert(tour.begin() + bestInsertionIndex, farthestCity);
        inTour[farthestCity] = true;
    }

    return tour;
}

// ============================================================================
// BUSCAS LOCAIS | ALGORITMO MEMÉTICO (mantidas da versão original da Q4)
// ============================================================================

/**
 * @brief Busca local usando 2-opt
 * Remove duas arestas do tour e reconecta invertendo o segmento entre elas,
 * mantendo a alteração sempre que reduzir o custo total.
 * Entrada: um tour e a matriz de custos | Saída: tour possivelmente melhorado.
 */
std::vector<int> localSearch2Opt(std::vector<int> tour, const std::vector<std::vector<double>>& matrix) {
    int n = tour.size();
    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 2; j < n; ++j) {
                if (i == 0 && j == n - 1) continue;

                double currentDist = matrix[tour[i]][tour[i + 1]] + matrix[tour[j]][tour[(j + 1) % n]];
                double newDist = matrix[tour[i]][tour[j]] + matrix[tour[i + 1]][tour[(j + 1) % n]];

                if (newDist < currentDist - 1e-9) {
                    std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
                    improved = true;
                }
            }
        }
    }
    return tour;
}

/**
 * @brief Busca local usando Swap
 * Testa a troca de posição entre cada par de cidades do tour, mantendo a
 * troca sempre que o custo total diminuir | Se não melhorar, faz backtrack
 * Entrada: um tour e a matriz de custos | Saída: tour possivelmente melhorado.
 */
std::vector<int> localSearchSwap(std::vector<int> tour, const std::vector<std::vector<double>>& matrix) {
    int n = tour.size();
    double bestCost = calculateTourCost(tour, matrix);
    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(tour[i], tour[j]);
                double newCost = calculateTourCost(tour, matrix);
                if (newCost < bestCost - 1e-9) {
                    bestCost = newCost;
                    improved = true;
                } 
                else {
                    std::swap(tour[i], tour[j]);
                }
            }
        }
    }
    return tour;
}

/**
 * @brief Busca local usando Shift
 * Remove uma cidade de uma posição do tour e reinsere em outra posição,
 * mantendo a alteração sempre que reduzir o custo total.
 * Entrada: um tour e a matriz de custos | Saída: tour possivelmente melhorado.
 */
std::vector<int> localSearchShift(std::vector<int> tour, const std::vector<std::vector<double>>& matrix) {
    int n = tour.size();
    double bestCost = calculateTourCost(tour, matrix);
    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                std::vector<int> newTour = tour;
                int city = newTour[i];
                newTour.erase(newTour.begin() + i);
                newTour.insert(newTour.begin() + j, city);
                double newCost = calculateTourCost(newTour, matrix);
                if (newCost < bestCost - 1e-9) {
                    tour = newTour;
                    bestCost = newCost;
                    improved = true;
                }
            }
        }
    }
    return tour;
}

/**
 * @brief Aplica aleatoriamente uma das 3 buscas locais implementadas acima
 * Entrada: um tour e a matriz de custos. Saída: tour refinado por uma busca
 * local escolhida aleatoriamente.
 */
std::vector<int> applyLocalSearch(std::vector<int> tour, const std::vector<std::vector<double>>& matrix, std::mt19937& rng) {
    std::uniform_int_distribution<int> strategyDist(0, 2);
    int strategy = strategyDist(rng);
    if (strategy == 0) return localSearch2Opt(tour, matrix);
    if (strategy == 1) return localSearchSwap(tour, matrix);
    return localSearchShift(tour, matrix);
}

// ============================================================================
// OPERADORES DO ALGORITMO GENÉTICO (Reaproveitados da nova versão da Q3)
// ============================================================================

/**
 * @brief Seleção por Torneio.
 * Escolhe k indivíduos aleatórios da população e retorna o de menor custo
 * (melhor fitness).
 */
std::vector<int> tournamentSelection(const std::vector<std::vector<int>>& pop,
                                     const std::vector<std::vector<double>>& matrix,
                                     std::mt19937& rng, int k = 3) {
    std::uniform_int_distribution<int> dist(0, pop.size() - 1);

    int bestIdx = dist(rng);
    double bestCost = calculateTourCost(pop[bestIdx], matrix);

    for (int i = 1; i < k; ++i) {
        int idx = dist(rng);
        double cost = calculateTourCost(pop[idx], matrix);
        if (cost < bestCost) {
            bestCost = cost;
            bestIdx = idx;
        }
    }
    return pop[bestIdx];
}

// função para adicionar vizinhos sem duplicar (necessária para o Edge
// Recombination Crossover)
void addEdge(std::vector<std::vector<int>>& edgeMap, int node, int neighbor) {
    if (std::find(edgeMap[node].begin(), edgeMap[node].end(), neighbor) ==
        edgeMap[node].end()) {
        edgeMap[node].push_back(neighbor);
    }
}

// remove uma cidade da lista de vizinhos de todas as outras cidades
// (necessária para o Edge Recombination Crossover)
void removeNodeFromMap(std::vector<std::vector<int>>& edgeMap, int nodeToRemove) {
    for (auto& neighbors : edgeMap) {
        neighbors.erase(
            std::remove(neighbors.begin(), neighbors.end(), nodeToRemove),
            neighbors.end());
    }
}

/**
 * @brief Cruzamento: Edge Recombination Crossover (ERX).
 * Constrói um mapa de arestas a partir de ambos os pais e monta o filho
 * priorizando, a cada passo, o vizinho com menor número de arestas restantes
 * (preservando ao máximo a estrutura de adjacências dos pais).
 */
std::vector<int> edgeRecombinationCrossover(const std::vector<int>& p1,
                                            const std::vector<int>& p2,
                                            std::mt19937& rng) {
    int n = p1.size();
    std::vector<int> child;
    child.reserve(n);

    // constroi o Mapa de Arestas
    std::vector<std::vector<int>> edgeMap(n);
    for (int i = 0; i < n; ++i) {
        // pai 1
        int p1_left = p1[(i - 1 + n) % n];
        int p1_right = p1[(i + 1) % n];
        addEdge(edgeMap, p1[i], p1_left);
        addEdge(edgeMap, p1[i], p1_right);

        // pai 2
        int p2_left = p2[(i - 1 + n) % n];
        int p2_right = p2[(i + 1) % n];
        addEdge(edgeMap, p2[i], p2_left);
        addEdge(edgeMap, p2[i], p2_right);
    }

    std::vector<bool> visited(n, false);

    // define o nó inicial aleatoriamente
    int current = (rng() % 2 == 0) ? p1[0] : p2[0];
    child.push_back(current);
    visited[current] = true;
    removeNodeFromMap(edgeMap, current);

    while (child.size() < (size_t)n) {
        const auto& neighbors = edgeMap[current];
        int nextNode = -1;

        if (!neighbors.empty()) {
            // seleciona o vizinho com o menor numero de caminhos restantes
            int minEdges = std::numeric_limits<int>::max();
            std::vector<int> candidates;

            for (int neighbor : neighbors) {
                int edgeCount = edgeMap[neighbor].size();
                if (edgeCount < minEdges) {
                    minEdges = edgeCount;
                    candidates = {neighbor};
                } else if (edgeCount == minEdges) {
                    candidates.push_back(neighbor);
                }
            }

            // se houver mais de um com o mesmo número mínimo, escolhe aleatoriamente
            std::uniform_int_distribution<int> dist(0, candidates.size() - 1);
            nextNode = candidates[dist(rng)];
        } else {
            std::vector<int> unvisited;
            for (int i = 0; i < n; ++i) {
                if (!visited[i]) unvisited.push_back(i);
            }
            std::uniform_int_distribution<int> dist(0, unvisited.size() - 1);
            nextNode = unvisited[dist(rng)];
        }

        current = nextNode;
        child.push_back(current);
        visited[current] = true;
        removeNodeFromMap(edgeMap, current);
    }

    return child;
}

/**
 * @brief Mutação por Inversão (Inversion Mutation).
 * Escolhe dois pontos aleatórios e inverte o sub-trecho entre eles, aplicada
 * de acordo com uma taxa de probabilidade.
 */
void mutateInversion(std::vector<int>& tour, double mutationRate, std::mt19937& rng) {
    std::uniform_real_distribution<double> probDist(0.0, 1.0);

    if (probDist(rng) <= mutationRate) {
        int n = tour.size();

        std::uniform_int_distribution<int> indexDist(0, n - 1);
        int idx1 = indexDist(rng);
        int idx2 = indexDist(rng);

        if (idx1 > idx2) {
            std::swap(idx1, idx2);
        }

        std::reverse(tour.begin() + idx1, tour.begin() + idx2 + 1);
    }
}

// ============================================================================
// ALGORITMO MEMÉTICO PRINCIPAL (v2 - baseado na nova Q3: Farthest Insertion +
// Edge Recombination Crossover + Inversion Mutation)
// ============================================================================

/**
 * @brief Algoritmo Memético v2: Algoritmo Genético (com Farthest Insertion,
 * Edge Recombination Crossover e Mutação por Inversão) + Busca Local sobre
 * os filhos da geração.
 * @param matrix Matriz de custos do problema
 * @param popSize Tamanho da população
 * @param generations Número de gerações
 * @param crossoverRate Taxa de cruzamento
 * @param mutationRate Taxa de mutação
 * @param localSearchRate Probabilidade de um filho recém-gerado passar por
 * uma das buscas locais | Caso evolua será substituído
 * @return Melhor custo e melhor rota encontrados
 */
std::pair<double, std::vector<int>> runMemeticAlgorithm(const std::vector<std::vector<double>>& matrix,
                                                        int popSize, int generations,
                                                        double crossoverRate, double mutationRate,
                                                        double localSearchRate) {
    int n = matrix.size();
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> probDist(0.0, 1.0);

    // Geração da População Inicial
    std::vector<std::vector<int>> population(popSize, std::vector<int>(n));
    std::vector<int> baseTour(n);
    for (int i = 0; i < n; ++i) baseTour[i] = i;

    // Insere o Farthest Insertion refinado (pela busca) como o primeiro indivíduo
    population[0] = applyLocalSearch(farthestInsertion(matrix), matrix, rng);

    // O restante da população é gerado aleatoriamente
    for (int i = 1; i < popSize; ++i) {
        population[i] = baseTour;
        std::shuffle(population[i].begin(), population[i].end(), rng);
    }

    std::vector<int> bestTourGlobal = population[0];
    double bestCostGlobal = calculateTourCost(bestTourGlobal, matrix);

    // Loop de Evolução
    for (int gen = 0; gen < generations; ++gen) {
        std::vector<std::vector<int>> newPopulation;
        newPopulation.reserve(popSize);

        // Jogando o melhor para a próxima geração
        newPopulation.push_back(bestTourGlobal);

        while (newPopulation.size() < (size_t)popSize) {
            // Seleção
            std::vector<int> p1 = tournamentSelection(population, matrix, rng);
            std::vector<int> p2 = tournamentSelection(population, matrix, rng);

            std::vector<int> child;
            // Cruzamento (Edge Recombination Crossover)
            if (probDist(rng) <= crossoverRate) {
                child = edgeRecombinationCrossover(p1, p2, rng);
            } 
            else {
                child = p1;
            }

            // Mutação (Inversão)
            mutateInversion(child, mutationRate, rng);

            // Busca local aleatória
            if (probDist(rng) <= localSearchRate) {
                child = applyLocalSearch(child, matrix, rng);
            }

            newPopulation.push_back(child);
        }

        population = newPopulation;

        // Atualiza o melhor global
        for (const auto& ind : population) {
            double cost = calculateTourCost(ind, matrix);
            if (cost < bestCostGlobal) {
                bestCostGlobal = cost;
                bestTourGlobal = ind;
            }
        }
    }

    return {bestCostGlobal, bestTourGlobal};
}

int main() {
    std::string folderPath = "./dados/tabelas";

    std::cout << "=== Buscando arquivos CSV na pasta '" << folderPath << "' ===" << std::endl;

    DIR* dir = opendir(folderPath.c_str());
    if (dir == nullptr) {
        std::cerr << "Erro: A pasta '" << folderPath << "' nao existe ou nao pode ser aberta." << std::endl;
        return 1;
    }

    std::vector<Instance> instances;
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;

        if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".csv") {
            std::string fullPath = folderPath + "/" + filename;
            Instance inst = parseCsvFile(fullPath, filename);
            if (inst.n >= 6) {
                instances.push_back(inst);
            } 
            else {
                std::cerr << "[Aviso] Arquivo " << filename << " ignorado." << std::endl;
            }
        }
    }
    closedir(dir);

    if (instances.empty()) {
        std::cerr << "Nenhum arquivo .csv válido encontrado." << std::endl;
        return 1;
    }

    std::sort(instances.begin(), instances.end(), [](const Instance& a, const Instance& b) {
        return a.name < b.name;
    });

    std::ofstream txtOut("./resultados/resultados_questao4B.txt");
    std::string headerStr = "=== RESUMO DOS RESULTADOS (ALGORITMO MEMÉTICO v2 - Farthest Insertion + ERX + Inversao) ===";

    std::cout << headerStr << "\n" << std::endl;
    if (txtOut.is_open()) txtOut << headerStr << "\n\n";

    // Hiperparâmetros do Algoritmo Memético
    int POP_SIZE = 20;
    int GENERATIONS = 50;
    double CROSSOVER_RATE = 0.85;
    double MUTATION_RATE = 0.10;
    double LOCAL_SEARCH_RATE = 0.30;
    int ITERATIONS = 20;

    for (const auto& inst : instances) {
        std::stringstream ss;
        ss << "========================================================\n";
        ss << "Instância Arquivo: " << inst.name << " (Tamanho N = " << inst.n << " Cidades)\n";
        ss << "========================================================\n";

        double minCost = std::numeric_limits<double>::max();
        double sumCost = 0.0;
        double totalDurationMs = 0.0;
        std::vector<int> absoluteBestTour;

        for (int run = 0; run < ITERATIONS; ++run) {
            auto startClock = std::chrono::high_resolution_clock::now();

            auto [runBestCost, runBestTour] = runMemeticAlgorithm(inst.matrix, POP_SIZE, GENERATIONS,
                                                                    CROSSOVER_RATE, MUTATION_RATE,
                                                                    LOCAL_SEARCH_RATE);

            auto endClock = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = endClock - startClock;

            totalDurationMs += duration.count();
            sumCost += runBestCost;

            if (runBestCost < minCost) {
                minCost = runBestCost;
                absoluteBestTour = runBestTour;
            }
        }

        double avgCost = sumCost / ITERATIONS;
        double avgTimeMs = totalDurationMs / ITERATIONS;

        ss << "  -> MENOR VALOR ENCONTRADO (20 iterações): " << std::fixed << std::setprecision(2) << minCost << "\n";
        ss << "  -> VALOR MÉDIO ENCONTRADO:                " << avgCost << "\n";
        ss << "  -> TEMPO MÉDIO DE EXECUÇÃO:               " << avgTimeMs << " ms\n";
        ss << "  -> Melhor Rota: ";

        for (size_t i = 0; i < absoluteBestTour.size(); ++i) {
            ss << absoluteBestTour[i] + 1 << (i == absoluteBestTour.size() - 1 ? "" : " -> ");
        }
        ss << " -> " << absoluteBestTour[0] + 1 << " (Retorno)\n\n";

        std::cout << ss.str();
        if (txtOut.is_open()) txtOut << ss.str();
    }

    if (txtOut.is_open()) {
        txtOut.close();
        std::cout << "Resumo gerado no arquivo 'resultados_questao4B.txt'." << std::endl;
    }

    return 0;
}