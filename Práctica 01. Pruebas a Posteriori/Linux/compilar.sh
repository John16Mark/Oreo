#!/bin/sh
# compilar.sh
# Version 1.0 Octubre 2022
# Autor: Darío Quiñones

# Un script de shell que compila todos los archivos .c en el directorio actual
# y los guarda en el directorio bin

# Variable de la carpeta de códigos fuente
SRC_DIR=src
# Variable de la carpeta de binarios
BIN_DIR=bin
# Variable de la carpeta de tiempos
TIM_DIR=src/tiempos/tiempo.c

# Crear el directorio de binarios
mkdir -p $BIN_DIR

# Compilar todos los archivos .c en el directorio actual y guardarlos en BIN_DIR
#gcc -o $BIN_DIR/burbujasim $SRC_DIR/BurbujaSimple.c $TIM_DIR
for f in $SRC_DIR/*.c
do
    RET_DIR=${f##*/}
    echo "  Compilando $RET_DIR"
    gcc -o $BIN_DIR/${RET_DIR%.*} $f $TIM_DIR
done