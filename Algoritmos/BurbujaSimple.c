#include <stdio.h>
#include <stdlib.h>

void burbujaSimple(int *A, int n);
void imprimir(int *A, int n);

int main(int argc, char *argv[])
{
	int i, n;
	int *A;
	
	if(argc != 2)
	{
		printf("\n\n Para compilar el programa se necesita tamanio de arreglo");
		printf("\n Ejemplo: [user@equipo]$ %s 100", argv[0]);
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
	printf("\n\n    BURBUJA SIMPLE\n   con %d números",n);
	// Ejecución del algoritmo de ordenamiento
	burbujaSimple(A, n);
	// Imprime el arreglo
	imprimir(A, n);
	
	
	return 1;
}

void burbujaSimple(int *A, int n)
{
	int i,j;
	int aux;
	
	for(i=0; i<=n-2; i++)
	{
		for(j=0; j<=n-2; j++)
		{
			if(A[j]>A[j+1])
			{
				aux = A[j];
				A[j] = A[j+1];
				A[j+1] = aux;
			}
		}
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
