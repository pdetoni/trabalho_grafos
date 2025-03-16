#include "GrafoLista.h"

GrafoLista::GrafoLista(int n, bool dir, bool vp, bool ap)
    : Grafo(n, dir, vp, ap) {
    vertices = new Vertice[n];
    for (int i = 0; i < n; ++i) {
        vertices[i].id = i;
        vertices[i].arestas = nullptr;
    }
}

GrafoLista::~GrafoLista() {
    for (int i = 0; i < numVertices; ++i) {
        Aresta* aresta = vertices[i].arestas;
        while (aresta) {
            Aresta* temp = aresta;
            aresta = aresta->proxima;
            delete temp;
        }
    }
    delete[] vertices;
}

void GrafoLista::inicializa_estrutura() {
    vertices = new Vertice[numVertices];
    for (int i = 0; i < numVertices; i++) {
        vertices[i].arestas = nullptr;
        vertices[i].peso = 0;
    }
}

void GrafoLista::adiciona_aresta(int origem, int destino, int peso) {
    Aresta* novaAresta = new Aresta{destino, peso, vertices[origem].arestas};
    vertices[origem].arestas = novaAresta;
}

void GrafoLista::adiciona_no() {
    aux = new Vertice[numVertices + 1];
    for (int i = 0; i < numVertices; ++i) {
        aux[i] = vertices[i];
    }
    numVertices++;
    delete[] vertices;
    inicializa_estrutura();
    vertices = aux;
}

void GrafoLista::remove_no(int id) {    
    for (int i = id; i < numVertices - 1; ++i) {        
        vertices[i] = vertices[i + 1];
    }
    numVertices--;
    
}

void GrafoLista::get_pesoAresta(int origem, int destino, int& peso) const {
    Aresta* aresta = vertices[origem].arestas;
    while (aresta) {
        if (aresta->destino == destino) {
            peso = aresta->peso;
        }
        aresta = aresta->proxima;
    }
}

void GrafoLista::get_vizinhos(int v, int*& vizinhos, int& tamanho) const {
    tamanho = 0;
    Aresta* aresta = vertices[v].arestas;
    while (aresta) {
        tamanho++;
        aresta = aresta->proxima;
    }

    vizinhos = new int[tamanho];
    int index = 0;
    aresta = vertices[v].arestas;
    while (aresta) {
        vizinhos[index++] = aresta->destino;
        aresta = aresta->proxima;
    }
}

void GrafoLista::get_arestas(int*& arestas, int& tamanho) {
    tamanho = 0;
    for (int i = 0; i < numVertices; ++i) {
        Aresta* aresta = vertices[i].arestas;
        while (aresta) {
            tamanho += 2; // Cada aresta é representada por dois valores (u, v)
            aresta = aresta->proxima;
        }
    }

    arestas = new int[tamanho];
    int index = 0;
    for (int i = 0; i < numVertices; ++i) {
        Aresta* aresta = vertices[i].arestas;
        while (aresta) {
            arestas[index++] = i;
            arestas[index++] = aresta->destino;
            aresta = aresta->proxima;
        }
    }
}

bool GrafoLista::existeAresta(int u, int v) const {
    Aresta* aresta = vertices[u].arestas;
    while (aresta) {
        if (aresta->destino == v) {
            return true;
        }
        aresta = aresta->proxima;
    }
    return false;
}

void GrafoLista::caixeiro_viajante_guloso_lista(int vertice_inicial, int*& caminho, int& tamanho_caminho) {
    bool* visitado = new bool[numVertices]();
    int* caminho_temp = new int[numVertices + 1];
    
    int atual = vertice_inicial;
    caminho_temp[0] = atual;
    visitado[atual] = true;
    int contador = 1;
    
    // Enquanto não visitamos todos os vértices
    for (int i = 1; i < numVertices; i++) {
        int melhor_vizinho = -1;
        int menor_peso = std::numeric_limits<int>::max();
        
        // Percorre a lista de adjacência para encontrar o vizinho não visitado com menor peso
        Aresta* aresta = vertices[atual].arestas;
        while (aresta) {
            int vizinho = aresta->destino;
            if (!visitado[vizinho]) {
                int peso = aresta->peso;
                if (peso < menor_peso) {
                    menor_peso = peso;
                    melhor_vizinho = vizinho;
                }
            }
            aresta = aresta->proxima;
        }
        
        // Se não encontrou mais vizinhos, busca qualquer vértice não visitado
        if (melhor_vizinho == -1) {
            for (int v = 0; v < numVertices; v++) {
                if (!visitado[v]) {
                    melhor_vizinho = v;
                    break;
                }
            }
            
            if (melhor_vizinho == -1) {
                break;
            }
        }
        
        // Adiciona o melhor vizinho ao caminho
        atual = melhor_vizinho;
        caminho_temp[contador++] = atual;
        visitado[atual] = true;
    }
    
    // Tenta completar o ciclo voltando ao vértice inicial
    Aresta* aresta = vertices[atual].arestas;
    bool ciclo_fechado = false;
    while (aresta) {
        if (aresta->destino == vertice_inicial) {
            caminho_temp[contador++] = vertice_inicial;
            ciclo_fechado = true;
            break;
        }
        aresta = aresta->proxima;
    }
    
    // Copia o caminho para o array de resultado
    tamanho_caminho = contador;
    caminho = new int[tamanho_caminho];
    for (int i = 0; i < tamanho_caminho; i++) {
        caminho[i] = caminho_temp[i];
    }
    
    // Libera a memória temporária
    delete[] caminho_temp;
    delete[] visitado;
}