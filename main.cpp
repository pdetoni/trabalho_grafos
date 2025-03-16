#include <iostream>
#include <string>
#include <cstring>
#include "Grafo.h"
#include "GrafoLista.h"
#include "GrafoMatriz.h"

void imprimirCaminho(int* caminho, int tamanho) {
    std::cout << "Caminho encontrado: ";
    for (int i = 0; i < tamanho; i++) {
        std::cout << caminho[i] + 1; // +1 para exibir índices base 1
        if (i < tamanho - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    // Verificar argumentos de linha de comando
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " [-d] [-m/-l] arquivo_grafo.txt" << std::endl;
        std::cerr << "  -d: Debug mode (opcional)" << std::endl;
        std::cerr << "  -m: Usar representação de matriz de adjacência" << std::endl;
        std::cerr << "  -l: Usar representação de lista de adjacência" << std::endl;
        return 1;
    }

    bool debug = false;
    bool usarMatriz = false;
    std::string arquivo;

    // Processar argumentos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            debug = true;
        } else if (strcmp(argv[i], "-m") == 0) {
            usarMatriz = true;
        } else if (strcmp(argv[i], "-l") == 0) {
            usarMatriz = false;
        } else {
            arquivo = argv[i];
        }
    }

    // Verificar se o arquivo foi especificado
    if (arquivo.empty()) {
        std::cerr << "Erro: Arquivo de grafo não especificado." << std::endl;
        return 1;
    }

    // Inicializar o grafo conforme a representação escolhida
    Grafo* grafo;
    if (usarMatriz) {
        grafo = new GrafoMatriz(0, false, false, false);
        if (debug) {
            std::cout << "Usando representação de matriz de adjacência." << std::endl;
        }
    } else {
        grafo = new GrafoLista(0, false, false, false);
        if (debug) {
            std::cout << "Usando representação de lista de adjacência." << std::endl;
        }
    }

    // Carregar o grafo do arquivo
    if (debug) {
        std::cout << "Carregando grafo do arquivo: " << arquivo << std::endl;
    }
    
    try {
        grafo->carrega_grafo(arquivo);
    } catch (const std::exception& e) {
        std::cerr << "Erro ao carregar o grafo: " << e.what() << std::endl;
        delete grafo;
        return 1;
    }

    // Informações sobre o grafo carregado
    if (debug) {
        std::cout << "Grafo carregado com sucesso!" << std::endl;
        std::cout << "Número de vértices: " << grafo->get_ordem() << std::endl;
        std::cout << "Grafo " << (grafo->eh_direcionado() ? "direcionado" : "não direcionado") << std::endl;
        std::cout << "Vértices " << (grafo->vertice_ponderado() ? "ponderados" : "não ponderados") << std::endl;
        std::cout << "Arestas " << (grafo->aresta_ponderada() ? "ponderadas" : "não ponderadas") << std::endl;
        std::cout << "Número de componentes conexos: " << grafo->n_conexo() << std::endl;
        std::cout << "Grau máximo: " << grafo->get_grau() << std::endl;
        std::cout << "O grafo " << (grafo->eh_completo() ? "é" : "não é") << " completo" << std::endl;
    }

    // Executar o algoritmo do caixeiro viajante
    int vertice_inicial = 0; // Começar pelo vértice 0 (índice base 0)
    int* caminho = nullptr;
    int tamanho_caminho = 0;

    std::cout << "Executando algoritmo do Caixeiro Viajante a partir do vértice " << (vertice_inicial + 1) << std::endl;

    // Chamar a implementação apropriada do TSP baseada na representação
    if (usarMatriz) {
        GrafoMatriz* grafoMatriz = dynamic_cast<GrafoMatriz*>(grafo);
        if (grafoMatriz) {
            grafoMatriz->caixeiro_viajante_guloso_matriz(vertice_inicial, caminho, tamanho_caminho);
        }
    } else {
        GrafoLista* grafoLista = dynamic_cast<GrafoLista*>(grafo);
        if (grafoLista) {
            grafoLista->caixeiro_viajante_guloso_lista(vertice_inicial, caminho, tamanho_caminho);
        }
    }

    // Se não conseguiu chamar a versão específica, use a implementação genérica
    if (caminho == nullptr) {
        grafo->caixeiro_viajante_guloso(vertice_inicial, caminho, tamanho_caminho);
    }

    // Imprimir o caminho encontrado
    if (caminho != nullptr) {
        imprimirCaminho(caminho, tamanho_caminho);
        
        // Calcular o custo total do caminho
        int custo_total = 0;
        if (grafo->aresta_ponderada()) {
            for (int i = 0; i < tamanho_caminho - 1; i++) {
                int peso;
                // Use get_pesoAresta através do grafo (já que é uma função virtual)
                if (usarMatriz) {
                    GrafoMatriz* grafoMatriz = dynamic_cast<GrafoMatriz*>(grafo);
                    grafoMatriz->get_pesoAresta(caminho[i], caminho[i+1], peso);
                } else {
                    GrafoLista* grafoLista = dynamic_cast<GrafoLista*>(grafo);
                    grafoLista->get_pesoAresta(caminho[i], caminho[i+1], peso);
                }
                custo_total += peso;
            }
            std::cout << "Custo total do caminho: " << custo_total << std::endl;
        }
        
        // Liberar memória
        delete[] caminho;
    } else {
        std::cerr << "Erro: Não foi possível encontrar um caminho." << std::endl;
    }

    // Liberar memória
    delete grafo;

    return 0;
}