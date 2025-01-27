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

void GrafoMatriz::carrega_grafo(const std::string& arquivo) {
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
        matrizAdj[u][v] = peso;
        if (!direcionado) {
            matrizAdj[v][u] = peso;
        }
    }
    file.close();
}

void GrafoMatriz::get_vizinhos(int v, int*& vizinhos, int& tamanho) {
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

int GrafoMatriz::n_conexo() {
    // Implementação do cálculo de componentes conexas (DFS ou BFS)
    // Retorna o número de componentes conexas
    return 0;
}

int GrafoMatriz::get_grau() {
    int grau = 0;
    for (int i = 0; i < numVertices; ++i) {
        int grauVertice = 0;
        for (int j = 0; j < numVertices; ++j) {
            if (matrizAdj[i][j] != 0) {
                grauVertice++;
            }
        }
        if (grauVertice > grau) {
            grau = grauVertice;
        }
    }
    return grau;
}

bool GrafoMatriz::eh_completo() {
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (i != j && matrizAdj[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}
