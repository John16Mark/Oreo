#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void burbujaOptimizada2(int *A, int n);
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
	printf("\n\n    BURBUJA OPTIMIZADA 2\n   con %d números",n);
	// Ejecución del algoritmo de ordenamiento
	
	
	
	t_inicio = clock();
	burbujaOptimizada2(A, n);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	
	
	
	
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
		// Se ignora la comparación en la última posición porque ya sabemos que está ordenadoa.
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
