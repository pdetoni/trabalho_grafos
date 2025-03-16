cmake_minimum_required(VERSION 3.10)
project(TrabalhoGrafos)

# Habilita o CTest
include(CTest)

# Define o padrão C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Inclui diretórios de cabeçalhos
include_directories(${CMAKE_SOURCE_DIR}/include)

# Configura diretório de saída dos executáveis
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Adiciona os arquivos fonte
set(SOURCES
    src/Grafo.cpp
    src/GrafoLista.cpp
    src/GrafoMatriz.cpp
)

# Cria o executável principal
add_executable(main.out ${SOURCES} testem.cpp)

add_custom_command(
    TARGET main.out POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/entradas ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/entradas
)