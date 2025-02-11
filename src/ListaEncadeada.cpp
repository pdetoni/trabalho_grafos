// ListaEncadeada.cpp
#include "ListaEncadeada.h"

template <typename T>
ListaEncadeada<T>::~ListaEncadeada() {
    while (cabeca != nullptr) {
        No* temp = cabeca;
        cabeca = cabeca->proximo;
        delete temp;
    }
}

template <typename T>
void ListaEncadeada<T>::inserirInicio(const T& valor) {
    No* novoNo = new No(valor);
    novoNo->proximo = cabeca;
    cabeca = novoNo;
    tamanho++;
}

template <typename T>
void ListaEncadeada<T>::inserirFinal(const T& valor) {
    No* novoNo = new No(valor);
    if (cabeca == nullptr) {
        cabeca = novoNo;
    } else {
        No* atual = cabeca;
        while (atual->proximo != nullptr) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
    tamanho++;
}

template <typename T>
bool ListaEncadeada<T>::removerInicio() {
    if (cabeca == nullptr) {
        return false;
    }
    No* temp = cabeca;
    cabeca = cabeca->proximo;
    delete temp;
    tamanho--;
    return true;
}

template <typename T>
bool ListaEncadeada<T>::buscar(const T& valor) const {
    No* atual = cabeca;
    while (atual != nullptr) {
        if (atual->dado == valor) {
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

template <typename T>
int ListaEncadeada<T>::getTamanho() const {
    return tamanho;
}

template <typename T>
bool ListaEncadeada<T>::estaVazia() const {
    return cabeca == nullptr;
}

template <typename T>
void ListaEncadeada<T>::imprimir() const {
    No* atual = cabeca;
    while (atual != nullptr) {
        std::cout << atual->dado;
        if (atual->proximo != nullptr) {
            std::cout << " -> ";
        }
        atual = atual->proximo;
    }
    std::cout << std::endl;
}

// Explicação: Como é um template, as definições dos métodos devem estar no mesmo arquivo .h ou ser explicitamente instanciadas no .cpp.
