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
