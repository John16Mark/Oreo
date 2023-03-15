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
    echo "  Ejecutando ${f##*/} 1000"
    $f 1000 < $SRC > $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 2000"
    $f 2000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 3000"
    $f 3000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 4000"
    $f 4000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 5000"
    $f 5000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 8000"
    $f 8000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 10000"
    $f 10000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 50000"
    $f 50000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 100000"
    $f 100000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 150000"
    $f 150000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 200000"
    $f 200000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 300000"
    $f 300000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 400000"
    $f 400000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 500000"
    $f 500000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 600000"
    $f 600000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 700000"
    $f 700000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 800000"
    $f 800000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 900000"
    $f 900000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 1000000"
    $f 1000000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 1500000"
    $f 1500000 < $SRC >> $OUT_DIR/${f##*/}.txt
    echo "  Ejecutando ${f##*/} 2000000"
    $f 2000000 < $SRC >> $OUT_DIR/${f##*/}.txt
done

