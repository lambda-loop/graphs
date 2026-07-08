OUT_DIR := out

SRCS := $(wildcard *.cpp)

EXECS := $(patsubst %.cpp,$(OUT_DIR)/%,$(SRCS))

all: $(EXECS) run

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/%: %.cpp | $(OUT_DIR)
	g++ $< -o $@

run: $(EXECS)
	@echo "=== Executando os programas de dentro da pasta $(OUT_DIR) ==="
	@for exec in $(EXECS); do \
		echo "-> Rodando $$exec:"; \
		./$$exec; \
		echo "-----------------------------"; \
	done

clean:
	rm -rf $(OUT_DIR)

.PHONY: all run clean