#!/bin/sh
# compilar.sh
# Version 1.9 marzo 2023
# Autor: Juan Molina
# Basado en el script de shell que implementó Darío Quiñones el semestre pasado en A y ED.

# Un script de shell que compila todos los archivos .c en el directorio src
# y los guarda en el directorio bin

# Variable de la carpeta de códigos fuente
SRC_DIR=src
# Variable de la carpeta de binarios
BIN_DIR=bin
# Variable de la librería de tiempos
TIM_DIR=src/lib/tiempo.c
# Variable de la librería de cola
COL_DIR=src/lib/TADColaDin.c

# Crear el directorio de binarios
mkdir -p $BIN_DIR

# Compilar todos los archivos .c en el directorio src y guardarlos en BIN_DIR
for f in $SRC_DIR/*.c
do
    RET_DIR=${f##*/} # nombre del archivo pero regresando un directorio
    echo "  Compilando $RET_DIR" # Imprime el nombre del archivo que se está compilando
    # $BIN_DIR/${RET_DIR%.*} El output lo genera en el directorio dado
    # $f src/nombre del archivo
    # $TIM_DIR librería para medición de tiempos.
    # $COL_DIR librería implementación de cola
    gcc -o $BIN_DIR/${RET_DIR%.*} $f $TIM_DIR $COL_DIR
    # gcc -o bin/BurbujaOptimizada1 src/BurbujaOptimizada1.c src/tiempos/tiempo.c
done

