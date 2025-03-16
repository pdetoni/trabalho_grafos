import random
import argparse

def gerar_instancia_tsp(num_nos, ponderado_arestas=False):
    if num_nos < 3:
        raise ValueError("O número de nós deve ser pelo menos 3 para formar um ciclo.")

    # Função para criar um ciclo inicial que conecta todos os nós
    def criar_ciclo_inicial():
        ciclo = list(range(1, num_nos + 1))
        random.shuffle(ciclo)  # Embaralhar para evitar ciclos óbvios
        arestas = []
        for i in range(num_nos):
            origem = ciclo[i]
            destino = ciclo[(i + 1) % num_nos]
            peso = random.randint(1, 20) if ponderado_arestas else 1
            arestas.append((origem, destino, peso))
        return arestas

    # Função para verificar se uma aresta já existe
    def aresta_existe(origem, destino, arestas):
        return (origem, destino) in [(a[0], a[1]) for a in arestas] or \
                (destino, origem) in [(a[0], a[1]) for a in arestas]

    # Criar o ciclo inicial
    arestas = criar_ciclo_inicial()

    # Adicionar arestas extras
    max_arestas_por_no = min(num_nos // 15, 5)  # Número máximo de arestas extras por nó
    max_distancia = min(num_nos // 12, 7)  # Distância máxima entre nós para adicionar arestas

    for no in range(1, num_nos + 1):
        num_arestas_extras = random.randint(0, max_arestas_por_no)  # Número aleatório de arestas extras
        tentativas = 0
        while num_arestas_extras > 0 and tentativas < 15:
            # Escolher um nó destino dentro da distância máxima
            destino = random.randint(max(1, no - max_distancia), min(num_nos, no + max_distancia))
            if destino != no and not aresta_existe(no, destino, arestas):
                peso = random.randint(1, 10) if ponderado_arestas else 1
                arestas.append((no, destino, peso))
                num_arestas_extras -= 1
            tentativas += 1

    # Gerar o arquivo de saída
    with open(f"instancia_tsp_{num_nos}_nos.txt", "w") as f:
        # Escrever a primeira linha
        f.write(f"{num_nos} 0 0 {int(ponderado_arestas)}\n")

        # Escrever as arestas
        for aresta in arestas:
            f.write(f"{aresta[0]} {aresta[1]} {aresta[2]}\n")

    print(f"Instância gerada com {num_nos} nós e {len(arestas)} arestas.")
    print(f"Ciclo inicial criado e arestas extras adicionadas conforme as regras.")

# Exemplo de uso recebendo o número de nós como argumento
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Gerador de instâncias do TSP.")
    parser.add_argument("num_nos", type=int, help="Número de nós no grafo.")
    parser.add_argument("--ponderado_arestas", action="store_true", help="Define se as arestas são ponderadas.")
    
    args = parser.parse_args()

    gerar_instancia_tsp(
        num_nos=args.num_nos,
        ponderado_arestas=args.ponderado_arestas
    )