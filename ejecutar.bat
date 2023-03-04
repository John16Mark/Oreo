::@echo off

set BIN=Ejecutables
set SRC=numeros10millones.txt
set OUT=out\out.txt

%BIN%\burbujasimple.exe 1000 < %SRC% > %OUT%