/*
Mergesort.c
V 1.0 Marzo 2022
Autor: Juan Luis Molina Acuña.

Implementación del ordenamiento por mezcla en C basada en el pseudocódigo proporcionado por el profesor.
Toma n números enteros de la entrada estándar en la forma:
> Mergesort.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime el tiempo que tomó la ejecución del algoritmo e imprime el arreglo ordenado(opcional).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MergeSort(int A[], int p, int r);
void Merge(int A[],int p, int q, int r);
void imprimir(int *A, int n);

int main(int argc, char *argv[])
{
	// Variables para la medición de tiempos
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
	printf("\n\n    MERGESORT\n   con %d números",n);
	
	// Ejecución del algoritmo de ordenamiento
	t_inicio = clock();
	MergeSort(A,0,n-1);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	
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
void MergeSort(int *A[], int p, int r)
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
void Merge(int *A[], int p, int q, int r)
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
