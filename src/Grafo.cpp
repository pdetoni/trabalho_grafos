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

bool Grafo::eh_completo() const{
    int n = numVertices;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && !existeAresta(i, j)) {
                    return false;
                }
            }
        }
        return true;
}

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

int Grafo::n_conexo()  {
        int n = numVertices;
        bool* visitado = new bool[n](); // Array dinâmico para rastrear vértices visitados
        int componentes = 0;

        for (int i = 0; i < n; ++i) {
            if (!visitado[i]) {
                dfs(i, visitado); // ou dfs(i, visitado);
                componentes++;
            }
        }

        delete[] visitado; // Liberar memória alocada
        return componentes;
    }

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
/*
    int Grafo::get_grau() const {
        int maior_grau = 0;
        
        for(int i = 0; i < numVertices; i++) {
            int grau = get_grau_vertice(i);
            if(grau > maior_grau) {
                maior_grau = grau;
            }
            
        }
        
        return maior_grau;
    }*/
/*
    int Grafo::get_grau_vertice(int v) const {
        int grau = 0;
        int* vizinhos;
        get_vizinhos(v, vizinhos, grau);
        return grau;
    }*/


