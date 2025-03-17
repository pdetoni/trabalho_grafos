#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <string>

/**
 * @class GrafoMatriz
 * @brief Classe que implementa um grafo usando matriz de adjacência.
 * 
 * Esta classe herda da classe base Grafo e implementa as funcionalidades
 * de um grafo utilizando uma matriz de adjacência.
 */
class GrafoMatriz : public Grafo {
private:
    int** matrizAdj; ///< Matriz de adjacência que armazena as arestas do grafo.
    int capacidade;  ///< Capacidade atual da matriz (número máximo de vértices suportados).

    /**
     * @brief Redimensiona a matriz de adjacência para uma nova capacidade.
     * 
     * @param novaCapacidade Nova capacidade da matriz.
     */
    void redimensionarMatriz(int novaCapacidade);

protected:
    /**
     * @brief Inicializa a estrutura do grafo.
     * 
     * Esta função é responsável por inicializar a matriz de adjacência,
     * alocando memória e configurando os valores iniciais.
     */
    void inicializa_estrutura() override;

    /**
     * @brief Adiciona uma aresta ao grafo.
     * 
     * @param origem ID do vértice de origem.
     * @param destino ID do vértice de destino.
     * @param peso Peso da aresta.
     */
    void adiciona_aresta(int origem, int destino, int peso) override;

    /**
     * @brief Obtém o peso de uma aresta entre dois vértices.
     * 
     * @param origem ID do vértice de origem.
     * @param destino ID do vértice de destino.
     * @param peso Referência para armazenar o peso da aresta.
     */
    void get_pesoAresta(int origem, int destino, int& peso) const override;

    /**
     * @brief Adiciona um novo vértice ao grafo.
     * 
     * Redimensiona a matriz de adjacência, se necessário, para acomodar o novo vértice.
     */
    void adiciona_no() override;

    /**
     * @brief Remove um vértice do grafo.
     * 
     * @param id ID do vértice a ser removido.
     */
    void remove_no(int id) override;

public:
    /**
     * @brief Construtor da classe GrafoMatriz.
     * 
     * @param n Número de vértices iniciais no grafo.
     * @param dir Indica se o grafo é direcionado (true) ou não direcionado (false).
     * @param vp Indica se os vértices possuem peso (true) ou não (false).
     * @param ap Indica se as arestas possuem peso (true) ou não (false).
     */
    GrafoMatriz(int n, bool dir = false, bool vp = false, bool ap = false);

    /**
     * @brief Destrutor da classe GrafoMatriz.
     * 
     * Libera a memória alocada para a matriz de adjacência.
     */
    ~GrafoMatriz();

    /**
     * @brief Obtém os vizinhos de um vértice.
     * 
     * @param v ID do vértice.
     * @param vizinhos Referência para armazenar a lista de vizinhos.
     * @param tamanho Referência para armazenar o número de vizinhos.
     */
    void get_vizinhos(int v, int*& vizinhos, int& tamanho) const override;

    /**
     * @brief Obtém todas as arestas do grafo.
     * 
     * @param arestas Referência para armazenar a lista de arestas.
     * @param tamanho Referência para armazenar o número de arestas.
     */
    void get_arestas(int*& arestas, int& tamanho) override;

    /**
     * @brief Verifica se existe uma aresta entre dois vértices.
     * 
     * @param u ID do vértice de origem.
     * @param v ID do vértice de destino.
     * @return true se a aresta existe, false caso contrário.
     */
    bool existeAresta(int u, int v) const override;

    /**
     * @brief Obtém a capacidade atual da matriz de adjacência.
     * 
     * @return A capacidade atual da matriz (número máximo de vértices suportados).
     */
    int get_capacidade() const;
};

#endif // GRAFOMATRIZ_H