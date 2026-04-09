# Variáveis
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
# Lista todos os arquivos .cpp na pasta
SOURCES = $(wildcard *.cpp)
# Gera os nomes dos executáveis (remove o .cpp de cada fonte)
TARGETS = $(SOURCES:.cpp=)

# Alvo que faz tudo para TODOS os arquivos
run_all:
	@for file in $(TARGETS); do \
		echo "--- Compilando $$file.cpp ---"; \
		$(CXX) $(CXXFLAGS) $$file.cpp -o $$file; \
		echo "--- Executando $$file ---"; \
		./$$file; \
		echo "--- Removendo $$file ---"; \
		rm -f $$file; \
		echo ""; \
	done

# Caso queira rodar apenas um arquivo específico (ex: make single FILE=meu_arquivo)
single:
	@$(CXX) $(CXXFLAGS) $(FILE).cpp -o $(FILE)
	@./$(FILE)
	@rm -f $(FILE)

# Limpeza geral (caso algum binário tenha sobrado por erro)
clean:
	rm -f $(TARGETS)