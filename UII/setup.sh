
echo "[Iniciando setup do projeto]"
echo "----------------------------"

echo "[Criando python env]:"

python -m venv venv
source venv/bin/activate

echo "[Instalando InquirerPy]:"

pip install InquirerPy

echo "[Compilando algoritmos]:"

# zig build-exe prim.zig #configurar o setup do prim aqui
g++ -std=c++20 prim.cpp -o prim
g++ -std=c++20 kruskal.cpp -o kruskal
g++ -std=c++20 boruvka.cpp -o boruvka
g++ chuliu_edmonds.cpp -o chuliu_edmonds

echo "Para rodar o projeto: python menu.py"


