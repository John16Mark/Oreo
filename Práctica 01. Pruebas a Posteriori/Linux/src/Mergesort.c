/*
Mergesort.c
V 1.0 Marzo 2022
Autor: Juan Luis Molina Acuña.

Implementación del ordenamiento por mezcla en C basada en el pseudocódigo proporcionado por el profesor.
Toma n números enteros de la entrada estándar en la forma:
> Mergesort.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime el tiempo que tomó la ejecución del algoritmo e imprime el arreglo ordenado(opcional).

Compilar desde la carpeta "Linux" de la forma:
gcc -o bin/Mergesort src/Mergesort.c src/tiempos/tiempo.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "tiempos/tiempo.h"

void MergeSort(int A[], int p, int r);
void Merge(int A[],int p, int q, int r);
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
	printf("\n\n    MEZCLA (MERGESORT)\n    con %d números\n",n);
	
	// Inicia la medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);
	// Ejecución del algoritmo de ordenamiento
	MergeSort(A , 0, n-1);
	// Termina la medición de tiempos
	uswtime(&utime1, &stime1, &wtime1);

	// Imprime el rendimiento de la ejecución del algoritmo
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);

	// Imprime el arreglo
	// imprimir(A, n);
	
	return 0;
}

/*
void MergeSort(int *A[], int p, int r)
Recibe:	A[]: Dirección del arreglo
		  p: posición primer elemento
		  r: posición final
Se encarga de dividir el arreglo a la mitad y ordenarlos de manera recursiva.
Complejidad: O(n log n)
*/
void MergeSort(int A[], int p, int r)
{
	int q;

	if (p<r)
	{
		q=(p+r)/2;
		MergeSort(A,p,q);
		MergeSort(A,q+1,r);
		Merge(A,p,q,r);
	}
}

/*
void Merge(int A[], int p, int q, int r)
Recibe:	A[]: Dirección del arreglo
		  p: posición primer elemento
		  q: posición elemento a la mitad
		  r: posición final
Se encarga de remezclar y reunir los subarreglos que se formaron en MergeSort
*/
void Merge(int A[], int p, int q, int r)
{
	int k, l=r-p+1, i=p, j=q+1;
	//int C[l];
	int *C = malloc(l * sizeof(int));
	if (C == NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n", l);
		exit(1);
	}

	for(k=0;k<l;k++)
	{
		if(i<=q&&j<=r)
		{
			if(A[i]<A[j])
			{
				C[k]=A[i];
				i++;
			}
			else
			{
				C[k]=A[j];
				j++;
			}
		}
		else if(i<=q)
		{
			C[k]=A[i];
			i++;
		}
		else
		{
			C[k]=A[j];
			j++;
		}
		//printf("C[%d] = %d\n",k, C[k]);
	}
	for(k=p,i=0;k<=r;k++,i++)
	{
		A[k]=C[i];
	}

	free(C);
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