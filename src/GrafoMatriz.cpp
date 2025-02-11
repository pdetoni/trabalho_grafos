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
/*
void GrafoMatriz::carrega_grafo(const std::string& arquivo) {
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << arquivo << std::endl;
        return;
    }

    // Lê a primeira linha (cabeçalho)
    int n, dir, vp, ap;
    file >> n >> dir >> vp >> ap;

    // Atualiza os atributos da classe base
    numVertices = n;
    direcionado = (dir == 1);
    verticesPonderados = (vp == 1);
    arestasPonderadas = (ap == 1);

    // Se os vértices são ponderados, lê os pesos dos vértices
    if (verticesPonderados) {
        int* pesos = new int[numVertices];
        for (int i = 0; i < numVertices; i++) {
            file >> pesos[i];
        }
        // Aqui você pode armazenar os pesos dos vértices em alguma estrutura
        // Por exemplo, você pode adicionar um array de pesos como atributo da classe
        delete[] pesos;
    }

    // Inicializa a matriz com zeros
    matrizAdj = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        matrizAdj[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            matrizAdj[i][j] = 0;
        }
    }

    // Lê as arestas
    int u, v, peso;
    while (file >> u >> v) {
        if (arestasPonderadas) {
            file >> peso;
        } else {
            peso = 1;  // Se não for ponderada, usa peso 1
        }

        // Como os vértices começam em 1 no arquivo, subtrai 1 para indexar o array
        matrizAdj[u-1][v-1] = peso;

        // Se o grafo não é direcionado, espelha a aresta
        if (!direcionado) {
            matrizAdj[v-1][u-1] = peso;
        }
    }

    file.close();
}
*/
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
/*
int GrafoMatriz::get_grau_vertice(int v) const{
    int grau = 0;
    int* vizinhos;
    get_vizinhos(v, vizinhos, grau);
    return grau;
}
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
/*
int GrafoMatriz::get_grau() {
    int grauMax = 0;
    if (eh_direcionado()) {
        for (int i = 0; i < numVertices; i++) {
            int grauSaida = 0;
            int grauEntrada = 0;
            for (int j = 0; j < numVertices; j++) {
                if (matrizAdj[i][j] != 0) grauSaida++;
                if (matrizAdj[j][i] != 0) grauEntrada++;
            }
            int grauTotal = grauSaida + grauEntrada;
            if (grauTotal > grauMax) grauMax = grauTotal;
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
*/

bool GrafoMatriz::existeAresta(int u, int v) const {
    return matrizAdj[u][v] != 0;
}
