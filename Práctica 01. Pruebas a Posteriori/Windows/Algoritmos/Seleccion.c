/*
Seleccion.c
V 1.0 Marzo 2022
Autor: Juan Luis Molina Acu�a.

Implementaci�n del ordenamiento por Selecci�n en C basada en el pseudoc�digo proporcionado por el profesor.
Toma n n�meros enteros de la entrada est�ndar en la forma:
> Seleccion.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime el tiempo que tom� la ejecuci�n del algoritmo e imprime el arreglo ordenado(opcional).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Seleccion(int *A, int n);
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
	printf("\n\n    SELECCI�N\n   con %d n�meros",n);
	
	// Ejecuci�n del algoritmo de ordenamiento
	t_inicio = clock();
	Seleccion(A, n);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	
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
