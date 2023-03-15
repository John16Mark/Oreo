/*
Treesort.c
V 1.0 Marzo 2022
Autor: Yael André Blazquez Martínez, Aarón Olvera Martínez.

Implementación del ordenamiento por árbol binario en C.
Toma n números enteros de la entrada estándar en la forma:
> mezcla.exe n n0 n1 n2 n3 n4 ...  (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo e imprime el arreglo ordenado(opcional).
*/

#include <stdio.h>
#include <stdlib.h>
#include "tiempos/tiempo.h"

/*
struct Nodo
Contiene:
	int v				número almacenado
	struct Nodo *izq	apuntador a nodo, hijo izquierdo
	struct Nodo *der	apuntador a nodo, hijo derecho
	int cont 			veces que se repite el número almacenado
*/
typedef struct Nodo {
	int v;
	struct Nodo *izq;
	struct Nodo *der;
	int cont;
} Nodo;

// Funciones del árbol
Nodo *nuevonodo(int v);
void buscar(Nodo **r, int v, Nodo **actual, Nodo **anterior);
void insertar(Nodo **r, int v);
void procesarNodo(Nodo* n, int *A, int *i);
void inOrden(Nodo* n, int *A, int *i);
// Ordenamiento
void TreeSort(int *A, int n);
// Imprimir arreglo
void imprimir(int *A, int n);
// Mostrar estadísticas
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);

int main(int argc, char *argv[])
{
	// Variables para la medición de tiempos.
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	// Variable para determinar la longitud del arreglo
	int n;
	// Variable contadora para leer los números
	int i;
	// Apuntador al arreglo
	int *A;
	
	if(argc != 2)
	{
		printf("\n\n Para compilar el programa se necesita tamanio de arreglo");
		printf("\n Ejemplo: %s 100", argv[0]);
		exit(1);
	}
	// Lee el argumento y crea un arreglo con el tamaño recibido
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	if (A == NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n", n);
		exit(1);
	}
	// Lee de la entrada estándar los n valores y los coloca en el arreglo
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	printf("\n\n    TREESORT\n    con %d números\n",n);
	
	// Inicia la medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);
	// Ejecución del algoritmo de ordenamiento
	TreeSort(A,n);
	// Termina la medición de tiempos
	uswtime(&utime1, &stime1, &wtime1);

	// Imprime el rendimiento de la ejecución del algoritmo
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);
	
	// Imprime el arreglo
	// imprimir(A, n);
	
	return 1;
}

/*
void TreeSort(int *A, int n)
Recibe:	*A: Dirección del arreglo original a ordenar
		 n:	Cantidad/tamaño del arreglo a ordenar
Crea el nodo raíz y una variable que marca la posición de hasta dónde se ha llenado el arreglo
Inserta todos los valores de A en el árbol, y los realmacena usando el recorrdo InOrden
*/
void TreeSort(int *A, int n)
{
	int i;
	Nodo *r = NULL;
	
	for(i=0; i<n; i++){
		insertar(&r, A[i]);
	}
	
	i=0;
	inOrden(r, A, &i);
}

//Funciones arbol--------------------------------------------------------------------------------------

/*
Nodo *nuevonodo(int v)
Recibe:
	v: Número a acomodar.
Crea un nuevo nodo que será añadido al árbol
Regresa:
	Nodo creado dentro de la función
*/
Nodo *nuevonodo(int v)
{
	Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
	if(nuevo==NULL){
		printf("No se generó correctamente el nodo");
		exit(1);
	}	
	nuevo->v=v;
	nuevo->der=NULL;
	nuevo->izq=NULL;
	nuevo->cont=0;
	return nuevo; //<- Preguntarle al profe
}

