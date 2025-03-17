#include "GrafoLista.h"

/**
 * @brief Construtor da classe GrafoLista.
 * 
 * Inicializa o grafo com um número inicial de vértices e configurações de direção,
 * peso de vértices e peso de arestas.
 * 
 * @param n Número inicial de vértices.
 * @param dir Indica se o grafo é direcionado (true) ou não direcionado (false).
 * @param vp Indica se os vértices possuem peso (true) ou não (false).
 * @param ap Indica se as arestas possuem peso (true) ou não (false).
 */
GrafoLista::GrafoLista(int n, bool dir, bool vp, bool ap)
    : Grafo(n, dir, vp, ap) {
    vertices = new Vertice[n];
    for (int i = 0; i < n; ++i) {
        vertices[i].id = i;
        vertices[i].arestas = nullptr;
    }
}

/**
 * @brief Destrutor da classe GrafoLista.
 * 
 * Libera a memória alocada para os vértices e suas arestas.
 */
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

/**
 * @brief Inicializa a estrutura do grafo.
 * 
 * Aloca memória para os vértices e inicializa suas arestas como nulas.
 */
void GrafoLista::inicializa_estrutura() {
    vertices = new Vertice[numVertices];
    for (int i = 0; i < numVertices; i++) {
        vertices[i].arestas = nullptr;
        vertices[i].peso = 0;
    }
}

/**
 * @brief Adiciona uma aresta ao grafo.
 * 
 * @param origem ID do vértice de origem.
 * @param destino ID do vértice de destino.
 * @param peso Peso da aresta.
 */
void GrafoLista::adiciona_aresta(int origem, int destino, int peso) {
    Aresta* novaAresta = new Aresta{destino, peso, vertices[origem].arestas};
    vertices[origem].arestas = novaAresta;
}

/**
 * @brief Adiciona um novo vértice ao grafo.
 * 
 * Redimensiona o array de vértices para acomodar o novo vértice.
 */
void GrafoLista::adiciona_no() {
    aux = new Vertice[numVertices + 1];
    for (int i = 0; i < numVertices; ++i) {
        aux[i] = vertices[i];
    }
    numVertices++;
    delete[] vertices;
    inicializa_estrutura();
    vertices = aux;
}

/**
 * @brief Remove um vértice do grafo.
 * 
 * @param id ID do vértice a ser removido.
 */
void GrafoLista::remove_no(int id) {    
    for (int i = id; i < numVertices - 1; ++i) {        
        vertices[i] = vertices[i + 1];
    }
    numVertices--;
}

/**
 * @brief Obtém o peso de uma aresta entre dois vértices.
 * 
 * @param origem ID do vértice de origem.
 * @param destino ID do vértice de destino.
 * @param peso Referência para armazenar o peso da aresta.
 */
void GrafoLista::get_pesoAresta(int origem, int destino, int& peso) const {
    Aresta* aresta = vertices[origem].arestas;
    while (aresta) {
        if (aresta->destino == destino) {
            peso = aresta->peso;
        }
        aresta = aresta->proxima;
    }
}

/**
 * @brief Obtém os vizinhos de um vértice.
 * 
 * @param v ID do vértice.
 * @param vizinhos Referência para armazenar a lista de vizinhos.
 * @param tamanho Referência para armazenar o número de vizinhos.
 */
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

/**
 * @brief Obtém todas as arestas do grafo.
 * 
 * @param arestas Referência para armazenar a lista de arestas.
 * @param tamanho Referência para armazenar o número de arestas.
 */
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

/**
 * @brief Verifica se existe uma aresta entre dois vértices.
 * 
 * @param u ID do vértice de origem.
 * @param v ID do vértice de destino.
 * @return true se a aresta existe, false caso contrário.
 */
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