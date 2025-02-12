#include "GrafoMatriz.h"

GrafoMatriz::GrafoMatriz(int n, bool dir, bool vp, bool ap)
    : Grafo(n, dir, vp, ap) {
    matrizAdj = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrizAdj[i] = new int[n]{0}; // Inicializa a matriz com zeros
    }
}

GrafoMatriz::~GrafoMatriz() {
    for (int i = 0; i < numVertices; ++i) {
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;
}

void GrafoMatriz::inicializa_estrutura() {
    // Aloca e inicializa a matriz
    matrizAdj = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        matrizAdj[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            matrizAdj[i][j] = 0;
        }
    }
    
    
}

void GrafoMatriz::adiciona_aresta(int origem, int destino, int peso){
    matrizAdj[origem][destino] = peso;
    if(!direcionado){
        matrizAdj[destino][origem] = peso;
    } 
}



void GrafoMatriz::adiciona_no(){
    int** matrizAux = new int*[numVertices + 1];
    for (int i = 0; i < numVertices; ++i) {
        matrizAux[i] = new int[numVertices];
        for (int j = 0; j < numVertices; ++j) {
            matrizAux[i][j] = matrizAdj[i][j];
        }
    }
    for (int i = 0; i < numVertices; ++i) {
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;
    numVertices++;
    inicializa_estrutura();
    matrizAdj = matrizAux;
}

void GrafoMatriz::remove_no(int id){
    if (id < 0 || id >= numVertices) {
        std::cerr << "Erro: ID do nó inválido." << std::endl;
        return;
    }
    int** matrizAux = new int*[numVertices - 1];
    for (int i = 0; i < numVertices - 1; ++i) {
        matrizAux[i] = new int[numVertices - 1];
    }
    for (int i = 0; i < numVertices; ++i) {
        if (i == id) {
            continue;
        }
        for (int j = 0; j < numVertices; ++j) {
            if (j == id) {
                continue;
            }
            matrizAux[i][j] = matrizAdj[i][j];
        }
    }
    for (int i = 0; i < numVertices; ++i) {
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;
    numVertices--;
    inicializa_estrutura();
    matrizAdj = matrizAux;
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
