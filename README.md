# Implementação de Grafos em C++

Este projeto implementa grafos em C++ usando duas representações diferentes: **Matriz de Adjacência** e **Lista de Adjacência**. O código é organizado em uma classe base (`Grafo`) e duas classes derivadas (`GrafoMatriz` e `GrafoLista`). O projeto também inclui testes automatizados usando o framework `CTest` do CMake.

## Estrutura do Projeto

- **`src/`**: Contém o código-fonte do projeto.
- **`tests/`**: Contém os casos de teste para validar a implementação.
- **`CMakeLists.txt`**: Arquivo de configuração do CMake para compilar o projeto e os testes.
- **`grafo.txt`**: Exemplo de arquivo de entrada para testar o programa.
- **`entradas/`**: Contém arquivos de entrada adicionais para testes.

## Requisitos

- Compilador C++ (e.g., `g++`, `clang++`)
- CMake (versão 3.10 ou superior)
- Git (para clonar o repositório)

## Como Compilar e Executar

### 1. Clonar o Repositório

```bash
git clone https://github.com/pdetoni/trabalho_grafos
cd trabalho_grafos
```

### 2. Configurar e Compilar o Projeto

```bash
mkdir build
cd build
cmake ..
make
```

Isso irá gerar:
- `main.out`: O programa principal para interagir com os grafos.

### 3. Executar o Programa Principal

O programa principal permite ler um grafo a partir de um arquivo de texto e exibir informações na tela. Use os seguintes comandos:

- Para ler um grafo representado por **matriz de adjacência**:

  ```bash
  ./main.out -d -m grafo.txt
  ```

- Para ler um grafo representado por **lista de adjacência**:

  ```bash
  ./main.out -d -l grafo.txt
  ```

### 4. Executar os Testes

Para rodar os testes automatizados, use o comando:

```bash
ctest
```

Isso executará todos os casos de teste definidos na pasta `tests/`.

Saída esperada:
```
Test project /caminho/para/build
Start  1: test1
 1/10 Test  #1: test1 ............................   Passed    0.01 sec
    Start  2: test2
 2/10 Test  #2: test2 ............................   Passed    0.00 sec
...
10/10 Test #10: test10 ...........................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 10
```