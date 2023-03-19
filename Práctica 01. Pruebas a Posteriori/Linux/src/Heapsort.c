/*
Heapsort.c
V 1.0 Marzo 2022
Autor: Yael André Blazquez Martínez, Aarón Olvera Martínez.

Implementación del ordenamiento por montículo en C.
Toma n números enteros de la entrada estándar en la forma:
> Heapsort.exe n n0 n1 n2 n3 n4 ...  (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo e imprime el arreglo ordenado(opcional).

Compilar desde la carpeta "Linux" de la forma:
gcc -o bin/Heapsort src/Heapsort.c src/tiempos/tiempo.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "tiempos/tiempo.h"

/*
struct Heap
Contiene:
	int* num		arreglo de números
	int tam 		indica cuántos elementos lleva almacenados en el montículo
	int capacidad	indica la capacidad máxima del montículo
*/
typedef struct Heap{
    int* num;
    int tam;
    int capacidad;
} Heap;

// Funciones del montículo
void intercambiar(int* a, int* b);
void heapify_down(Heap* heap, int i);
void heapify_up(Heap* heap, int i);
void insertar(Heap* heap, int valor);
int extraer(Heap* heap);
// Ordenamiento
void HeapSort(int *A, int n);
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
	printf("\n\n    HEAPSORT\n    con %d números\n",n);
	
	// Inicia la medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);
	// Ejecución del algoritmo de ordenamiento
	HeapSort(A,n);
	// Termina la medición de tiempos
	uswtime(&utime1, &stime1, &wtime1);

	// Imprime el rendimiento de la ejecución del algoritmo
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);
	
	// Imprime el arreglo
	// imprimir(A, n);
	
	return 1;
}

/*
void HeapSort(int *A, int n)
Recibe:	*A: Dirección del arreglo original a ordenar
		 n:	Cantidad/tamaño del arreglo a ordenar
Crea el montículo, lo inicializa, inserta todos los números del arreglo dentro
de la estructura y finalmente los extrae ya ordenados.
*/
void HeapSort(int *A, int n)
{
	int i;
	Heap heap = {
        .num = (int*)malloc(sizeof(int) * n),			//Por n, que es el tamaño del heap
        .tam = 0,
        .capacidad = n
    };
	
	for(i=0; i<n; i++){
		insertar(&heap, A[i]);
	}
	
	for(i=0; i<n; i++){
		A[i]=extraer(&heap);
	}
}

/*
void intercambiar(int* a, int* b)
Recibe:	*a: Dirección del primer valor
		*b: Dirección del segundo valor
Realiza el intercambio de los elementos a y b
*/
void intercambiar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
void heapify_down(Heap* heap, int i)
Recibe:	*heap: 	Dirección del heap
		*i: 	Posición del número a comparar
Crea una variable (smallest) para almacenar la posición del número más pequeño (inicia en la cima).
Realiza una serie comparaciones con sus hijos para obtener la posición correcta y finalmente intercambia la cima
con este número. Esto lo hace de manera recursiva hasta que llegue al fondo.
*/
void heapify_down(Heap* heap, int i) {
    int hijo_izq = 2 * i + 1;
    int hijo_der = 2 * i + 2;
    int smallest = i;

    if (hijo_izq < heap->tam && heap->num[hijo_izq] < heap->num[smallest]) {
        smallest = hijo_izq;
    }

    if (hijo_der < heap->tam && heap->num[hijo_der] < heap->num[smallest]) {
        smallest = hijo_der;
    }

    if (smallest != i) {
        intercambiar(&heap->num[i], &heap->num[smallest]);
        heapify_down(heap, smallest);
    }
}

/*
void insertar(Heap* heap, int valor)
Recibe:	*heap: 	Dirección del heap
		valor: 	Valor del número a añadir
Pregunta si llegó a la capacidad máxima que cabe dentro de la estructura. Si no ha llegado, añade el número hasta abajo.
Posteriormente revisa si su posición es correcta con la función heapify_up.
*/
void insertar(Heap* heap, int valor) {
    if (heap->tam < heap->capacidad) {
        heap->num[heap->tam] = valor;
        heap->tam++;
        heapify_up(heap, heap->tam - 1);
    }
}

/*
void heapify_up(Heap* heap, int i)
Recibe:	*heap: 	Dirección del heap
		*i: 	Posición del número a comparar
Calcula quién es el padre del número y compara cuál es mayor; si el hijo es menor, los intercambia
Realiza la operación de manera recursiva hasta que llegue lo más arriba que puede
*/
void heapify_up(Heap* heap, int i) {
    int padre = (i - 1) / 2;

    if (i > 0 && heap->num[i] < heap->num[padre]) {
        intercambiar(&heap->num[i], &heap->num[padre]);
        heapify_up(heap, padre);
    }
}

/*
int extraer(Heap* heap)
Recibe:
	*heap: 	Dirección del heap
Toma el número más pequeño del montículo (posición 0) y pone en su lugar el más grande (última posición).
Posteriormente reacomoda los números con la función heapidy_down
Regresa:
	int min_valor:	Número más pequeño dentro del montículo.
*/
int extraer(Heap* heap) {
    if (heap->tam == 0) {
        //printf("El montículo está vacío.\n");
        return -1;
    }

    int min_valor = heap->num[0];
    heap->num[0] = heap->num[heap->tam - 1];
    heap->tam--;
    heapify_down(heap, 0);

    return min_valor;
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
