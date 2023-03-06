#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tiempos/tiempo.h"

void burbujaOptimizada2(int *A, int n);
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
	printf("\n\n    BURBUJA OPTIMIZADA 1\n    con %d n�meros\n",n);
	
	// Inicia la medici�n de tiempos
	uswtime(&utime0, &stime0, &wtime0);
	// Ejecuci�n del algoritmo de ordenamiento
	burbujaOptimizada2(A, n);
	// Termina la medici�n de tiempos
	uswtime(&utime1, &stime1, &wtime1);

	// Imprime el rendimiento de la ejecuci�n del algoritmo
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);

	// Imprime el arreglo
	imprimir(A, n);
	
	return 1;
}

void burbujaOptimizada2(int *A, int n)
{
	int i=0,j;
	int aux;
	bool cambios = true;
	
	while(i<=n-2 && cambios != false)
	{
		cambios = false;
		// Se ignora la comparaci�n en la �ltima posici�n porque ya sabemos que est� ordenadoa.
		for(j=0; j<=n-2-i; j++)
		{
			if(A[j]>A[j+1])
			{
				aux = A[j];
				A[j] = A[j+1];
				A[j+1] = aux;
				cambios = true;
			}
		}
		i++;
	}
}

void imprimir(int *A, int n)
{
	int i, j;
	printf("\n\n  ARREGLO ORDENADO:\n");
	
	for(i=0; i<n; i++)
	{
		printf("\n%d: %d",i,A[i]);
	}
}

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