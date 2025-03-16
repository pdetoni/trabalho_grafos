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

void GrafoMatriz::caixeiro_viajante_guloso_matriz(int vertice_inicial, int*& caminho, int& tamanho_caminho) {
    bool* visitado = new bool[numVertices]();
    int* caminho_temp = new int[numVertices + 1];
    
    int atual = vertice_inicial;
    caminho_temp[0] = atual;
    visitado[atual] = true;
    int contador = 1;
    
    // Enquanto não visitamos todos os vértices
    for (int i = 1; i < numVertices; i++) {
        int melhor_vizinho = -1;
        int menor_peso = std::numeric_limits<int>::max();
        
        // Percorre a linha da matriz para encontrar o vizinho não visitado com menor peso
        for (int j = 0; j < numVertices; j++) {
            if (matrizAdj[atual][j] > 0 && !visitado[j]) {
                int peso = matrizAdj[atual][j];
                if (peso < menor_peso) {
                    menor_peso = peso;
                    melhor_vizinho = j;
                }
            }
        }
        
        // Se não encontrou mais vizinhos, busca qualquer vértice não visitado
        if (melhor_vizinho == -1) {
            for (int v = 0; v < numVertices; v++) {
                if (!visitado[v]) {
                    melhor_vizinho = v;
                    break;
                }
            }
            
            if (melhor_vizinho == -1) {
                break;
            }
        }
        
        // Adiciona o melhor vizinho ao caminho
        atual = melhor_vizinho;
        caminho_temp[contador++] = atual;
        visitado[atual] = true;
    }
    
    // Tenta completar o ciclo voltando ao vértice inicial
    if (matrizAdj[atual][vertice_inicial] > 0) {
        caminho_temp[contador++] = vertice_inicial;
    }
    
    // Copia o caminho para o array de resultado
    tamanho_caminho = contador;
    caminho = new int[tamanho_caminho];
    for (int i = 0; i < tamanho_caminho; i++) {
        caminho[i] = caminho_temp[i];
    }
    
    // Libera a memória temporária
    delete[] caminho_temp;
    delete[] visitado;
}