cmake_minimum_required(VERSION 3.10)
project(TrabalhoGrafos)

# Define o padrão C++ (C++11 ou superior)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Inclui diretórios de cabeçalhos
include_directories(include)

# Adiciona os arquivos fonte
set(SOURCES
    src/Grafo.cpp
    src/GrafoLista.cpp
    src/GrafoMatriz.cpp
    main.cpp
)

# Cria o executável
add_executable(main.out ${SOURCES})