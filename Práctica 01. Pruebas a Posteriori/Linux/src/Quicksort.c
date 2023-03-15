/*
Quicksort.c
V 1.0 Marzo 2022
Autor: Juan Luis Molina Acuña.

Implementación del ordenamiento rápido en C basada en el pseudocódigo proporcionado por el profesor.
Toma n números enteros de la entrada estándar en la forma:
> Quicksort.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime el tiempo que tomó la ejecución del algoritmo e imprime el arreglo ordenado(opcional).
*/

#include <stdio.h>
#include <stdlib.h>
#include "tiempos/tiempo.h"

void QuickSort(int *A, int p, int r);
int Pivot(int *A, int p, int r);
void Intercambiar(int *A, int i, int j);
void imprimir(int *A, int n);
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
	
	// Verifica si se reciben solo dos argumentos
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
	printf("\n\n    QUICKSORT\n    con %d números\n",n);
	
	// Inicia la medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);
	// Ejecución del algoritmo de ordenamiento
	QuickSort(A, 0, n - 1);
	// Termina la medición de tiempos
	uswtime(&utime1, &stime1, &wtime1);

	// Imprime el rendimiento de la ejecución del algoritmo
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);

	// Imprime el arreglo
	// imprimir(A, n);
	
	return 0;
}

/*
void QuickSort(int *A, int p, int r)
Recibe:	*A: Dirección del arreglo original a ordenar
		 n:	indice desde donde ordenar
		 r: indice hasta donde ordenar
Realiza los cambios en el arreglo original, recursivamente ordena
los elementos de A desde el índice p hasta r de forma ascendente.
Complejidad: O(n log n)
*/
void QuickSort(int *A, int p, int r)
{
    if (p < r)
    {
        int j = Pivot(A, p, r);
        QuickSort(A, p, j-1);
        QuickSort(A, j+1, r);
    }
}

/*
int Pivot(int *A, int p, int r)
Recibe:	*A: Dirección del arreglo original a ordenar
		 p: Pivote, el primer elemento de la región a ordenar
		 r: Límite de la región a ordenar
Coloca todos los elementos menores al pivote a la izquierda y
los mayores a la derecha, después intercambia el pivote para que
quede en su lugar correcto.
Devuelve:
	El indice del pivote después de ordenar la región
*/
int Pivot(int *A, int p, int r)
{
    int piv = A[p], i = p+1, j = r;
    do // <-- Es importante que se ejecute por lo menos una vez
    {
        while (A[i] <= piv && i < j) i++;
        while (A[j] > piv) j--;
		// Intercambiar(A, i, j);
        if (i < j) Intercambiar(A, i, j); // <-- Diferencia respecto al pseudo-cÃ³digo del profe
    } while (i < j);
    Intercambiar(A, p, j);
    return j;
}

/*
void Intercambiar(int *A, int i, int j)
Recibe:*A: Dirección del arreglo
		i: indice elemento a intercambiar con j
		j: indice elemento a intercambiar con i
Realiza el intercambio de los elementos en las posiciones i y j
*/
void Intercambiar(int *A, int i, int j)
{
    int temp = A[j];
    A[j] = A[i];
    A[i] = temp;
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