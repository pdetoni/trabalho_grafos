#include "../include/GrafoMatriz.h"

/**
 * @brief Construtor da classe GrafoMatriz.
 * 
 * Inicializa o grafo com um número inicial de vértices e configurações de direção,
 * peso de vértices e peso de arestas. A matriz de adjacência é inicializada com
 * uma capacidade padrão de 10, mas pode ser redimensionada se necessário.
 * 
 * @param n Número inicial de vértices.
 * @param dir Indica se o grafo é direcionado (true) ou não direcionado (false).
 * @param vp Indica se os vértices possuem peso (true) ou não (false).
 * @param ap Indica se as arestas possuem peso (true) ou não (false).
 */
GrafoMatriz::GrafoMatriz(int n, bool dir, bool vp, bool ap)
    : Grafo(n, dir, vp, ap), capacidade(10) {
    if (n > capacidade) {
        capacidade = n;
    }
    inicializa_estrutura();
}

/**
 * @brief Destrutor da classe GrafoMatriz.
 * 
 * Libera a memória alocada para a matriz de adjacência.
 */
GrafoMatriz::~GrafoMatriz() {
    for (int i = 0; i < capacidade; ++i) {
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;
}

/**
 * @brief Inicializa a estrutura do grafo.
 * 
 * Aloca memória para a matriz de adjacência e inicializa todos os valores com zero.
 */
void GrafoMatriz::inicializa_estrutura() {
    matrizAdj = new int*[capacidade];
    for (int i = 0; i < capacidade; ++i) {
        matrizAdj[i] = new int[capacidade]{0}; // Inicializa a matriz com zeros
    }
}

/**
 * @brief Redimensiona a matriz de adjacência para uma nova capacidade.
 * 
 * Cria uma nova matriz com a capacidade especificada, copia os valores da matriz
 * antiga e libera a memória da matriz antiga.
 * 
 * @param novaCapacidade Nova capacidade da matriz.
 */
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

/**
 * @brief Adiciona uma aresta ao grafo.
 * 
 * Se os vértices de origem ou destino excederem a capacidade atual da matriz,
 * a matriz é redimensionada. O peso da aresta é armazenado na matriz de adjacência.
 * 
 * @param origem ID do vértice de origem.
 * @param destino ID do vértice de destino.
 * @param peso Peso da aresta.
 */
void GrafoMatriz::adiciona_aresta(int origem, int destino, int peso) {
    if (origem >= capacidade || destino >= capacidade) {
        redimensionarMatriz(capacidade * 2);
    }
    matrizAdj[origem][destino] = peso;
    if (!direcionado) {
        matrizAdj[destino][origem] = peso;
    }
}

/**
 * @brief Adiciona um novo vértice ao grafo.
 * 
 * Se o número de vértices exceder a capacidade atual da matriz, a matriz é redimensionada.
 */
void GrafoMatriz::adiciona_no() {
    if (numVertices >= capacidade) {
        redimensionarMatriz(capacidade * 2);
    }
    numVertices++;
}

/**
 * @brief Remove um vértice do grafo.
 * 
 * Remove o vértice com o ID especificado e reorganiza a matriz de adjacência.
 * 
 * @param id ID do vértice a ser removido.
 */
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

/**
 * @brief Obtém o peso de uma aresta entre dois vértices.
 * 
 * @param origem ID do vértice de origem.
 * @param destino ID do vértice de destino.
 * @param peso Referência para armazenar o peso da aresta.
 */
void GrafoMatriz::get_pesoAresta(int origem, int destino, int& peso) const {
    peso = matrizAdj[origem][destino];
}

/**
 * @brief Obtém os vizinhos de um vértice.
 * 
 * @param v ID do vértice.
 * @param vizinhos Referência para armazenar a lista de vizinhos.
 * @param tamanho Referência para armazenar o número de vizinhos.
 */
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

/**
 * @brief Obtém todas as arestas do grafo.
 * 
 * @param arestas Referência para armazenar a lista de arestas.
 * @param tamanho Referência para armazenar o número de arestas.
 */
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

/**
 * @brief Verifica se existe uma aresta entre dois vértices.
 * 
 * @param u ID do vértice de origem.
 * @param v ID do vértice de destino.
 * @return true se a aresta existe, false caso contrário.
 */
bool GrafoMatriz::existeAresta(int u, int v) const {
    return matrizAdj[u][v] != 0;
}