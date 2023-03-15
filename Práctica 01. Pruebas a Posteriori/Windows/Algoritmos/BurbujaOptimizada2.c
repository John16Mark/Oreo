/*
BurbujaOptimizada2.c
V 1.0 Marzo 2022
Autor: Paola Reyes Francisco.

Implementaci�n del ordenamiento burbuja con optimizaci�n en cantidad de comparaciones y evitar
iteraciones innecesarias en C basada en el pseudoc�digo proporcionado por el profesor.
Toma n n�meros enteros de la entrada est�ndar en la forma:
> BurbujaOptimizada2.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime el tiempo que tom� la ejecuci�n del algoritmo e imprime el arreglo ordenado(opcional).
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void burbujaOptimizada2(int *A, int n);
void imprimir(int *A, int n);

int main(int argc, char *argv[])
{
	// Variables para la medici�n de tiempos
	clock_t t_inicio, t_final;
	double t_intervalo;
	int i, n;
	int *A;
	
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
	printf("\n\n    BURBUJA OPTIMIZADA 2\n   con %d n�meros",n);

	// Ejecuci�n del algoritmo de ordenamiento
	t_inicio = clock();
	burbujaOptimizada2(A, n);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	
	// Imprime el arreglo
	// imprimir(A, n);
	
	return 1;
}

/*
void burbujaOptimizada2(int *A, int n)
Recibe:	*A: Direcci�n del arreglo original a ordenar
		 n:	Cantidad/tama�o del arreglo a ordenar
Ordena el arreglo A de tama�o n mediante el algoritmo de la burbuja con dos optimizaciones
Complejidad: O(n^2)
*/
void burbujaOptimizada2(int *A, int n)
{
	int i=0,j;
	int aux;
	bool cambios = true;
	
	// Deja de iterar si llega al final o si detecta que en una iteraci�n no hizo cambios
	while(i<=n-2 && cambios != false)
	{
		cambios = false;
		// Se ignoran las comparaciones en las �ltimas posiciones que ya sabemos que est�n acomodadas.
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
