
# ejecutarEnTERMINAL.sh
# Version 1.5 abril 2023
# Autor: Juan Molina
# Basado en el script de shell que implementó Darío Quiñones el semestre pasado en AyED.

# Un script de shell que ejecuta todos los archivos .c en el directorio bin con un argumento
# y los guarda la salida en un archivo de texto en la carpeta out

# --------------------MODIFICAR ESTE VALOR-------------------------
ALGORITMO=ArbolBinarioT
n=10000000
THREADS=4
# -----------------------------------------------------------------
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

if [[ $ALGORITMO =~ (^(Lineal))|(^(ArbolBinario)) ]]; then
    SRC=numeros10millones.txt
else
    SRC=10millones.txt
fi
    
echo " SOURCE: $SRC"
if [[ $ALGORITMO =~ (T)$ ]]; then
    echo "  Ejecutando $ALGORITMO $n con $THREADS hilos"
    $BIN_DIR/$ALGORITMO $n $THREADS < $SRC
else
    echo "  Ejecutando $ALGORITMO $n"
    $BIN_DIR/$ALGORITMO $n < $SRC
fi
