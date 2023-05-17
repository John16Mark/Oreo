/*

gcc Descomprimir.c lib/TADLista/TADListaDL.c
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

typedef struct direcciones{
	char entrada[150];
	char salida[150];
}direcciones;

typedef struct valArbol{
	unsigned char c;
	bool val;
}valArbol;

void codePreOrden(posicion n, elemento *Frec);
void asignarCodigo(posicion n, elemento *Frec);

int main(/*void *arg*/)
{

	//direcciones D0 = *((direcciones*)arg);
	double n_bytes_salida = 100;
	int pos_bit = 2;
	int i;
	elemento *Frec;			// Tabla de frecuencias
	elemento *Tablafrec;
	lista mi_lista;
	int n_char = 10;
	int n_bytes_cod = 500;
	int bits_sobrantes = 2;
	unsigned char *Acod;
	unsigned char *Asalida;

	FILE *TABLA = fopen("Tabla.txt", "r");

	//Verificar si el archivo se abrió correctamente
    if (TABLA == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

	// Hacer nuestro arreglo de frecuencias y lo inicializa en 0

	Frec = malloc(256 * sizeof(elemento));
	for(i = 0; i < 256; i++){
		Frec[i].frecuencia = 0;
	}

	// Leer la tabla de frecuencias

	Tablafrec = malloc(n_char * sizeof(elemento));

	// Guarda los valores e inserta en una lista los elementos
	Initialize(&mi_lista);

	for(i = 0; i < n_char; i++){
		fscanf(TABLA, "%c:%d\n", &Tablafrec[i].c, &Tablafrec[i].frecuencia);
		Add(&mi_lista, Tablafrec[i]);
	}

	fclose(TABLA);					// Cerramos el archivo de tabla

	SelectionSort(&mi_lista);

	//Verificar 			COMENTAR

	//for (i = 0; i < 10; i++) {
    //    printf("Letra: %c, Frecuencia: %d\n", Tablafrec[i].c, Tablafrec[i].frecuencia);
    //}


	// Hacer el arbol

	posicion raiz = NULL;			// Raiz
	nodo N;							// Nuevo nodo auxiliar
	posicion S1 = NULL; 			// Subarbol 1
	posicion S2 = NULL;				// Subarbol 2

	while(mi_lista.tam != 0){
		S1 = DequeuePos(&mi_lista);			// Desencola y guarda la posición
		S2 = DequeuePos(&mi_lista);			// Desencola y guarda la posición

		// Se modifica el nodo auxiliar con hijos S1 y S2
		N.e.frecuencia = S1->e.frecuencia + S2->e.frecuencia;
		N.ramaIzq = S1;
		N.ramaDer = S2;

		// Insertar el nodo ordenado
		if(mi_lista.tam != 0){
			InsertNodoIn(&mi_lista, N, 0);
			SelectionSort(&mi_lista);
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

	// Guardar el archivo a descomprimir	********************************

	FILE *archivocod = fopen("Comp.dat", "rb");

	Acod = (unsigned char *) malloc(n_bytes_cod * sizeof(unsigned char));

	// Leer el archivo y guardarlo en un arreglo

	fread(Acod, n_bytes_cod, 1, archivocod);		// Almacenar en Acod
	fclose(archivocod);							// Cerrar archivocod

	// Leer los bytes con el arbol y guardarlos en un arreglo

	unsigned char byte_aux = 0;
	int bits_consultados = 0;
	int j = 0;
	valArbol aux;

	for(i = 0; i < n_bytes_cod - bits_sobrantes; i++){
		
		// Caso Pone_1
		if(CONSULTARBIT(Acod[i/8], 7 - i%8) == 1){
			PONE_1(byte_aux, 7 - bits_consultados);
			bits_consultados++;
		}
			
		// Caso Pone_0
		else{
			bits_consultados++;
		}
		
		// Verifica si ya se llegó a una hoja

		aux = validaCaracter(raiz, byte_aux, bits_consultados);

		// Si ya llegó
		if(aux.val == true){
			Asalida[j] = Frec[aux.c].c;	// Guarda el caracter en el arreglo de salida
			j++;						// Avanza a la siguiente posición del arreglo de salida
			bits_consultados = 0;		// Vuelve a contar los bits
		}
		// Si no hay llegado no pasa nada
	}

	// Escribir los caracteres en un archivo.extensión
	


	return 0;
}


// FUNCIONES

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
		
		// Se mete al arreglo si es una hoja

		if(n->ramaIzq->ramaDer == NULL && n->ramaIzq->ramaIzq == NULL)
			Frec[n->ramaIzq->e.c] = n->ramaIzq->e;

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

		// Se mete al arreglo si es una hoja
		
		if(n->ramaDer->ramaDer == NULL && n->ramaDer->ramaIzq == NULL)
			Frec[n->ramaDer->e.c] = n->ramaDer->e;
		

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

valArbol validaCaracter(posicion n, unsigned char byte_aux, int bits_consultados){
	
	valArbol aux;
	int i;

	for(i = 0; i < bits_consultados; i++){
		
		// Se desplaza en el árbol
		if(CONSULTARBIT(byte_aux, 7 - i) == 1){
			n = n->ramaDer;
		}
		else{
			n = n->ramaIzq;
		}

		// Verifica si se llegó a una hoja

		if(n->e.limite == bits_consultados)
			aux.c = n->e.c;
			aux.val = true;
			return aux;
	}

	aux.val = false;
	return aux;
}