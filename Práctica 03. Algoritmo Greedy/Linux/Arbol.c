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

#define PESOBIT(bpos) 1<<bpos
#define CONSULTARBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)

void codePreOrden(posicion n, elemento *Frec);
void asignarCodigo(posicion n, elemento *Frec);

int main()
{

	int i;
	elemento *Frec;			// Tabla de frecuencias
	lista mi_lista;

	Frec = malloc(256 * sizeof(elemento));

	Initialize(&mi_lista);

	// Crea la tabla de frecuencias con tama�o 10 e inicializa en i la frecuencia de todos los bytes
	// Se creó de esta forma para que me fuera fácil entender lo que sucedía, NO va en el final
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

	// Asigna element.c y los agrega a la lista

	for(i = 0; i < 10; i++){
		if(Frec[i].frecuencia != 0){
			Frec[i].c = i;
			printf("\n%c",Frec[i].c);
			Add(&mi_lista, Frec[i]);
		}
	}

	SelectionSort(&mi_lista);

	posicion raiz = NULL;
	nodo N;
	posicion S1 = NULL; 
	posicion S2 = NULL;

	while(mi_lista.tam != 0){
		S1 = DequeuePos(&mi_lista);
		//printf("%d ", S1->e.frecuencia);			// Comentarios para verificar en caso de ser necesario ( Se borran cuando el programa ya funcione)
		S2 = DequeuePos(&mi_lista);
		//printf("%d ", S2->e.frecuencia);			// Mismo que arriba
		// Modificación de los valores para agregar un nodo simple

		N.e.frecuencia = S1->e.frecuencia + S2->e.frecuencia;
		N.ramaIzq = S1;
		N.ramaDer = S2;

		// Insertar el nodo ordenado
		if(mi_lista.tam != 0){
			InsertNodoIn(&mi_lista, N, 0);				// Lo quiero ordenado
			SelectionSort(&mi_lista);					// Si no se puede insertar ordenado
		}

		// Terminar cuando la lista esté vacía, se guarda la posición de raiz
		else{
			raiz = &N;
			printf("Fin en nodo con frecuencia %d ", raiz->e.frecuencia);		// Para verificar COMENTAR
			break;
		}
	}

	// Verificación de que se armó bien
	//printf("raiz->ramaIzq->ramaDer->e.frecuencia = %d ", raiz->ramaIzq->ramaDer->e.frecuencia);

	// Asignar códigos de manera recursiva por medio del recorrido en inOrden

	// Inicialmente se asigna el código 00000000 al nodo raiz

	int n_bits=sizeof(unsigned char)*8;
	raiz->e.code = 0;
	raiz->e.limite = 0;		// Para el nodo raiz
	Frec[raiz->e.c] = raiz->e;		// Se mete al arreglo

	//PONE_1(raiz->e.code, 7); 		//1 en Bit 0
	
	codePreOrden(raiz, Frec);

	/*
	Para verificar que se escribió bien el bit

	//Revisar el valor de cada bit
	printf("Valor de los bits\n");
	for (i=n_bits-1; i>=0; i--)
	printf("%d",CONSULTARBIT(raiz->e.code,i));
	printf("\t%u\n", raiz->e.code);

	*/

	
	return 0;
}

void codePreOrden(posicion n, elemento *Frec){
	if(n!=NULL){
		// ProcesarNodo, asignando su código correspondiente
		asignarCodigo(n, Frec);

		codePreOrden(n->ramaIzq, Frec);
		codePreOrden(n->ramaDer, Frec);
	}
}

void asignarCodigo(posicion n, elemento *Frec){

	// Copia el código y límite (lo incrementa), para su hijo izquierdo
	if(n->ramaIzq != NULL){
		// Actualización del límite
		n->ramaIzq->e.limite = n->e.limite;		// Copia el límite
		(n->ramaIzq->e.limite)++;				// Lo incrementa

		// Actualización del bit
		n->ramaIzq->e.code = n->e.code;			// Copia el código
		// No es necesario poner 0 porque inicia en 0
		//PONE_0(n->ramaIzq->e.code, 7 - n->ramaIzq->e.limite); 			// 0 en el bit n->ramaIzq->e.limite
		Frec[n->ramaIzq->e.code] = n->ramaIzq->e;			// Se mete al arreglo

	}

	// Copia el código y límite (lo incrementa), para su hijo derecho
	if(n->ramaDer != NULL){
		// Actualización del límite
		n->ramaDer->e.limite = n->e.limite;		// Copia el límite
		(n->ramaDer->e.limite)++;				// Lo incrementa
		printf("\n%d ", n->ramaDer->e.limite);	// Para verificar en que nivel se está imprimiendo COMENTAR

		// Actualización del bit
		n->ramaDer->e.code = n->e.code;			// Copia el código
		PONE_1(n->ramaDer->e.code, 7 - n->ramaIzq->e.limite + 1); 			// 1 en el bit n->ramaIzq->e.limite
		Frec[n->ramaDer->e.code] = n->ramaDer->e;				// Se mete al arreglo
		

	// Para verificar que funciona COMENTAR

	//***********************************************************
	//Revisar el valor de cada bit
	int n_bits = 8;
	printf("Valor de los bits\n");
	for (int i=n_bits-1; i>=0; i--)
	printf("%d",CONSULTARBIT(n->ramaDer->e.code,i));			// Para verificar que funciona COMENTAR
	}

	//************************************************************
}
