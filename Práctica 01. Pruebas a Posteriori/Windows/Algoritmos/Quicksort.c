#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void QuickSort(int *A, int p, int r);
int Pivot(int *A, int p, int r);
void Intercambiar(int *A, int i, int j);
void imprimir(int *A, int n);

int main(int argc, char *argv[])
{
	// Variables para la medici√≥n de tiempos
	clock_t t_inicio, t_final;
	double t_intervalo;

	int i, j, n, *A;

	// Recibir por argumento el tama√±o de n y el valor a buscar
	if (argc != 2)
	{
		printf("\n\n Para compilar el programa se necesita tamanio de arreglo");
		printf("\n Ejemplo: %s 100", argv[0]);
		exit(1);
	}

	// Tomar el argumento del main
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	if (A == NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n", n);
		exit(1);
	}

	// Leer de la entrada est·ndar los n valores y colocarlos en el arreglo de n√∫meros
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	printf("\n\n    QUICKSORT\n   con %d n˙meros",n);
	
	// Inicia mediciÛn del tiempo
	t_inicio = clock();
	// Llamar al algoritmo
	QuickSort(A, 0, n - 1);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	
	imprimir(A, n);
	
	return 0;
}

void QuickSort(int *A, int p, int r)
{
    if (p < r)
    {
        int j = Pivot(A, p, r);
        QuickSort(A, p, j-1);
        QuickSort(A, j+1, r);
    }
}

int Pivot(int *A, int p, int r)
{
    int piv = A[p], i = p+1, j = r;
    do // <-- Es importante que se ejecute por lo menos una vez
    {
        while (A[i] <= piv && i < j) i++;
        while (A[j] > piv) j--;
		// Intercambiar(A, i, j);
        if (i < j) Intercambiar(A, i, j); // <-- Diferencia respecto al pseudo-c√≥digo del profe
    } while (i < j);
    Intercambiar(A, p, j);
    return j;
}

void Intercambiar(int *A, int i, int j)
{
    int temp = A[j];
    A[j] = A[i];
    A[i] = temp;
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
