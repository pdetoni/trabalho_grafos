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
    numVertices++;
    inicializa_estrutura(); // Reconfigura a estrutura para o novo tamanho
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
    numVertices--;
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
double Grafo::menor_distancia(int u, int v) {
    return menor_distancia_dijkstra(u, v);
}

// Função auxiliar para calcular a menor distância usando Dijkstra
double Grafo::menor_distancia_dijkstra(int u, int v) {
    double* dist = new double[numVertices];
    bool* visitado = new bool[numVertices]();
    for (int i = 0; i < numVertices; ++i) {
        dist[i] = std::numeric_limits<double>::max();
    }

    dist[u] = 0;

    while (true) {
        int atual = -1;
        double menorDistancia = std::numeric_limits<double>::max();

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
            double pesoAresta = 0;
            if (arestasPonderadas) {
                pesoAresta = 1; // Substitua por get_peso_aresta(atual, vizinho) se existir
            }
            double novaDistancia = dist[atual] + pesoAresta;
            if (novaDistancia < dist[vizinho]) {
                dist[vizinho] = novaDistancia;
            }
        }

        delete[] vizinhos;
    }

    double resultado = dist[v];
    delete[] dist;
    delete[] visitado;
    return resultado;
}