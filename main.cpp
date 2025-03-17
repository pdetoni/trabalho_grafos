#include <iostream>
#include <string>
#include <fstream>
#include "./include/GrafoMatriz.h"
#include "./include/GrafoLista.h"

/**
 * @brief Imprime a descrição do grafo.
 * 
 * Exibe informações sobre o grafo, como grau, ordem, se é direcionado, se os vértices
 * e arestas são ponderados, e se o grafo é completo.
 * 
 * @param grafo Ponteiro para o grafo a ser descrito.
 */
void imprimirDescricao(Grafo* grafo) {
    std::cout << "Grau: " << grafo->get_grau() << std::endl;
    std::cout << "Ordem: " << grafo->get_ordem() << std::endl;
    std::cout << "Direcionado: " << (grafo->eh_direcionado() ? "Sim" : "Não") << std::endl;
    std::cout << "Vertices ponderados: " << (grafo->vertice_ponderado() ? "Sim" : "Não") << std::endl;
    std::cout << "Arestas ponderadas: " << (grafo->aresta_ponderada() ? "Sim" : "Não") << std::endl;
    std::cout << "Completo: " << (grafo->eh_completo() ? "Sim" : "Não") << std::endl;
}

/**
 * @brief Função principal do programa.
 * 
 * Lê os argumentos da linha de comando, carrega o grafo a partir de um arquivo,
 * executa o algoritmo do caixeiro viajante guloso e imprime o caminho encontrado.
 * 
 * @param argc Número de argumentos da linha de comando.
 * @param argv Vetor de argumentos da linha de comando.
 * @return 0 se o programa for executado com sucesso, 1 em caso de erro.
 */
int main(int argc, char* argv[]) {
    // Verifica o número de argumentos
    if (argc != 4) {
        std::cerr << "Uso: " << argv[0] << " -p (-m ou -l) arquivo.txt" << std::endl;
        return 1;
    }

    std::string modo = argv[1];  // -p
    std::string tipo = argv[2];  // -m ou -l
    std::string arquivo = argv[3];  // arquivo.txt

    // Verifica se o modo é válido
    if (modo != "-p") {
        std::cerr << "Modo inválido. Use -p." << std::endl;
        return 1;
    }

    // Verifica se o tipo de grafo é válido
    if (tipo != "-m" && tipo != "-l") {
        std::cerr << "Tipo de grafo inválido. Use -m para matriz ou -l para lista." << std::endl;
        return 1;
    }

    // Abre o arquivo para ler o número de nós e configurações
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    // Lê as configurações do grafo a partir do arquivo
    int numVertices, direcionado, verticesPonderados, arestasPonderadas;
    file >> numVertices >> direcionado >> verticesPonderados >> arestasPonderadas;

    Grafo* grafo = nullptr; // Ponteiro para o grafo

    // Cria o grafo com base no tipo especificado
    // Cria o grafo com base no tipo especificado
    if (tipo == "-m") {
        grafo = new GrafoMatriz(numVertices, direcionado, verticesPonderados, arestasPonderadas);
    } else if (tipo == "-l") {
        grafo = new GrafoLista(numVertices, direcionado, verticesPonderados, arestasPonderadas);
    }

    // Carrega o grafo a partir do arquivo
    // Carrega o grafo a partir do arquivo
    grafo->carrega_grafo(arquivo);

    // Define o vértice inicial
    int vertice_inicial = 0;

    // Variáveis para armazenar o caminho e o tamanho do caminho
    int* caminho = nullptr;
    int tamanho_caminho = 0;

    // Chama a função caixeiro_viajante_guloso
    grafo->caixeiro_viajante_guloso(vertice_inicial, caminho, tamanho_caminho, true, false);

    // Imprime o caminho encontrado
    std::cout << "Caminho encontrado pelo caixeiro viajante guloso: ";
    for (int i = 0; i < tamanho_caminho; ++i) {
        std::cout << (caminho[i] + 1) << " ";  // Incrementa o valor do nó ao imprimir
    }
    std::cout << std::endl;

    // Libera a memória alocada para o caminho
    delete[] caminho;

    // Libera a memória alocada para o grafo
    delete grafo;

    return 0;
}