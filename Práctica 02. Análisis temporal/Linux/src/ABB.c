/*
ABB.c
V 1.0 Abril 2022
Autor: Paola Reyes Francisco.

Implementación del árbol binario de búsqueda en C.
Toma n números enteros de la entrada estándar en la forma:
> ABB n n0 n1 n2 n3 n4 ...  (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo, e imprime la dirección de memoria donde se encontró el valor.
*/

//gcc ABB.c -o ABB.exe arbol/abb.c

#include <stdio.h>
#include <stdlib.h>
#include "arbol/abb.h"
//#include "tiempos/tiempo.h"

//void burbujaOptimizada1(int *A, int n);
//void imprimir(int *A, int n);
//void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);

int main(int argc, char *argv[])
{
	// Variable para determinar la longitud del arreglo
	int n;
	// Variable contadora para leer los números
	int i;
	// Variable auxiliar para ir almacenando las entradas
	int aux;
	// Árbol binario de búsqueda
	abb arbol;
	// Elemento auxiliar para ir almacenando al árbol
	elemento e;
	// Variable que almacena el valor a buscar
	int k;
	// Posicion del elemento a buscar
	posicion p;

	// Verifica si se reciben solo dos argumentos
	if(argc != 3)
	{
		printf("\n\n Para ejecutar el programa se necesita tama%co de arreglo y el n%cmero a buscar",164,163);
		printf("\n Ejemplo: %s 100 23781", argv[0]);
		exit(1);
	}
	// Lee el argumento
	n = atoi(argv[1]);
	
	Initialize(&arbol);
	// Lee de la entrada estándar los n valores y los coloca en el árbol
	for (i = 0; i < n; i++){
		scanf("%d", &aux);
		e.num = aux;
		Add(&arbol, e);
	}

	// Se lee el argumento del valor a buscar y se añade al elemento auxiliar
	k = atoi(argv[2]);
	e.num = k;

	printf("\n\n    %cRBOL BINARIO DE B%cSQUEDA\n    con %d n%cmeros\n",181,233,n,163);
	
	// Ejecución del algoritmo de búsqueda
	p = Busqueda(&arbol, e);

	printf("\n Valor a encontrar: %d", k);
	if(p == NULL){
		printf("\n \033[91mNO SE ENCONTR%c EL N%cMERO\033[0m\n", 224, 233);
	}
	else{
		printf("\n Se encontr%c en la posici%cn: %d\n",162,162, p);
	}
	return 1;
}