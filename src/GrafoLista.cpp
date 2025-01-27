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

void GrafoLista::carrega_grafo(const std::string& arquivo) {
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    int u, v, peso;
    while (file >> u >> v >> peso) {
        if (u >= numVertices || v >= numVertices) {
            std::cerr << "Vértice inválido." << std::endl;
            continue;
        }
        Aresta* novaAresta = new Aresta{v, peso, vertices[u].arestas};
        vertices[u].arestas = novaAresta;

        if (!direcionado) {
            Aresta* novaArestaInversa = new Aresta{u, peso, vertices[v].arestas};
            vertices[v].arestas = novaArestaInversa;
        }
    }
    file.close();
}

void GrafoLista::get_vizinhos(int v, int*& vizinhos, int& tamanho) {
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

int GrafoLista::n_conexo() {
    // Implementação do cálculo de componentes conexas (DFS ou BFS)
    // Retorna o número de componentes conexas
    return 0;
}

int GrafoLista::get_grau() {
    int grau = 0;
    for (int i = 0; i < numVertices; ++i) {
        int grauVertice = 0;
        Aresta* aresta = vertices[i].arestas;
        while (aresta) {
            grauVertice++;
            aresta = aresta->proxima;
        }
        if (grauVertice > grau) {
            grau = grauVertice;
        }
    }
    return grau;
}

bool GrafoLista::eh_completo() {
    for (int i = 0; i < numVertices; ++i) {
        bool* conectado = new bool[numVertices]{false};
        Aresta* aresta = vertices[i].arestas;
        while (aresta) {
            conectado[aresta->destino] = true;
            aresta = aresta->proxima;
        }
        for (int j = 0; j < numVertices; ++j) {
            if (i != j && !conectado[j]) {
                delete[] conectado;
                return false;
            }
        }
        delete[] conectado;
    }
    return true;
}
