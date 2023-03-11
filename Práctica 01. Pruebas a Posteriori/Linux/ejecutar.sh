#!/bin/sh
# compilar.sh
# Version 1.0 marzo 2023
# Autor: Juan Molina
# Basado en el script de shell que implementó Darío Quiñones el semestre pasado en AyED.

# Un script de shell que ejecuta todos los archivos .c en el directorio bin con un argumento
# y los guarda la salida en un archivo de texto en la carpeta out

# Variables
BIN_DIR=bin
SRC=numeros10millones.txt
OUT_DIR=out

# Comprobar que el directorio bin existe
if [ ! -d $BIN_DIR ]; then
    echo "El directorio $BIN_DIR no existe, utilice el script compilar.sh para compilar los algoritmos"
    exit 1
fi

# Comprobar que el archivo de entrada existe
if [ ! -f $SRC ]; then
    echo "El archivo $SRC no esta en el directorio actual"
    exit 1
fi

# Crear el directorio de salida
mkdir -p $OUT_DIR

# Ejecutar todos los binarios en el directorio bin
for f in $BIN_DIR/*
do
    echo "Ejecutando $f"
    $f 1000 < $SRC > $OUT_DIR/${f##*/}.txt
done
