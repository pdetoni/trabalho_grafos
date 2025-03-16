import argparse, random, os
try:
    from tqdm import tqdm
    HAS_TQDM = True
except ImportError:
    HAS_TQDM = False

def calcular_distancia(grafo, origem, destino):
    """
    Função para calcular a distância real entre dois nós usando Dijkstra.
    Assume que o grafo é representado como um dicionário de adjacência.
    """
    distancias = {no: float('inf') for no in grafo}
    distancias[origem] = 0
    visitados = set()

    while True:
        # Encontra o nó não visitado com a menor distância
        no_atual = None
        menor_distancia = float('inf')
        for no in grafo:
            if no not in visitados and distancias[no] < menor_distancia:
                no_atual = no
                menor_distancia = distancias[no]

        if no_atual is None or no_atual == destino:
            break

        visitados.add(no_atual)

        # Atualiza as distâncias dos vizinhos
        for vizinho, peso in grafo[no_atual].items():
            if distancias[no_atual] + peso < distancias[vizinho]:
                distancias[vizinho] = distancias[no_atual] + peso

    return distancias[destino]

def gerar_instancia_tsp(num_nos, ponderado_arestas=False):
    if num_nos < 3:
        raise ValueError("O número de nós deve ser pelo menos 3 para formar um ciclo.")
    
    print("Iniciando a geração da instância do TSP...")

    # Função para criar um ciclo inicial que conecta todos os nós
    def criar_ciclo_inicial():
        print("Criando ciclo inicial...")
        ciclo = list(range(1, num_nos + 1))
        random.shuffle(ciclo)
        arestas = []
        iteravel = range(num_nos)
        if HAS_TQDM:
            iteravel = tqdm(iteravel, desc="Ciclo inicial")
        for i in iteravel:
            origem = ciclo[i]
            destino = ciclo[(i + 1) % num_nos]
            peso = random.randint(1, 20) if ponderado_arestas else 1
            arestas.append((origem, destino, peso))
        return arestas

    # Função para verificar se uma aresta já existe
    def aresta_existe(origem, destino, arestas):
        return (origem, destino) in [(a[0], a[1]) for a in arestas] or \
                (destino, origem) in [(a[0], a[1]) for a in arestas]
    
    arestas = criar_ciclo_inicial()

    # Construir o grafo como um dicionário de adjacência para calcular distâncias
    grafo = {no: {} for no in range(1, num_nos + 1)}
    for aresta in arestas:
        origem, destino, peso = aresta
        grafo[origem][destino] = peso
        if not ponderado_arestas:
            grafo[destino][origem] = peso  # Se não for ponderado, assume-se que é bidirecional

    print("Adicionando arestas extras...")
    max_arestas_por_no = max(1, min(num_nos // 15, 5))  # Número máximo de arestas extras por nó. (mínimo 1, máximo 5)
    max_distancia = max(2, min(num_nos // 12, 7))  # Distância máxima entre nós para adicionar arestas. (mínimo 2, máximo 7)
    
    print(f"Número máximo de arestas extras por nó: {max_arestas_por_no}")
    print(f"Distância máxima para adicionar arestas extras: {max_distancia}")

    ### Adicionar arestas extras
    # Adiciona um número aleatório de arestas extras para cada nó dentro da distância máxima
    iteravel = range(1, num_nos + 1)
    if HAS_TQDM:
        iteravel = tqdm(iteravel, desc="Adicionando arestas extras")
    for no in iteravel:
        num_arestas_extras = random.randint(1, max_arestas_por_no)  # Pelo menos 1 aresta extra
        tentativas = 0
        while num_arestas_extras > 0 and tentativas < 15:
            # Escolher um nó destino aleatório
            destino = random.randint(1, num_nos)
            if destino != no and not aresta_existe(no, destino, arestas):
                # Calcular a distância real entre os nós
                distancia = calcular_distancia(grafo, no, destino)
                if distancia <= max_distancia:
                    peso = random.randint(1, 10) if ponderado_arestas else 1
                    arestas.append((no, destino, peso))
                    grafo[no][destino] = peso  # Atualiza o grafo com a nova aresta
                    if not ponderado_arestas:
                        grafo[destino][no] = peso  # Se não for ponderado, assume-se que é bidirecional
                    num_arestas_extras -= 1
                else:
                    # Se a distância for maior que o máximo, relaxa a restrição e adiciona a aresta
                    peso = random.randint(1, 10) if ponderado_arestas else 1
                    arestas.append((no, destino, peso))
                    grafo[no][destino] = peso
                    if not ponderado_arestas:
                        grafo[destino][no] = peso
                    num_arestas_extras -= 1
            tentativas += 1

    # Gerar o arquivo de saída
    print("Salvando a instância em arquivo...")
    base_nome = f"instancia_tsp_{num_nos}_nos"
    sufixo = 0
    nome_arquivo = f"{base_nome}.txt"
    
    # Verificar se o arquivo já existe e incrementar o sufixo
    while os.path.exists(nome_arquivo):
        sufixo += 1
        nome_arquivo = f"{base_nome}_{sufixo}.txt"

    with open(nome_arquivo, "w") as f:
        # Escrever a primeira linha
        f.write(f"{num_nos} 0 0 {int(ponderado_arestas)}\n")

        # Escrever as arestas
        iteravel = arestas
        if HAS_TQDM:
            iteravel = tqdm(iteravel, desc="Salvando arestas")
        for aresta in iteravel:
            f.write(f"{aresta[0]} {aresta[1]} {aresta[2]}\n")

    print(f"Instância gerada com {num_nos} nós e {len(arestas)} arestas.")
    print(f"Ciclo inicial criado e arestas extras adicionadas conforme as regras.")

if __name__ == "__main__":
    # EXEMPLO: python3 gen_tsp.py 5000 --ponderado_arestas
    parser = argparse.ArgumentParser(description="Gerador de instâncias do TSP.")
    parser.add_argument("num_nos", type=int, help="Número de nós no grafo.")
    parser.add_argument("--ponderado_arestas", action="store_true", help="Define se as arestas são ponderadas.")
    
    args = parser.parse_args()

    gerar_instancia_tsp(
        num_nos=args.num_nos,
        ponderado_arestas=args.ponderado_arestas
    )