#include "Grafo.h"

// Construtor
Grafo::Grafo(int n, bool dir, bool vp, bool ap)
    : numVertices(n), direcionado(dir), verticesPonderados(vp), arestasPonderadas(ap) {}

// Destrutor virtual
Grafo::~Grafo() {}

// Retorna o número de vértices (ordem do grafo)
int Grafo::get_ordem() {
    return numVertices;
}

// Verifica se o grafo é direcionado
bool Grafo::eh_direcionado() {
    return direcionado;
}

// Verifica se os vértices são ponderados
bool Grafo::vertice_ponderado() {
    return verticesPonderados;
}

// Verifica se as arestas são ponderadas
bool Grafo::aresta_ponderada() {
    return arestasPonderadas;
}

bool Grafo::eh_completo() const{
    int n = numVertices;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && !existeAresta(i, j)) {
                    return false;
                }
            }
        }
        return true;
}
