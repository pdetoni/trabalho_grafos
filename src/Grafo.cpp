#include "Grafo.h"

// Construtor
Grafo::Grafo(int n, bool dir, bool vp, bool ap)
    : numVertices(n), direcionado(dir), verticesPonderados(vp), arestasPonderadas(ap) {}

// Destrutor virtual
Grafo::~Grafo() {}

// Retorna o número de vértices (ordem do grafo)
int Grafo::get_ordem() {
    return numVertices;
}

// Verifica se o grafo é direcionado
bool Grafo::eh_direcionado() {
    return direcionado;
}

// Verifica se os vértices são ponderados
bool Grafo::vertice_ponderado() {
    return verticesPonderados;
}

// Verifica se as arestas são ponderadas
bool Grafo::aresta_ponderada() {
    return arestasPonderadas;
}

// Verifica se o grafo é completo
bool Grafo::eh_completo() const {
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (i != j && !existeAresta(i, j)) {
                return false;
            }
        }
    }
    return true;
}

// Carrega o grafo de um arquivo
void Grafo::carrega_grafo(const std::string& arquivo) {
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << arquivo << std::endl;
        return;
    }

    // Lê o cabeçalho
    int n, dir, vp, ap;
    file >> n >> dir >> vp >> ap;

    // Atualiza os atributos
    numVertices = n;
    direcionado = (dir == 1);
    verticesPonderados = (vp == 1);
    arestasPonderadas = (ap == 1);

    // Inicializa a estrutura específica da classe filha
    inicializa_estrutura();

    // Lê os pesos dos vértices (se aplicável)
    if (verticesPonderados) {
        for (int i = 0; i < numVertices; ++i) {
            int peso;
            file >> peso;
        }
    }

    // Lê as arestas
    int u, v, peso;
    while (file >> u >> v) {
        if (arestasPonderadas) {
            file >> peso;
        } else {
            peso = 1;
        }

        // Ajusta os índices para base 0
        u--;
        v--;

        // Adiciona a aresta
        adiciona_aresta(u, v, peso);

        // Se não for direcionado, adiciona a aresta inversa
        if (!direcionado) {
            adiciona_aresta(v, u, peso);
        }
    }

    file.close();
}

// Retorna o número de componentes conexos
int Grafo::n_conexo() {
    bool* visitado = new bool[numVertices]();
    int componentes = 0;

    for (int i = 0; i < numVertices; ++i) {
        if (!visitado[i]) {
            dfs(i, visitado);
            componentes++;
        }
    }

    delete[] visitado;
    return componentes;
}

// Função auxiliar para DFS
void Grafo::dfs(int v, bool* visitado) {
    visitado[v] = true;

    int* vizinhos;
    int tamanho;
    get_vizinhos(v, vizinhos, tamanho);

    for (int i = 0; i < tamanho; ++i) {
        int vizinho = vizinhos[i];
        if (!visitado[vizinho]) {
            dfs(vizinho, visitado);
        }
    }

    delete[] vizinhos;
}

// Retorna o grau máximo do grafo
int Grafo::get_grau() {
    int grauMax = 0;
    if (eh_direcionado()) {
        for (int i = 0; i < numVertices; i++) {
            int grauSaida = 0;
            int grauEntrada = 0;
            for (int j = 0; j < numVertices; j++) {
                if (existeAresta(i, j)) grauSaida++;
                if (existeAresta(j, i)) grauEntrada++;
            }
            int grauTotal = grauSaida + grauEntrada;
            if (grauTotal > grauMax) grauMax = grauTotal;
        }
    } else {
        for (int i = 0; i < numVertices; i++) {
            int grau = 0;
            for (int j = 0; j < numVertices; j++) {
                if (existeAresta(i, j)) grau++;
            }
            if (grau > grauMax) grauMax = grau;
        }
    }
    return grauMax;
}

// Adiciona um novo nó ao grafo
void Grafo::novo_no() {
    adiciona_no();
    
}


// Adiciona uma nova aresta ao grafo
void Grafo::nova_aresta(int origem, int destino, int peso) {
    adiciona_aresta(origem, destino, peso);
}

// Remove um nó do grafo
void Grafo::deleta_no(int id) {
    if (id < 0 || id >= numVertices) {
        std::cerr << "Erro: ID do nó inválido." << std::endl;
        return;
    }

    // Remove todas as arestas associadas ao nó
    for (int i = 0; i < numVertices; ++i) {
        deleta_aresta(i, id);
        deleta_aresta(id, i);
    }

    // Reorganiza os IDs dos nós
    remove_no(id);
}

// Remove uma aresta do grafo
void Grafo::deleta_aresta(int origem, int destino) {
    if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices) {
        std::cerr << "Erro: IDs dos nós inválidos." << std::endl;
        return;
    }

    // Remove a aresta
    adiciona_aresta(origem, destino, 0); // Define o peso como 0 (sem aresta)
}

// Calcula a menor distância entre dois nós
int Grafo::menor_distancia(int u, int v) {
    return menor_distancia_dijkstra(u, v);
}

