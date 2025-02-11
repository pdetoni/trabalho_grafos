#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include "ListaEncadeada.h"

#include <iostream>
#include <fstream>
#include <string>
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
    void dfs(int u, bool* visitado) ;
    void getVizinhos(int u, int*& numVizinhos, int& tamanho) const;
    virtual void inicializa_estrutura() = 0;
    virtual void adiciona_aresta(int origem, int destino, int peso) = 0;
public:
    // Construtor
    Grafo(int n, bool dir = false, bool vp = false, bool ap = false);

    // Destrutor virtual
    virtual ~Grafo();

    // Funções virtuais puras (abstrações)
    int n_conexo() ;
   // virtual int get_grau() const;
    bool eh_completo() const;
    void carrega_grafo(const std::string& arquivo) ;
    virtual void get_vizinhos(int v, int*& vizinhos, int& tamanho) const = 0;
    virtual void get_arestas(int*& arestas, int& tamanho) = 0;

    // Funções com implementação padrão
    virtual int get_ordem();        // Retorna o número de vértices
    virtual bool eh_direcionado(); // Verifica se o grafo é direcionado
    virtual bool vertice_ponderado(); // Verifica se os vértices são ponderados
    virtual bool aresta_ponderada();  // Verifica se as arestas são ponderadas
    //virtual int get_grau_vertice(int v) const; // Retorna o grau do vértice v
    virtual int get_grau() ; // Retorna o grau do grafo
    virtual bool existeAresta(int u, int v) const = 0; // Verifica se existe uma aresta entre u e v

};

#endif // GRAFO_H
