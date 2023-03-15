/*
Quicksort.c
V 1.0 Marzo 2022
Autor: Juan Luis Molina Acu�a.

Implementaci�n del ordenamiento r�pido en C basada en el pseudoc�digo proporcionado por el profesor.
Toma n n�meros enteros de la entrada est�ndar en la forma:
> Quicksort.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime el tiempo que tom� la ejecuci�n del algoritmo e imprime el arreglo ordenado(opcional).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void QuickSort(int *A, int p, int r);
int Pivot(int *A, int p, int r);
void Intercambiar(int *A, int i, int j);
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
	printf("\n\n    QUICKSORT\n   con %d n�meros",n);
	
	// Ejecuci�n del algoritmo de ordenamiento
	t_inicio = clock();
	QuickSort(A, 0, n - 1);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	
	// Imprime el arreglo
	// imprimir(A, n);
	
	return 0;
}

/*
void QuickSort(int *A, int p, int r)
Recibe:	*A: Direcci�n del arreglo original a ordenar
		 n:	indice desde donde ordenar
		 r: indice hasta donde ordenar
Realiza los cambios en el arreglo original, recursivamente ordena
los elementos de A desde el �ndice p hasta r de forma ascendente.
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
Recibe:	*A: Direcci�n del arreglo original a ordenar
		 p: Pivote, el primer elemento de la regi�n a ordenar
		 r: L�mite de la regi�n a ordenar
Coloca todos los elementos menores al pivote a la izquierda y
los mayores a la derecha, despu�s intercambia el pivote para que
quede en su lugar correcto.
Devuelve:
	El indice del pivote despu�s de ordenar la regi�n
*/
int Pivot(int *A, int p, int r)
{
    int piv = A[p], i = p+1, j = r;
    do // <-- Es importante que se ejecute por lo menos una vez
    {
        while (A[i] <= piv && i < j) i++;
        while (A[j] > piv) j--;
		// Intercambiar(A, i, j);
        if (i < j) Intercambiar(A, i, j); // <-- Diferencia respecto al pseudo-código del profe
    } while (i < j);
    Intercambiar(A, p, j);
    return j;
}

/*
void Intercambiar(int *A, int i, int j)
Recibe:*A: Direcci�n del arreglo
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
