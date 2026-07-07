#include <algorithm>
#include <chrono>
#include <cmath>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

struct Instance {
  std::string name;
  std::vector<std::vector<double>> matrix;
  int n;
};

// ============================================================================
// FUNÇÕES DE LEITURA E CÁLCULO BASE
// ============================================================================

Instance parseCsvFile(const std::string &filePath,
                      const std::string &fileName) {
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
    if (!line.empty() && line.back() == '\r')
      line.pop_back();
    if (line.empty())
      continue;

    std::vector<double> row;
    std::string token = "";
    bool in_quotes = false;
    bool valid_row = true;

    for (size_t i = 0; i <= line.size(); ++i) {
      char c = (i < line.size()) ? line[i] : ',';

      if (c == '"') {
        in_quotes = !in_quotes;
      } else if (c == ',' && !in_quotes) {
        if (!token.empty()) {
          try {
            row.push_back(std::stod(token));
          } catch (...) {
            valid_row = false;
            break;
          }
        }
        token = "";
      } else if (c == ',' && in_quotes) {
        token += '.';
      } else {
        if (c != ' ')
          token += c;
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

double calculateTourCost(const std::vector<int> &tour,
                         const std::vector<std::vector<double>> &matrix) {
  double cost = 0.0;
  int n = tour.size();
  for (int i = 0; i < n; ++i) {
    int u = tour[i];
    int v = tour[(i + 1) % n];
    cost += matrix[u][v];
  }
  return cost;
}

// ============================================================================
// HEURÍSTICA CONSTRUTIVA: INSERÇÃO MAIS BARATA (CHEAPEST INSERTION)
// ============================================================================

/**
 * @brief Implementa a heurística determinística da Inserção Mais Barata.
 * Inicia com as duas cidades mais próximas e, iterativamente, insere na
 * rota parcial a cidade não visitada que resulte no menor incremento de custo.
 */
std::vector<int>
cheapestInsertion(const std::vector<std::vector<double>> &matrix) {
  int n = matrix.size();
  if (n == 0)
    return {};
  if (n == 1)
    return {0};

  std::vector<bool> inTour(n, false);
  std::vector<int> tour;
  tour.reserve(n);

  // Passo 1: Iniciar com a cidade 0 e sua vizinha mais próxima
  int startNode = 0;
  int closestNode = -1;
  double minInitialDist = std::numeric_limits<double>::max();

  for (int i = 1; i < n; ++i) {
    if (matrix[startNode][i] < minInitialDist) {
      minInitialDist = matrix[startNode][i];
      closestNode = i;
    }
  }

  tour.push_back(startNode);
  tour.push_back(closestNode);
  inTour[startNode] = true;
  inTour[closestNode] = true;

  // Passo 2: Iterar inserindo a cidade com o menor custo de inserção
  while (tour.size() < (size_t)n) {
    int bestNodeToInsert = -1;
    int bestInsertPos = -1;
    double minInsertionCost = std::numeric_limits<double>::max();

    // Avalia todas as cidades ainda não inseridas
    for (int k = 0; k < n; ++k) {
      if (!inTour[k]) {
        // Testa a inserção da cidade k em todas as posições possíveis da rota
        // parcial (entre u e v)
        for (size_t i = 0; i < tour.size(); ++i) {
          int u = tour[i];
          int v = tour[(i + 1) % tour.size()];

          // Custo de inserção = d(u, k) + d(k, v) - d(u, v)
          double insertionCost = matrix[u][k] + matrix[k][v] - matrix[u][v];

          if (insertionCost < minInsertionCost) {
            minInsertionCost = insertionCost;
            bestNodeToInsert = k;
            bestInsertPos = i + 1; // Posição para inserir logo após u
          }
        }
      }
    }

    // Efetua a inserção da melhor cidade na melhor posição
    tour.insert(tour.begin() + bestInsertPos, bestNodeToInsert);
    inTour[bestNodeToInsert] = true;
  }

  return tour;
}

// ============================================================================
// BUSCA LOCAL DETERMINÍSTICA (2-OPT)
// ============================================================================

std::vector<int>
localSearch2Opt(std::vector<int> tour,
                const std::vector<std::vector<double>> &matrix) {
  int n = tour.size();
  bool improved = true;

  while (improved) {
    improved = false;
    for (int i = 0; i < n - 1; ++i) {
      for (int j = i + 2; j < n; ++j) {
        // Evita desfazer o ciclo inicial/final de forma redundante
        if (i == 0 && j == n - 1)
          continue;

        double currentDist =
            matrix[tour[i]][tour[i + 1]] + matrix[tour[j]][tour[(j + 1) % n]];
        double newDist =
            matrix[tour[i]][tour[j]] + matrix[tour[i + 1]][tour[(j + 1) % n]];

        // Se houver redução de custo, aplica o movimento e reinicia a busca
        if (newDist < currentDist - 1e-9) {
          std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
          improved = true;
        }
      }
    }
  }
  return tour;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
  std::string folderPath = "./dados/tabelas";

  std::cout << "=== Buscando arquivos CSV na pasta '" << folderPath
            << "' ===" << std::endl;

  DIR *dir = opendir(folderPath.c_str());
  if (dir == nullptr) {
    std::cerr << "Erro: A pasta '" << folderPath
              << "' nao existe ou nao pode ser aberta." << std::endl;
    return 1;
  }

  std::vector<Instance> instances;
  struct dirent *entry;
  while ((entry = readdir(dir)) != nullptr) {
    std::string filename = entry->d_name;

    if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".csv") {
      std::string fullPath = folderPath + "/" + filename;
      Instance inst = parseCsvFile(fullPath, filename);
      if (inst.n >= 6) {
        instances.push_back(inst);
      } else {
        std::cerr << "[Aviso] Arquivo " << filename << " ignorado."
                  << std::endl;
      }
    }
  }
  closedir(dir);

  if (instances.empty()) {
    std::cerr << "Nenhum arquivo .csv válido encontrado." << std::endl;
    return 1;
  }

  // Ordenação para consistência na exibição
  std::sort(
      instances.begin(), instances.end(),
      [](const Instance &a, const Instance &b) { return a.name < b.name; });

  std::ofstream txtOut("resultados_questao2.txt");
  std::string headerStr = "=== RESUMO DOS RESULTADOS (INSERÇÃO MAIS BARATA + "
                          "BUSCA LOCAL 2-OPT) ===";

  std::cout << headerStr << "\n" << std::endl;
  if (txtOut.is_open())
    txtOut << headerStr << "\n\n";

  for (const auto &inst : instances) {
    std::stringstream ss;
    ss << "========================================================\n";
    ss << "Instância Arquivo: " << inst.name << " (Tamanho N = " << inst.n
       << " Cidades)\n";
    ss << "========================================================\n";

    // Execução Determinística: Rodar uma única vez!
    auto startClock = std::chrono::high_resolution_clock::now();

    // 1. Constrói a rota inicial pela Inserção Mais Barata
    std::vector<int> tour = cheapestInsertion(inst.matrix);

    // 2. Refina a rota com Busca Local 2-Opt
    tour = localSearch2Opt(tour, inst.matrix);

    auto endClock = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = endClock - startClock;

    double finalCost = calculateTourCost(tour, inst.matrix);

    ss << "  -> VALOR OBTIDO:          " << std::fixed << std::setprecision(2)
       << finalCost << "\n";
    ss << "  -> TEMPO DE EXECUÇÃO:     " << duration.count() << " ms\n";
    ss << "  -> Melhor Rota: ";

    for (size_t i = 0; i < tour.size(); ++i) {
      ss << tour[i] + 1 << (i == tour.size() - 1 ? "" : " -> ");
    }
    ss << " -> " << tour[0] + 1 << " (Retorno)\n\n";

    std::cout << ss.str();
    if (txtOut.is_open())
      txtOut << ss.str();
  }

  if (txtOut.is_open()) {
    txtOut.close();
    std::cout << "Resumo gerado no arquivo 'resultados_questao2.txt'."
              << std::endl;
  }

  return 0;
}
