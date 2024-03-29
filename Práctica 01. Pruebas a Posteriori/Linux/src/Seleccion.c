/*
Seleccion.c
V 1.0 Marzo 2022
Autor: Juan Luis Molina Acu�a.

Implementaci�n del ordenamiento por Selecci�n en C basada en el pseudoc�digo proporcionado por el profesor.
Toma n n�meros enteros de la entrada est�ndar en la forma:
> Seleccion.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime el tiempo que tom� la ejecuci�n del algoritmo e imprime el arreglo ordenado(opcional).

Compilar desde la carpeta "Linux" de la forma:
gcc -o bin/Seleccion src/Seleccion.c src/tiempos/tiempo.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "tiempos/tiempo.h"

void Seleccion(int *A, int n);
void imprimir(int *A, int n);
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);

int main(int argc, char *argv[])
{
	// Variables para la medici�n de tiempos.
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	// Variable para determinar la longitud del arreglo
	int n;
	// Variable contadora para leer los n�meros
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
	// Lee el argumento y crea un arreglo con el tama�o recibido
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	if (A == NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n", n);
		exit(1);
	}
	// Lee de la entrada est�ndar los n valores y los coloca en el arreglo
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	printf("\n\n    SELECCI�N\n    con %d n�meros\n",n);
	
	// Inicia la medici�n de tiempos
	uswtime(&utime0, &stime0, &wtime0);
	// Ejecuci�n del algoritmo de ordenamiento
	Seleccion(A, n);
	// Termina la medici�n de tiempos
	uswtime(&utime1, &stime1, &wtime1);

	// Imprime el rendimiento de la ejecuci�n del algoritmo
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);
	
	// Imprime el arreglo
	// imprimir(A, n);
	
	return 1;
}

/*
void Seleccion(int *A, int n)
Recibe:	*A: Direcci�n del arreglo original a ordenar
		 n:	Cantidad/tama�o del arreglo a ordenar
Ordena el arreglo A de tama�o n mediante el algoritmo de selecci�n
Complejidad: O(n^2)
*/
void Seleccion(int *A, int n)
{
	int i,k,p;
	int temp;
	
	for(k=0; k<=n-2; k++)
	{
		p=k;
		for(i=k+1; i<=n-1; i++)
		{
			if(A[i]<A[p])
			{
				p = i;
			}
		}
		temp = A[p];
		A[p] = A[k];
		A[k] = temp;
	}
}

/*
void imprimir(int *A, int n)
Recibe:	*A: Direcci�n del arreglo original a ordenar
		 n:	Cantidad/tama�o del arreglo a ordenar
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
	// C�lculo del tiempo de ejecuci�n del programa
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