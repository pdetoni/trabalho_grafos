#include <iostream>
#include <cassert>
#include <fstream>
#include "GrafoLista.h"
#include "GrafoMatriz.h"

void verificaDescricao(Grafo* grafo) {
    assert(grafo->get_grau() == 2);
    assert(grafo->get_ordem() == 3);
    assert(grafo->eh_direcionado() == true);
    assert(grafo->vertice_ponderado() == false);
    assert(grafo->aresta_ponderada() == true);
    assert(grafo->eh_completo() == false);
}

int main() {
    std::string arquivo = "entradas/grafo8.txt";

    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    int numVertices, direcionado, verticesPonderados, arestasPonderadas;
    file >> numVertices >> direcionado >> verticesPonderados >> arestasPonderadas;

    Grafo* grafoMatriz = nullptr;
    Grafo* grafoLista = nullptr;

    grafoMatriz = new GrafoMatriz(numVertices, direcionado, verticesPonderados, arestasPonderadas);
    grafoLista = new GrafoLista(numVertices, direcionado, verticesPonderados, arestasPonderadas);

    grafoMatriz->carrega_grafo(arquivo);
    grafoLista->carrega_grafo(arquivo);

    //TODO: Arruamar eh_completo
    std::cout << "MATRIZ é completo: " << grafoMatriz->eh_completo() << std::endl;
    std::cout << "LISTA é completo: " << grafoLista->eh_completo() << std::endl;

    verificaDescricao(grafoMatriz);
    verificaDescricao(grafoLista);

    delete grafoMatriz;
    delete grafoLista;

    return 0;
}