// Função auxiliar para calcular a menor distância usando Dijkstra
int Grafo::menor_distancia_dijkstra(int u, int v) {
    int* dist = new int[numVertices];
    bool* visitado = new bool[numVertices]();
    for (int i = 0; i < numVertices; ++i) {
        dist[i] = std::numeric_limits<int>::max();
    }

    dist[u] = 0;

    while (true) {
        int atual = -1;
        int menorDistancia = std::numeric_limits<int>::max();

        // Encontra o nó não visitado com a menor distância
        for (int i = 0; i < numVertices; ++i) {
            if (!visitado[i] && dist[i] < menorDistancia) {
                atual = i;
                menorDistancia = dist[i];
            }
        }

        if (atual == -1 || atual == v) {
            break; // Todos os nós foram visitados ou chegamos ao destino
        }

        visitado[atual] = true;
        int* vizinhos;
        int tamanho;
        get_vizinhos(atual, vizinhos, tamanho);

        for (int i = 0; i < tamanho; ++i) {
            int vizinho = vizinhos[i];
            int pesoAresta = 1;
            if (arestasPonderadas) {
                get_pesoAresta(atual, vizinho, pesoAresta);
                
            }
            int novaDistancia = dist[atual] + pesoAresta;
            if (novaDistancia < dist[vizinho]) {
                dist[vizinho] = novaDistancia;
                
            } 
        }

        delete[] vizinhos;
    }

    int resultado = dist[v];
    delete[] dist;
    delete[] visitado;
    return resultado;
}

void Grafo::caixeiro_viajante_guloso(int vertice_inicial, int*& caminho, int& tamanho_caminho) {
    bool* visitado = new bool[numVertices]();  // Inicializa com false
    int* caminho_temp = new int[numVertices + 1];  // +1 para o possível retorno ao início
    
    int atual = vertice_inicial;
    caminho_temp[0] = atual;
    visitado[atual] = true;
    int contador = 1;
    
    // Enquanto não visitamos todos os vértices
    for (int i = 1; i < numVertices; i++) {
        int melhor_vizinho = -1;
        int menor_peso = std::numeric_limits<int>::max();
        
        // Pega todos os vizinhos do vértice atual
        int* vizinhos;
        int num_vizinhos;
        get_vizinhos(atual, vizinhos, num_vizinhos);
        
        // Encontra o vizinho não visitado com menor peso
        for (int j = 0; j < num_vizinhos; j++) {
            int vizinho = vizinhos[j];
            if (!visitado[vizinho]) {
                int peso = 1;
                if (arestasPonderadas) {
                    get_pesoAresta(atual, vizinho, peso);
                }
                
                // Verifica se o vizinho permite retornar ao início
                if (peso < menor_peso && (existeAresta(vizinho, vertice_inicial) || i == numVertices - 1)) {
                    menor_peso = peso;
                    melhor_vizinho = vizinho;
                }
            }
        }
        
        // Libera a memória dos vizinhos
        delete[] vizinhos;
        
        // Se não encontrou mais vizinhos, vamos verificar se podemos voltar ao início
        if (melhor_vizinho == -1) {
            // Se não há conexão direta com todos os vértices, tenta encontrar qualquer não visitado
            for (int v = 0; v < numVertices; v++) {
                if (!visitado[v] && existeAresta(atual, v)) {
                    melhor_vizinho = v;
                    break;
                }
            }
            
            // Se ainda não encontrou, significa que visitamos todos os vértices acessíveis
            if (melhor_vizinho == -1) {
                break;
            }
        }
        
        // Adiciona o melhor vizinho ao caminho
        atual = melhor_vizinho;
        caminho_temp[contador++] = atual;
        visitado[atual] = true;
    }
    
    // Tenta completar o ciclo voltando ao vértice inicial
    if (existeAresta(atual, vertice_inicial)) {
        caminho_temp[contador++] = vertice_inicial;
    } else {
        // Se não há aresta direta de volta ao início, encontra o caminho mais curto para voltar
        int menor_peso_volta = std::numeric_limits<int>::max();
        int melhor_vizinho_volta = -1;
        
        // Procura o vértice mais próximo do vértice inicial que tenha uma aresta para ele
        for (int v = 0; v < numVertices; v++) {
            if (v != atual && existeAresta(atual, v) && existeAresta(v, vertice_inicial)) {
                int peso_atual_v = 1;
                int peso_v_inicial = 1;
                if (arestasPonderadas) {
                    get_pesoAresta(atual, v, peso_atual_v);
                    get_pesoAresta(v, vertice_inicial, peso_v_inicial);
                }
                int peso_total = peso_atual_v + peso_v_inicial;
                if (peso_total < menor_peso_volta) {
                    menor_peso_volta = peso_total;
                    melhor_vizinho_volta = v;
                }
            }
        }
        
        if (melhor_vizinho_volta != -1) {
            // Adiciona o vértice intermediário e o vértice inicial ao caminho
            caminho_temp[contador++] = melhor_vizinho_volta;
            caminho_temp[contador++] = vertice_inicial;
        } else {
            // Se não encontrou um caminho de volta, simplesmente adiciona o vértice inicial
            caminho_temp[contador++] = vertice_inicial;
        }
    }
    
    // Copia o caminho para o array de resultado
    tamanho_caminho = contador;
    caminho = new int[tamanho_caminho];
    for (int i = 0; i < tamanho_caminho; i++) {
        caminho[i] = caminho_temp[i];
    }
    
    // Libera a memória temporária
    delete[] caminho_temp;
    delete[] visitado;
}