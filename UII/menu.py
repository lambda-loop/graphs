from InquirerPy import inquirer
import subprocess
import os


def limpar_tela():
    os.system("cls" if os.name == "nt" else "clear")


def main():
    while True:
        limpar_tela()

        escolha = inquirer.select(
            message="Projeto 1: Infraestrutura de Fibra Óptica\nSelecione o Algoritmo:",
            choices=[
                "1. Algoritmo de Prim (Não-Direcionado)",
                "2. Algoritmo de Kruskal (Não-Direcionado)",
                "3. Algoritmo de Boruvka (Não-Direcionado)",
                "4. Algoritmo de Chu-Liu/Edmonds (Direcionado)",
                "5. Sair",
            ],
        ).execute()

        if "5" in escolha:
            print("\nEncerrando o sistema...")
            break

        print(f"\n--- Executando: {escolha.split('.')[1].strip()} ---\n")

        try:
            if "1" in escolha:
                subprocess.run(["./prim"])
            elif "2" in escolha:
                subprocess.run(["./kruskal"])
            elif "3" in escolha:
                subprocess.run(["./boruvka"])
            elif "4" in escolha:
                subprocess.run(["./chuliu_edmonds"])
        except FileNotFoundError:
            print("\n[ERRO] Executável não encontrado.")
            print(
                "Certifique-se de compilar os arquivos .cpp correspondentes antes de rodar o menu."
            )

        input("\nPressione Enter para voltar ao menu principal...")


if __name__ == "__main__":
    main()
