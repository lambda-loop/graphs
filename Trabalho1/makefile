# Variáveis
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Pastas
SRC_DIR = ./src
OUT_DIR = ./saidas

# Busca os arquivos dentro de src (ex: ./src/questao21.cpp)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Extrai apenas o nome do arquivo para usar como executável temporário
# Ex: ./src/questao21.cpp vira questao21
TARGETS = $(patsubst $(SRC_DIR)/%.cpp, %, $(SOURCES))

# Alvo que faz tudo para TODOS os arquivos
run_all:
	@mkdir -p $(OUT_DIR)
	@for file in $(TARGETS); do \
		echo "--- Compilando $(SRC_DIR)/$$file.cpp ---"; \
		$(CXX) $(CXXFLAGS) $(SRC_DIR)/$$file.cpp -o $$file; \
		echo "--- Executando $$file e salvando em $(OUT_DIR)/$$file.txt ---"; \
		./$$file > $(OUT_DIR)/$$file.txt 2>&1; \
		echo "--- Removendo executável $$file ---"; \
		rm -f $$file; \
		echo ""; \
	done

# Caso queira rodar apenas um arquivo específico
# Uso: make single FILE=questao21
single:
	@mkdir -p $(OUT_DIR)
	@echo "--- Compilando $(SRC_DIR)/$(FILE).cpp ---"
	@$(CXX) $(CXXFLAGS) $(SRC_DIR)/$(FILE).cpp -o $(FILE)
	@echo "--- Executando e salvando em $(OUT_DIR)/$(FILE).txt ---"
	@./$(FILE) > $(OUT_DIR)/$(FILE).txt 2>&1
	@rm -f $(FILE)

# Limpeza geral
clean:
	rm -f $(TARGETS)
	rm -rf $(OUT_DIR)
