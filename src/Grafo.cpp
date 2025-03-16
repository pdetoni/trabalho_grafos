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

void Grafo::ordenarCandidatos(int* pesos, int* destinos, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (pesos[j] > pesos[j + 1]) {
                int tempPeso = pesos[j];
                pesos[j] = pesos[j + 1];
                pesos[j + 1] = tempPeso;

                int tempDestino = destinos[j];
                destinos[j] = destinos[j + 1];
                destinos[j + 1] = tempDestino;
            }
        }
    }
}



int* Grafo::tspGulosoRandomizado(const Grafo* grafo, int k, int& tamanhoCiclo) {
    int n = get_ordem();
    int* ciclo = new int[n + 1];
    bool* visitado = new bool[n]();
    srand(time(nullptr));

    // Passo 1: Escolher vértice inicial aleatoriamente
    int inicio = rand() % n;
    ciclo[0] = inicio;
    visitado[inicio] = true;
    tamanhoCiclo = 1;

    // Passo 2: Construir o ciclo
    while (tamanhoCiclo < n) {
        int atual = ciclo[tamanhoCiclo - 1];
        int* vizinhos = new int[n];
        int numVizinhos = 0;
        get_vizinhos(atual, vizinhos, numVizinhos);

        if (numVizinhos == 0) {
            delete[] vizinhos;
            break;
        }

        int* candidatosPesos = new int[numVizinhos];
        int* candidatosDestinos = new int[numVizinhos];
        int numCandidatos = 0;

        // Coletar vizinhos não visitados
        for (int i = 0; i < numVizinhos; i++) {
            if (!visitado[vizinhos[i]]) {
                int peso = 1;
                get_pesoAresta(atual, vizinhos[i], peso);
                if (peso > 0) {
                    candidatosPesos[numCandidatos] = peso;
                    candidatosDestinos[numCandidatos] = vizinhos[i];
                    numCandidatos++;
                }
            }
        }

        delete[] vizinhos;

        if (numCandidatos == 0) {
            delete[] candidatosPesos;
            delete[] candidatosDestinos;
            break;
        }

        // Ordenar candidatos por peso
        ordenarCandidatos(candidatosPesos, candidatosDestinos, numCandidatos);

        // Selecionar os k menores
        int limite = k;
        if (numCandidatos < k) {
            limite = numCandidatos;
        }

        double somaInversos = 0.0;
        for (int i = 0; i < limite; i++) {
            somaInversos += 1.0 / candidatosPesos[i];
        }

        // Escolher aleatoriamente com probabilidade inversa ao peso
        double r = (double)rand() / RAND_MAX * somaInversos;
        int escolhido = 0;
        double acumulado = 0.0;
        for (int i = 0; i < limite; i++) {
            acumulado += 1.0 / candidatosPesos[i];
            if (r <= acumulado) {
                escolhido = i;
                break;
            }
        }

        int proximo = candidatosDestinos[escolhido];
        ciclo[tamanhoCiclo++] = proximo;
        visitado[proximo] = true;

        delete[] candidatosPesos;
        delete[] candidatosDestinos;
    }

    // Passo 3: Fechar o ciclo
    ciclo[tamanhoCiclo++] = inicio;
    delete[] visitado;
    return ciclo;
}

int Grafo::calcularCustoCiclo(const Grafo* grafo, const int* ciclo, int tamanho) {
    int custo = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        int peso = 0;
        get_pesoAresta(ciclo[i], ciclo[i + 1], peso);
        custo += peso;
    }
    return custo;
}




