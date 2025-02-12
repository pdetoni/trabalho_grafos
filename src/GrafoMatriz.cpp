#include "GrafoMatriz.h"

GrafoMatriz::GrafoMatriz(int n, bool dir, bool vp, bool ap)
    : Grafo(n, dir, vp, ap), capacidade(10) {
    if (n > capacidade) {
        capacidade = n;
    }
    inicializa_estrutura();
}

GrafoMatriz::~GrafoMatriz() {
    for (int i = 0; i < capacidade; ++i) {
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;
}

void GrafoMatriz::inicializa_estrutura() {
    matrizAdj = new int*[capacidade];
    for (int i = 0; i < capacidade; ++i) {
        matrizAdj[i] = new int[capacidade]{0}; // Inicializa a matriz com zeros
    }
}

void GrafoMatriz::redimensionarMatriz(int novaCapacidade) {
    int** novaMatriz = new int*[novaCapacidade];
    for (int i = 0; i < novaCapacidade; ++i) {
        novaMatriz[i] = new int[novaCapacidade]{0};
    }

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            novaMatriz[i][j] = matrizAdj[i][j];
        }
    }

    for (int i = 0; i < capacidade; ++i) {
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;

    matrizAdj = novaMatriz;
    capacidade = novaCapacidade;
}

void GrafoMatriz::adiciona_aresta(int origem, int destino, int peso) {
    if (origem >= capacidade || destino >= capacidade) {
        redimensionarMatriz(capacidade * 2);
    }
    matrizAdj[origem][destino] = peso;
    if (!direcionado) {
        matrizAdj[destino][origem] = peso;
    }
}

void GrafoMatriz::adiciona_no() {
    if (numVertices >= capacidade) {
        redimensionarMatriz(capacidade * 2);
    }
    numVertices++;
}

void GrafoMatriz::remove_no(int id) {
    if (id < 0 || id >= numVertices) {
        std::cerr << "Erro: ID do nó inválido." << std::endl;
        return;
    }

    // Remove o nó e reorganiza os IDs
    for (int i = id; i < numVertices - 1; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            matrizAdj[i][j] = matrizAdj[i + 1][j]; // Move as linhas para cima
        }
    }

    for (int j = id; j < numVertices - 1; ++j) {
        for (int i = 0; i < numVertices; ++i) {
            matrizAdj[i][j] = matrizAdj[i][j + 1]; // Move as colunas para a esquerda
        }
    }

    // Atualiza o número de vértices
    numVertices--;

    // Preenche a última linha e coluna com zeros
    for (int i = 0; i < numVertices; ++i) {
        matrizAdj[i][numVertices] = 0;
        matrizAdj[numVertices][i] = 0;
    }
}

void GrafoMatriz::get_pesoAresta(int origem, int destino, int& peso) const {
    peso = matrizAdj[origem][destino];
}

void GrafoMatriz::get_vizinhos(int v, int*& vizinhos, int& tamanho) const {
    tamanho = 0;
    for (int i = 0; i < numVertices; ++i) {
        if (matrizAdj[v][i] != 0) {
            tamanho++;
        }
    }

    vizinhos = new int[tamanho];
    int index = 0;
    for (int i = 0; i < numVertices; ++i) {
        if (matrizAdj[v][i] != 0) {
            vizinhos[index++] = i;
        }
    }
}

void GrafoMatriz::get_arestas(int*& arestas, int& tamanho) {
    tamanho = 0;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (matrizAdj[i][j] != 0) {
                tamanho += 2; // Cada aresta é representada por dois valores (u, v)
            }
        }
    }

    arestas = new int[tamanho];
    int index = 0;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (matrizAdj[i][j] != 0) {
                arestas[index++] = i;
                arestas[index++] = j;
            }
        }
    }
}

bool GrafoMatriz::existeAresta(int u, int v) const {
    return matrizAdj[u][v] != 0;
}