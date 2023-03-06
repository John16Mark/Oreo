@echo off

rem compilar todos los algoritmos
rem .c del directorio

:: Dirección de la carpeta
set BIN=Algoritmos
set EXE=Ejecutables

gcc %BIN%/BurbujaSimple.c -o %EXE%/burbujasimple.exe
gcc %BIN%/BurbujaOptimizada1.c -o %EXE%/burbujaopt1.exe
gcc %BIN%/BurbujaOptimizada2.c -o %EXE%/burbujaopt2.exe
gcc %BIN%/Insercion.c -o %EXE%/insercion.exe
gcc %BIN%/Seleccion.c -o %EXE%/seleccion.exe 