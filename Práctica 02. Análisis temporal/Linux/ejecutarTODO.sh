
# compilar.sh
# Version 1.0 abril 2023
# Autor: Juan Molina
# Basado en el script de shell que implementó Darío Quiñones el semestre pasado en AyED.

# Un script de shell que ejecuta todos los archivos .c en el directorio bin con un argumento
# y los guarda la salida en un archivo de texto en la carpeta out

# --------------------MODIFICAR ESTE VALOR-------------------------
THREADS=4
# -----------------------------------------------------------------
# Variables
BIN_DIR=bin
SRC=numeros10millones.txt
OUT_DIR=out

enes=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

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
    RET_DIR=${f##*/} # nombre del archivo pero regresando un directorio
    mkdir -p $OUT_DIR/$RET_DIR
    FOL_DIR=$OUT_DIR/$RET_DIR
    for n in ${enes[@]}
    do
	if [[ $f =~ (T)$ ]]; then
	    echo "  Ejecutando $RET_DIR $n con $THREADS hilos"
	    $f $n $THREADS < $SRC > $FOL_DIR/${f##*/}_$n.txt
	else
	    echo "  Ejecutando $RET_DIR $n"
	    $f $n < $SRC > $FOL_DIR/${f##*/}_$n.txt
	fi
    done
    
    #echo "  Ejecutando ${f##*/} 1000"
    #$f 1000 < $SRC > $OUT_DIR/${f##*/}.txt
    #for n in ${enes[@]}
    #do
    #	echo "  Ejecutando ${f##*/} $n"
    #	$f $n < $SRC >> $OUT_DIR/${f##*/}.txt
    #done
done

