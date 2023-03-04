@echo off

rem compilar todos los algoritmos
rem .c del directorio

:: Dirección de la carpeta
set BIN=Algoritmos

gcc %BIN%\BurbujaSimple.c -o Ejecutables/burbujasimple.exe