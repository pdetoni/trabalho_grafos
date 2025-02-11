#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include <iostream>
#include <fstream>
#include <string>

#include "Grafo.h"

class GrafoLista : public Grafo {
private:
    struct Aresta {
        int destino;
        int peso;
        Aresta* proxima;
    };

    struct Vertice {
        int id;
        int peso;
        Aresta* arestas;
    };

    Vertice* vertices;
protected:
    void inicializa_estrutura() override;
    void adiciona_aresta(int origem, int destino, int peso) override;
public:
    GrafoLista(int n, bool dir = false, bool vp = false, bool ap = false);
    ~GrafoLista();

    //void carrega_grafo(const std::string& arquivo) override;
    void get_vizinhos(int v, int*& vizinhos, int& tamanho) const override;
    void get_arestas(int*& arestas, int& tamanho) override;
    //int n_conexo() override;
    //int get_grau() override;
   // bool eh_completo() override;
    bool existeAresta(int u, int v) const override;
    //int get_grau_vertice(int v) const override;
};

#endif // GRAFOLISTA_H
