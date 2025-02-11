#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h" // Inclua o cabeçalho base da classe Grafo
#include <iostream>
#include <fstream>
#include <string>

class GrafoMatriz : public Grafo {
private:
    int** matrizAdj;

protected:
    void inicializa_estrutura() override;
    void adiciona_aresta(int origem, int destino, int peso) override;   
public:
    GrafoMatriz(int n, bool dir = false, bool vp = false, bool ap = false);
    ~GrafoMatriz();

    //void carrega_grafo(const std::string& arquivo) override;
    void get_vizinhos(int v, int*& vizinhos, int& tamanho) const override;
    void get_arestas(int*& arestas, int& tamanho) override;
    //int n_conexo() override;
   // int get_grau_vertice(int v) const override;
   // bool eh_completo() override;
    bool existeAresta(int u, int v) const override;
};

#endif // GRAFOMATRIZ_H
