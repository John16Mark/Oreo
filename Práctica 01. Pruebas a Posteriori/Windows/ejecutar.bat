::@echo off

set BIN=Ejecutables
set SRC=numeros10millones.txt
set OUT=Salidas

::%BIN%\burbujasimple.exe 100000 < %SRC% > %OUT%\burbujasim.txt
::%BIN%\burbujaopt1.exe 100000 < %SRC% > %OUT%\burbujaopt1.txt
::%BIN%\burbujaopt2.exe 100000 < %SRC% > %OUT%\burbujaopt2.txt
::%BIN%\insercion.exe 100000 < %SRC% > %OUT%\insercion.txt
%BIN%\seleccion.exe 100000 < %SRC% > %OUT%\seleccion.txt