/*
Busqueda Lineal.c
V 1.1 Abril 2022
Autor: Aarón Olvera Martínez

Implementación de la búsqueda lineal en C obtenida en https://www.geeksforgeeks.org/linear-search/
Toma n números enteros de la entrada estándar en la forma:
> BusquedaLineal n k a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo, e imprime la dirección de memoria donde se encontró el valor.
*/

//gcc BusquedaLineal.c -o BusquedaLineal tiempos/tiempo.c
//BusquedaLineal 500000 82182077 < orden10millones.txt

#include <stdio.h>
#include <stdlib.h>
#include "tiempos/tiempo.h"

int Busqueda(int *A, int n, int k);
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
	// Variable a encontrar en el arreglo
	int k;
	// Variable del índice en el que se encontró el valor
	int p;
	// Verifica si se reciben solo tres argumentos
	if(argc != 3)
	{
		printf("\n\n Para ejecutar el programa se necesita tama%co de arreglo y el n%cmero a buscar",164,163);
		printf("\n Ejemplo: %s 100 23781", argv[0]);
		exit(1);
	}
	// Lee el argumento
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	// Se lee el argumento del valor a buscar y se añade al elemento auxiliar
	k = atoi(argv[2]);
	// Lee de la entrada estándar los n valores y los coloca en el árbol
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	// Inicia la medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);
	// Ejecución del algoritmo de búsqueda
	p = Busqueda(A, n, k);
	
	// /*																	Comentar si no se quiere imprimir la posición en donde se encontró

	//Se imprime la posición del arreglo en la que se encontró o, en su defecto, -1 si no se encuentra en arreglo
	printf("\n Valor a encontrar: %d", k);
	if(p == -1){
		printf("\n \033[91mNO SE ENCONTR%c EL N%cMERO\033[0m\n", 224, 233);
	}
	else{
		printf("\n Se encontr%c en la posici%cn: %d\n",162,162, p);
	}

	// */																	Fin comentario
	// Termina la medición de tiempos
	uswtime(&utime1, &stime1, &wtime1);
	// Imprime el rendimiento de la ejecución del algoritmo
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);
	//Libera la memoria del arreglo
	free(A);
	return 0;
}

/*
int Busqueda(int *A, int n, int k)
Recibe:	*A: Dirección del arreglo original a ordenar
		 n: Numero de elementos en el arreglo
		 k: Valor a buscar

Compara cada elemento del arreglo A con el valor 
a buscar k. Regresa -1 si no se encuentra.
Complejidad: O(n)
*/
int Busqueda(int *A, int n, int k)
{
	int i;
	for (i = 0; i < n; i++)
		if (A[i] == k)
			return i;
	return -1;
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