/*
void buscar(Nodo **r, int v, Nodo **actual, Nodo **anterior)
Recibe:	  **r:	Apuntador a nodo raíz.
			v:	Valor a buscar
     **actual:	Apuntador al apuntador del nodo actual
   **anterior:	Apuntador al apuntador del nodo padre
Revisa si el valor recibido ya existe en el árbol. Actualiza el padre de un nuevo nodo.
*/
void buscar(Nodo **r, int v, Nodo **actual, Nodo **anterior)
{
	*anterior = NULL;
	*actual=*r;
	int encontrado=0;
	
	while( !encontrado && *actual!=NULL){
		
		if(v==(*actual)->v){
			encontrado=1;
		}else{
			*anterior=*actual;			//Se recorre al nodo padre
			if(v<(*actual)->v){			//Si v es menor que el valor del nodo
				*actual=(*actual)->izq;		//Se ubica en el hijo izquierdo
			}else{
				*actual=(*actual)->der;		//Se ubica en el hijo derecho
			}
		}
		
	}

}

/*
void insertar(Nodo **r, int v)
Recibe:	**r:	Apuntador a nodo raíz.
		  v:	Valor a buscar
De un nodo creado en la función nuevonodo(v), llama a la función buscar para saber si añadir en la raíz y para actualizar
al padre del nodo nuevo. Posteriormente, añade el nodo en su posición correcta.
*/
void insertar(Nodo **r, int v)
{
	Nodo *nuevo=nuevonodo(v);
	Nodo *actual=NULL;
	Nodo *anterior=NULL;
	
	buscar(r, v, &actual, &anterior);
	
	if(actual!=NULL){
		//printf("\n\tEl elemento ya esta en el arbol");
		(actual->cont)++;
	}else{
		if(anterior==NULL){
			*r=nuevo;
		}else{
			if(v<anterior->v){     //Si el elemento es menor que su padre
				anterior->izq=nuevo;
			}else{
				anterior->der=nuevo;
			}
		}
	}
}

/*
void procesarNodo(Nodo* n, int *A, int *i)
Recibe:	*n:	Apuntador a nodo.
		*A:	Apuntador a arreglo.
		*i: Apuntador a entero que marca posición.
Del nodo recibido, añade al arreglo las veces que se repite ese valor.
*/
void procesarNodo(Nodo* n, int *A, int *i)
{
	int j;
	//Se hace este ciclo para contemplar los casos cuando se repite
	for(j=0; j<=n->cont; j++){
		A[*i]=n->v;
		(*i)++;								//Se va recorriendo el arreglo conforme i se incrementa
	}
}

/*
void inOrden(Nodo *n, int *A, int *i)
Recibe:	*n:	Apuntador a nodo.
		*A:	Apuntador a arreglo.
		*i: Apuntador a entero que marca posición.
Realiza el recorrido inOrden del árbol de manera recursiva y llama a la función procesarNodo()
para almacenar los valores en el arreglo A.
*/
void inOrden(Nodo *n, int *A, int *i)
{
	if(n!=NULL){
		inOrden(n->izq, A, i);
		procesarNodo(n, A, i);
		inOrden(n->der, A, i);
	}
}

/*
void imprimir(int *A, int n)
Recibe:	*A: Dirección del arreglo original a ordenar
		 n:	Cantidad/tamaño del arreglo a ordenar
Imprime todos los elementos del arreglo recibido
*/
void imprimir(int *A, int n)
{
	int i, j;
	printf("\n\n  ARREGLO ORDENADO:\n");
	
	for(i=0; i<n; i++)
	{
		printf("\n%d: %d",i,A[i]);
	}
}

/*
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1)
Recibe:	u0:	inicio tiempo usuario
		s0:	inicio tiempo sistema
		w0: inicio tiempo real
		u1: final tiempo usuario
		s1: final tiempo sistema
		w1: final tiempo real
Muestra los resultados del rendimiento temporal dentro de un espacio de tiempo acotado
*/
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1)
{
	// Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  w1 - w0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  u1 - u0);
	printf("sys (Tiempo en acciones de E/S)  %.10f s\n",  s1 - s0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (u1 - u0 + s1 - s0) / (w1 - w0));
	printf("\n");
	
	// Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  w1 - w0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  u1 - u0);
	printf("sys (Tiempo en acciones de E/S)  %.10e s\n",  s1 - s0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (u1 - u0 + s1 - s0) / (w1 - w0));
	printf("\n");
}