#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include "ListaEncadeada.h"

class Grafo {

    struct Aresta {
        int destino;
        int peso;
        Aresta* prox;
    };

    struct Vertice {
        int id;
        int peso;
        Aresta* arestas;
    };

protected:
    int numVertices;          // Número de vértices no grafo
    bool direcionado;         // Define se o grafo é direcionado
    bool verticesPonderados;  // Define se os vértices possuem pesos
    bool arestasPonderadas;   // Define se as arestas possuem pesos

public:
    // Construtor
    Grafo(int n, bool dir = false, bool vp = false, bool ap = false);

    // Destrutor virtual
    virtual ~Grafo();

    // Funções virtuais puras (abstrações)
    virtual int n_conexo() = 0;
    virtual int get_grau() = 0;
    bool eh_completo() const;
    virtual void carrega_grafo(const std::string& arquivo) = 0;
    virtual void get_vizinhos(int v, int*& vizinhos, int& tamanho) = 0;
    virtual void get_arestas(int*& arestas, int& tamanho) = 0;

    // Funções com implementação padrão
    virtual int get_ordem();        // Retorna o número de vértices
    virtual bool eh_direcionado(); // Verifica se o grafo é direcionado
    virtual bool vertice_ponderado(); // Verifica se os vértices são ponderados
    virtual bool aresta_ponderada();  // Verifica se as arestas são ponderadas

    virtual bool existeAresta(int u, int v) const = 0; // Verifica se existe uma aresta entre u e v

};

#endif // GRAFO_H
