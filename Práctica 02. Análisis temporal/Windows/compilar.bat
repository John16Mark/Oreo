@echo off

rem compilar todos los algoritmos
rem .c del directorio

:: Dirección de la carpeta
set SRC=src
set BIN=bin

echo Compilando ABB.c
gcc %SRC%/ABB.c -o %BIN%/ABB.exe %SRC%/arbol/abb.c