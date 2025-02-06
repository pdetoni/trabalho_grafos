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
add_executable(main.out ${SOURCES} main.cpp)

# Adiciona os arquivos de teste
set(TEST_SOURCES
    tests/test1.cpp
    tests/test2.cpp
    tests/test3.cpp
    tests/test4.cpp
    tests/test5.cpp
    tests/test6.cpp
    tests/test7.cpp
    tests/test8.cpp
    tests/test9.cpp
    tests/test10.cpp
)

# Copia a pasta de entradas para o mesmo diretório dos executáveis
add_custom_command(
    TARGET main.out POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/entradas ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/entradas
)

# Configura cada teste
foreach(test_file ${TEST_SOURCES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file} ${SOURCES})
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    
    # Adiciona o teste ao CTest
    add_test(
        NAME ${test_name}
        COMMAND ${test_name}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
    
    # Copia os arquivos de entrada para cada executável de teste
    add_custom_command(
        TARGET ${test_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/entradas ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/entradas
    )
endforeach()