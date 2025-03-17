#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include <iostream>
#include <fstream>
#include <string>

#include "Grafo.h"

/**
 * @class GrafoLista
 * @brief Classe que implementa um grafo usando lista de adjacência.
 * 
 * Esta classe herda da classe base Grafo e implementa as funcionalidades
 * de um grafo utilizando uma lista de adjacência.
 */
class GrafoLista : public Grafo {
private:
    /**
     * @struct Aresta
     * @brief Estrutura que representa uma aresta no grafo.
     */
    struct Aresta {
        int destino;     ///< ID do vértice de destino da aresta.
        int peso;        ///< Peso da aresta.
        Aresta* proxima; ///< Ponteiro para a próxima aresta na lista de adjacência.
    };

    /**
     * @struct Vertice
     * @brief Estrutura que representa um vértice no grafo.
     */
    struct Vertice {
        int id;          ///< ID do vértice.
        int peso;        ///< Peso do vértice (se aplicável).
        Aresta* arestas; ///< Ponteiro para a lista de arestas adjacentes a este vértice.
    };

    Vertice* vertices; ///< Array de vértices que compõem o grafo.

protected:
    /**
     * @brief Inicializa a estrutura do grafo.
     * 
     * Esta função é responsável por inicializar a estrutura de dados do grafo,
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
     * @brief Adiciona um novo vértice ao grafo.
     */
    void adiciona_no() override;

    /**
     * @brief Remove um vértice do grafo.
     * 
     * @param id ID do vértice a ser removido.
     */
    void remove_no(int id) override;

    /**
     * @brief Obtém o peso de uma aresta entre dois vértices.
     * 
     * @param origem ID do vértice de origem.
     * @param destino ID do vértice de destino.
     * @param peso Referência para armazenar o peso da aresta.
     */
    void get_pesoAresta(int origem, int destino, int& peso) const override;

public:
    /**
     * @brief Construtor da classe GrafoLista.
     * 
     * @param n Número de vértices iniciais no grafo.
     * @param dir Indica se o grafo é direcionado (true) ou não direcionado (false).
     * @param vp Indica se os vértices possuem peso (true) ou não (false).
     * @param ap Indica se as arestas possuem peso (true) ou não (false).
     */
    GrafoLista(int n, bool dir = false, bool vp = false, bool ap = false);

    /**
     * @brief Destrutor da classe GrafoLista.
     * 
     * Libera a memória alocada para a estrutura do grafo.
     */
    ~GrafoLista();

    Vertice* aux; ///< Ponteiro auxiliar para manipulação interna do grafo.

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
};

#endif // GRAFOLISTA_H