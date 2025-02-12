#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <string>

class GrafoMatriz : public Grafo {
private:
    int** matrizAdj;
    int capacidade;  // Capacidade atual da matriz

    void redimensionarMatriz(int novaCapacidade);

protected:
    void inicializa_estrutura() override;
    void adiciona_aresta(int origem, int destino, int peso) override;   
    void get_pesoAresta(int origem, int destino, int& peso) const override;
    void adiciona_no() override;
    void remove_no(int id) override;

public:
    GrafoMatriz(int n, bool dir = false, bool vp = false, bool ap = false);
    ~GrafoMatriz();

    void get_vizinhos(int v, int*& vizinhos, int& tamanho) const override;
    void get_arestas(int*& arestas, int& tamanho) override;
    bool existeAresta(int u, int v) const override;

    // Nova função para mostrar a capacidade atual da matriz
    int get_capacidade() const;
};

#endif // GRAFOMATRIZ_H