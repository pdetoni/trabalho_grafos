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
        std::cerr << "Erro ao abrir o arquivo: " << arquivo << std::endl;
        return;
    }

    // Lê a primeira linha (cabeçalho)
    int n, dir, vp, ap;
    file >> n >> dir >> vp >> ap;
    // Obs.: supomos que 'numVertices' já foi definido (na construção) com o valor lido

    int u, v, peso;
    // Lê as arestas do arquivo – lembre-se que os vértices estão indexados a partir de 1
    while (file >> u >> v >> peso) {
        // Se ainda não existe uma aresta (para evitar sobrescrever duplicata),
        // atribui o peso lido.
        if (matrizAdj[u-1][v-1] == 0)
            matrizAdj[u-1][v-1] = peso;
        // Se o grafo NÃO é direcionado, insere também na posição simétrica
        if (!eh_direcionado() && matrizAdj[v-1][u-1] == 0)
            matrizAdj[v-1][u-1] = peso;
    }
    file.close();

    // -- Completa o grafo se ele for (ou se se deseja) completo --
    // Um grafo completo (segundo o critério da função eh_completo())
    // exige que para cada par de vértices distintos exista uma aresta.
    // Aqui, para cada par (i,j) com i ≠ j onde não haja aresta,
    // inserimos um "peso padrão" (1). No caso de grafo direcionado,
    // a ideia é preencher apenas uma das direções, de modo que para o par
    // (i,j) pelo menos um dos elementos (matrizAdj[i][j] ou matrizAdj[j][i])
    // seja não zero.
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i != j && matrizAdj[i][j] == 0) {
                if (eh_direcionado()) {
                    // Para grafos direcionados: se também não há aresta inversa, preenche
                    if (matrizAdj[j][i] == 0)
                        matrizAdj[i][j] = 1;
                } else {
                    // Para grafos não direcionados, preenche sempre a posição faltante
                    matrizAdj[i][j] = 1;
                }
            }
        }
    }
    
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
    int grauMax = 0;
    if (eh_direcionado()) {
        for (int i = 0; i < numVertices; i++) {
            int grau = 0;
            for (int j = 0; j < numVertices; j++) {
                if (matrizAdj[i][j] != 0) grau++;      // saídas
                if (matrizAdj[j][i] != 0) grau++;      // entradas
            }
            if (grau > grauMax) grauMax = grau;
        }
    } else {
        for (int i = 0; i < numVertices; i++) {
            int grau = 0;
            for (int j = 0; j < numVertices; j++) {
                if (matrizAdj[i][j] != 0) grau++;
            }
            if (grau > grauMax) grauMax = grau;
        }
    }
    return grauMax;
}


bool GrafoMatriz::eh_completo() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = i+1; j < numVertices; j++) {
            if (matrizAdj[i][j] == 0 && matrizAdj[j][i] == 0)
                return false;
        }
    }
    return true;
}

