// ListaEncadeada.h
#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H

#include <iostream>

template <typename T>
class ListaEncadeada {
private:
    struct No {
        T dado;
        No* proximo;
        No(const T& valor) : dado(valor), proximo(nullptr) {}
    };
    
    No* cabeca;
    int tamanho;

public:
    ListaEncadeada() : cabeca(nullptr), tamanho(0) {}
    ~ListaEncadeada();
    void inserirInicio(const T& valor);
    void inserirFinal(const T& valor);
    bool removerInicio();
    bool buscar(const T& valor) const;
    int getTamanho() const;
    bool estaVazia() const;
    void imprimir() const;
};

#endif
