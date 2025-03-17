#!/bin/bash

# filepath: /home/gustavo/code/trabalho_grafos/scripts/auto_run.sh

# Verifica se o número correto de argumentos foi passado
if [ "$#" -ne 2 ]; then
    echo "Uso: $0 <N> <A>"
    exit 1
fi

# Atribui os argumentos a variáveis
N=$1
A=$2

# Gera N grafos
for ((i=1; i<=N; i++))
do
    echo "Gerando grafo $i de $N com $A nós..."
    python3 gen_tsp.py $A --ponderado_arestas
done

echo "Geração de grafos concluída."