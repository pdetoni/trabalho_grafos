#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <limits>
#include <iostream>
#include <fstream>

class Grafo {
protected:
    int numVertices;          // Número de vértices no grafo
    bool direcionado;         // Define se o grafo é direcionado
    bool verticesPonderados;  // Define se os vértices possuem pesos
    bool arestasPonderadas;   // Define se as arestas possuem pesos

    // Funções auxiliares para DFS e cálculo de distância
    void dfs(int u, bool* visitado);
    int menor_distancia_dijkstra(int u, int v);
    virtual void get_pesoAresta(int origem, int destino, int& peso) const = 0;
public:
    // Construtor
    Grafo(int n, bool dir = false, bool vp = false, bool ap = false);

    // Destrutor virtual
    virtual ~Grafo();

    // Funções virtuais puras (abstrações)
    virtual void inicializa_estrutura() = 0;
    virtual void adiciona_aresta(int origem, int destino, int peso) = 0;
    virtual void adiciona_no() = 0;
    virtual void remove_no(int id) = 0;
    virtual void get_vizinhos(int v, int*& vizinhos, int& tamanho) const = 0;
    virtual void get_arestas(int*& arestas, int& tamanho) = 0;
    virtual bool existeAresta(int u, int v) const = 0;

    // Funções com implementação padrão
    int get_ordem();        // Retorna o número de vértices
    bool eh_direcionado();  // Verifica se o grafo é direcionado
    bool vertice_ponderado(); // Verifica se os vértices são ponderados
    bool aresta_ponderada();  // Verifica se as arestas são ponderadas
    int n_conexo();          // Retorna o número de componentes conexos
    bool eh_completo() const; // Verifica se o grafo é completo
    int get_grau();          // Retorna o grau máximo do grafo
    void carrega_grafo(const std::string& arquivo); // Carrega o grafo de um arquivo

    // Novas funções
    virtual void novo_no();
    virtual void nova_aresta(int origem, int destino, int peso);
    virtual void deleta_no(int id);
    virtual void deleta_aresta(int origem, int destino);
    int menor_distancia(int u, int v); // Calcula a menor distância entre dois nós
};

#endif // GRAFO_H