#!/bin/bash

echo "[Iniciando setup do projeto]"
echo "----------------------------"

echo "[Criando python env]:"

python -m venv venv
source venv/bin/activate

echo "[Instalando InquirerPy]:"

pip install InquirerPy

echo "[Compilando algoritmos]:"

zig build-exe prim.zig #configurar o setup do prim aqui
g++ kruskal.cpp -o kruskal
g++ boruvka.cpp -o boruvka
g++ chuliu_edmonds.cpp -o chuliu_edmonds

echo "Para rodar o projeto: python menu.py"


