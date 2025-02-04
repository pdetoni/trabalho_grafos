#include <iostream>
#include <string>
#include "GrafoMatriz.h"
#include "GrafoLista.h"

void imprimirDescricao(Grafo* grafo) {
    std::cout << "Grau: " << grafo->get_grau() << std::endl;
    std::cout << "Ordem: " << grafo->get_ordem() << std::endl;
    std::cout << "Direcionado: " << (grafo->eh_direcionado() ? "Sim" : "Não") << std::endl;
    std::cout << "Vertices ponderados: " << (grafo->vertice_ponderado() ? "Sim" : "Não") << std::endl;
    std::cout << "Arestas ponderadas: " << (grafo->aresta_ponderada() ? "Sim" : "Não") << std::endl;
    std::cout << "Completo: " << (grafo->eh_completo() ? "Sim" : "Não") << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: " << argv[0] << " -d (-m ou -l) arquivo.txt" << std::endl;
        return 1;
    }

    std::string modo = argv[1];
    std::string tipo = argv[2];
    std::string arquivo = argv[3];

    if (modo != "-d") {
        std::cerr << "Modo inválido. Use -d." << std::endl;
        return 1;
    }

    // Abre o arquivo para ler o número de nós e configurações
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    int numVertices, direcionado, verticesPonderados, arestasPonderadas;
    file >> numVertices >> direcionado >> verticesPonderados >> arestasPonderadas;

    Grafo* grafo = nullptr;

    if (tipo == "-m") {
        grafo = new GrafoMatriz(numVertices, direcionado, verticesPonderados, arestasPonderadas);
    } else if (tipo == "-l") {
        grafo = new GrafoLista(numVertices, direcionado, verticesPonderados, arestasPonderadas);
    } else {
        std::cerr << "Tipo de grafo inválido. Use -m para matriz ou -l para lista." << std::endl;
        return 1;
    }

    grafo->carrega_grafo(arquivo);
    imprimirDescricao(grafo);

    delete grafo;
    return 0;
}