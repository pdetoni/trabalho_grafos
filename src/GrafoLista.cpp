#include "GrafoLista.h"

GrafoLista::GrafoLista(int n, bool dir, bool vp, bool ap)
    : Grafo(n, dir, vp, ap) {
    vertices = new Vertice[n];
    for (int i = 0; i < n; ++i) {
        vertices[i].id = i;
        vertices[i].arestas = nullptr;
    }
}

GrafoLista::~GrafoLista() {
    for (int i = 0; i < numVertices; ++i) {
        Aresta* aresta = vertices[i].arestas;
        while (aresta) {
            Aresta* temp = aresta;
            aresta = aresta->proxima;
            delete temp;
        }
    }
    delete[] vertices;
}
/*
void GrafoLista::carrega_grafo(const std::string& arquivo) {
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

    // Lê os pesos dos vértices (se aplicável)
    if (verticesPonderados) {
        for (int i = 0; i < numVertices; ++i) {
            file >> vertices[i].peso;
        }
    }

    // Lê as arestas
    int u, v, peso;
    while (file >> u >> v) { // Lê u e v primeiro
        if (arestasPonderadas) {
            file >> peso; // Lê o peso apenas se necessário
        } else {
            peso = 1; // Valor padrão
        }

        // Ajusta os índices para base 0
        u--;
        v--;

        // Adiciona a aresta (u -> v)
        Aresta* novaAresta = new Aresta{v, peso, vertices[u].arestas};
        vertices[u].arestas = novaAresta;

        // Se não for direcionado, adiciona a aresta inversa (v -> u)
        if (!direcionado) {
            Aresta* arestaInversa = new Aresta{u, peso, vertices[v].arestas};
            vertices[v].arestas = arestaInversa;
        }
    }

    file.close();
}
*/
void GrafoLista::inicializa_estrutura() {
    vertices = new Vertice[numVertices];
    for (int i = 0; i < numVertices; i++) {
        vertices[i].arestas = nullptr;
        vertices[i].peso = 0;
    }
}

void GrafoLista::adiciona_aresta(int origem, int destino, int peso) {
    Aresta* novaAresta = new Aresta{destino, peso, vertices[origem].arestas};
    vertices[origem].arestas = novaAresta;
}

void GrafoLista::get_vizinhos(int v, int*& vizinhos, int& tamanho) const {
    tamanho = 0;
    Aresta* aresta = vertices[v].arestas;
    while (aresta) {
        tamanho++;
        aresta = aresta->proxima;
    }

    vizinhos = new int[tamanho];
    int index = 0;
    aresta = vertices[v].arestas;
    while (aresta) {
        vizinhos[index++] = aresta->destino;
        aresta = aresta->proxima;
    }
}

void GrafoLista::get_arestas(int*& arestas, int& tamanho) {
    tamanho = 0;
    for (int i = 0; i < numVertices; ++i) {
        Aresta* aresta = vertices[i].arestas;
        while (aresta) {
            tamanho += 2; // Cada aresta é representada por dois valores (u, v)
            aresta = aresta->proxima;
        }
    }

    arestas = new int[tamanho];
    int index = 0;
    for (int i = 0; i < numVertices; ++i) {
        Aresta* aresta = vertices[i].arestas;
        while (aresta) {
            arestas[index++] = i;
            arestas[index++] = aresta->destino;
            aresta = aresta->proxima;
        }
    }
}
/*
int GrafoLista::get_grau() {
    int grauMax = 0;

    if (eh_direcionado()) {
        // Para grafos direcionados, o grau é a soma das arestas de entrada e saída
        for (int i = 0; i < numVertices; ++i) {
            // Grau de saída (arestas que partem do vértice i)
            int grauSaida = 0;
            Aresta* arestaSaida = vertices[i].arestas;
            while (arestaSaida) {
                grauSaida++;
                arestaSaida = arestaSaida->proxima;
            }

            // Grau de entrada (arestas que chegam ao vértice i)
            int grauEntrada = 0;
            for (int j = 0; j < numVertices; ++j) {
                Aresta* arestaEntrada = vertices[j].arestas;
                while (arestaEntrada) {
                    if (arestaEntrada->destino == i) {
                        grauEntrada++;
                    }
                    arestaEntrada = arestaEntrada->proxima;
                }
            }

            int grauTotal = grauSaida + grauEntrada;
            if (grauTotal > grauMax) {
                grauMax = grauTotal;
            }
        }
    } else {
        // Para grafos não direcionados, o grau é o número de arestas
        for (int i = 0; i < numVertices; ++i) {
            int grau = 0;
            Aresta* aresta = vertices[i].arestas;
            while (aresta) {
                grau++;
                aresta = aresta->proxima;
            }
            if (grau > grauMax) {
                grauMax = grau;
            }
        }
    }

    return grauMax;
}
*/
/*
int GrafoLista::get_grau_vertice(int v) const {
    int grau;    
    int* vizinhos;
    get_vizinhos(v, vizinhos, grau);
    return grau;
}*/

bool GrafoLista::existeAresta(int u, int v) const {
    Aresta* aresta = vertices[u].arestas;
    while (aresta) {
        if (aresta->destino == v) {
            return true;
        }
        aresta = aresta->proxima;
    }
    return false;
}
