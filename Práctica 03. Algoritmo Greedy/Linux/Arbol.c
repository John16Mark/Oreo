/*

gcc Arbol.c lib/TADLista/TADListaDL.c
./a.out

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <math.h>
#include "lib/disenio.h"
#include "lib/ascii_art.h"
#include "lib/menu.h"
#include "lib/TADLista/TADListaDL.h"

int main()
{

	int i;
	elemento *Frec;			// Tabla de frecuencias *en prueba como tabla resumida*
	lista mi_lista;

	Frec = malloc(256 * sizeof(elemento));

	Initialize(&mi_lista);

	// Crea la tabla de frecuencias con tama�o 10 e inicializa en i la frecuencia de todos los bytes
	Frec = malloc(10 * sizeof(elemento));
	for(i = 1; i < 11; i++){
		Frec[i-1].frecuencia = i;
	}

	/*
	// Cuenta los caracteres
	for(i = 0; i < n_bytes; i++){
		Frec[A[i]].frecuencia++;
	}
	*/

	for(i = 0; i < 10; i++){
			Add(&mi_lista, Frec[i]);
	}
	// int tam_lista = Size(&mi_lista);

	//SelectionSort(&mi_lista);

	posicion raiz = NULL;
	nodo S1, S2, N;

	while(mi_lista.tam != 0){
		S1 = Dequeue(&mi_lista);
		//printf("%d ", S1.e.frecuencia);			// Comentarios para verificar en caso de ser necesario ( Se borran cuando el programa ya funcione)
		S2 = Dequeue(&mi_lista);
		//printf("%d ", S2.e.frecuencia);			// Mismo que arriba
		// Modificación de los valores para agregar un nodo simple

		N.e.frecuencia = S1.e.frecuencia + S2.e.frecuencia;
		N.ramaIzq = &S1;
		N.ramaDer = &S2;

		// Insertar el nodo ordenado
		if(mi_lista.tam != 0){
			InsertNodoIn(&mi_lista, N, 0);				// Lo quiero ordenado
			SelectionSort(&mi_lista);					// Si no se puede insertar ordenado
		}

		// Terminar cuando la lista esté vacía, se guarda la posición de raiz
		else{
			raiz = &N;
			printf("Fin en nodo con frecuencia %d ", raiz->e.frecuencia);
			break;
		}
	}

	
	return 0;
}