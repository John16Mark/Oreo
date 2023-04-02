@echo off

set BIN=bin
set SRC=numeros.txt
set OUT=out

::%BIN%\burbujasimple.exe 100000 < %SRC% > %OUT%\burbujasim.txt
::%BIN%\burbujaopt1.exe 100000 < %SRC% > %OUT%\burbujaopt1.txt
::%BIN%\burbujaopt2.exe 100000 < %SRC% > %OUT%\burbujaopt2.txt
::%BIN%\insercion.exe 100000 < %SRC% > %OUT%\insercion.txt
::%BIN%\seleccion.exe 100000 < %SRC% > %OUT%\seleccion.txt
::%BIN%\Heapsort.exe 100000 < %SRC% > %OUT%\Heapsort.txt
::%BIN%\ABBbien.exe 100000 < %SRC% > %OUT%\ABBbien.txt
%BIN%\ABB.exe 10 179938885 < %SRC%