/**
 * @file Grafo.h
 * @brief Definição da classe Grafo para representação de grafos.
 */

 #ifndef GRAFO_H
 #define GRAFO_H
 
 #include <string>
 #include <limits>
 #include <iostream>
 #include <fstream>
 #include <cstdlib>
 #include <ctime>
 
 /**
  * @class Grafo
  * @brief Classe base para representação de um grafo.
  */
 class Grafo {
 protected:
     int numVertices;          ///< Número de vértices no grafo
     bool direcionado;         ///< Define se o grafo é direcionado
     bool verticesPonderados;  ///< Define se os vértices possuem pesos
     bool arestasPonderadas;   ///< Define se as arestas possuem pesos
 
     /**
      * @brief Função auxiliar para busca em profundidade (DFS).
      * @param u Índice do vértice inicial.
      * @param visitado Vetor de controle de visitação.
      */
     void dfs(int u, bool* visitado);
 
     /**
      * @brief Calcula a menor distância entre dois vértices usando Dijkstra.
      * @param u Vértice de origem.
      * @param v Vértice de destino.
      * @return A menor distância entre u e v.
      */
     int menor_distancia_dijkstra(int u, int v);
 
     /**
      * @brief Obtém o peso da aresta entre dois vértices.
      * @param origem Vértice de origem.
      * @param destino Vértice de destino.
      * @param peso Referência para armazenar o peso.
      */
     virtual void get_pesoAresta(int origem, int destino, int& peso) const = 0;
 
 public:
     /**
      * @brief Construtor da classe Grafo.
      * @param n Número de vértices.
      * @param dir Define se o grafo é direcionado.
      * @param vp Define se os vértices possuem pesos.
      * @param ap Define se as arestas possuem pesos.
      */
     Grafo(int n, bool dir = false, bool vp = false, bool ap = false);
 
     /**
      * @brief Destrutor virtual da classe Grafo.
      */
     virtual ~Grafo();
 
     /**
      * @brief Inicializa a estrutura do grafo.
      */
     virtual void inicializa_estrutura() = 0;
 
     /**
      * @brief Adiciona uma aresta ao grafo.
      * @param origem Vértice de origem.
      * @param destino Vértice de destino.
      * @param peso Peso da aresta.
      */
     virtual void adiciona_aresta(int origem, int destino, int peso) = 0;
 
     /**
      * @brief Adiciona um novo nó ao grafo.
      */
     virtual void adiciona_no() = 0;
 
     /**
      * @brief Remove um nó do grafo.
      * @param id Identificador do nó a ser removido.
      */
     virtual void remove_no(int id) = 0;
 
     /**
      * @brief Obtém os vizinhos de um vértice.
      * @param v Vértice alvo.
      * @param vizinhos Referência para vetor de vizinhos.
      * @param tamanho Referência para armazenar o tamanho do vetor.
      */
     virtual void get_vizinhos(int v, int*& vizinhos, int& tamanho) const = 0;
 
     /**
      * @brief Obtém todas as arestas do grafo.
      * @param arestas Referência para vetor de arestas.
      * @param tamanho Referência para armazenar o tamanho do vetor.
      */
     virtual void get_arestas(int*& arestas, int& tamanho) = 0;
 
     /**
      * @brief Verifica se uma aresta existe entre dois vértices.
      * @param u Vértice de origem.
      * @param v Vértice de destino.
      * @return True se a aresta existe, False caso contrário.
      */
     virtual bool existeAresta(int u, int v) const = 0;
 
     int get_ordem();        ///< Retorna o número de vértices.
     bool eh_direcionado();  ///< Verifica se o grafo é direcionado.
     bool vertice_ponderado(); ///< Verifica se os vértices são ponderados.
     bool aresta_ponderada();  ///< Verifica se as arestas são ponderadas.
     int n_conexo();          ///< Retorna o número de componentes conexos.
     bool eh_completo() const; ///< Verifica se o grafo é completo.
     int get_grau();          ///< Retorna o grau máximo do grafo.
 
     /**
      * @brief Carrega um grafo a partir de um arquivo.
      * @param arquivo Nome do arquivo de entrada.
      */
     void carrega_grafo(const std::string& arquivo);
 
     /**
      * @brief Adiciona um novo nó ao grafo.
      */
     virtual void novo_no();
 
     /**
      * @brief Adiciona uma nova aresta ao grafo.
      * @param origem Vértice de origem.
      * @param destino Vértice de destino.
      * @param peso Peso da aresta.
      */
     virtual void nova_aresta(int origem, int destino, int peso);
 
     /**
      * @brief Remove um nó do grafo.
      * @param id Identificador do nó a ser removido.
      */
     virtual void deleta_no(int id);
 
     /**
      * @brief Remove uma aresta do grafo.
      * @param origem Vértice de origem.
      * @param destino Vértice de destino.
      */
     virtual void deleta_aresta(int origem, int destino);
 
     /**
      * @brief Calcula a menor distância entre dois nós.
      * @param u Vértice de origem.
      * @param v Vértice de destino.
      * @return A menor distância entre os nós u e v.
      */
     int menor_distancia(int u, int v);
 
     /**
      * @brief Resolve o problema do Caixeiro Viajante usando um método guloso.
      * @param vertice_inicial Vértice de início do percurso.
      * @param caminho Referência para armazenar o caminho resultante.
      * @param tamanho_caminho Referência para armazenar o tamanho do caminho.
      * @param randomize Define se o método usa aleatoriedade.
      * @param reativo Define se o método é reativo.
      */
     int caixeiro_viajante(int vertice_inicial, int*& caminho, int& tamanho_caminho, bool randomize = false, bool reativo = false);
 };
 
 #endif // GRAFO_H
 