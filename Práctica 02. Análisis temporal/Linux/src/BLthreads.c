/*
Busqueda Lineal.c
V 1.0 Abril 2022
Autor: Aarón Olvera Martínez

Implementación de la búsqueda lineal en C obtenida en https://www.geeksforgeeks.org/linear-search/
Toma n números enteros de la entrada estándar en la forma:
> BusquedaLineal n k n0 n1 n2 n3 n4 ...  (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo, e imprime la dirección de memoria donde se encontró el valor.
*/

// gcc BLthreads.c -lpthread tiempos/tiempo.c -o BLT
//Ejemplo
// BLT 500000 82182077 < orden10millones.txt

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "tiempos/tiempo.h"

//VARIABLES GLOBALES
//*****************************************************************
int NumThreads = 8;			//Número de threads
int N;						//Tamaño del arreglo
int k;						//Variable a encontrar en el arreglo
int *A;						// Apuntador al arreglo
int p;

int Busqueda(int arr[], int inicio, int fin, int k);
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);
void *procesar(void* id);

int main(int argc, char *argv[])
{
	// Variables para la medición de tiempos.
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	//Obtener el número de threads a usar y el arreglo para la identificacion de los mismos
	//********************************************************************************
	pthread_t *thread;
	// Variable contadora para leer los números
	int i;
	// Verifica si se reciben solo tres argumentos
	if(argc != 3)
	{
		printf("\n\n Para ejecutar el programa se necesita tama%co de arreglo y el n%cmero a buscar",164,163);
		printf("\n Ejemplo: %s 100 23781", argv[0]);
		exit(1);
	}
	// Lee el argumento
	N = atoi(argv[1]);
	A = malloc(N * sizeof(int));
	/// Se lee el argumento del valor a buscar y se añade al elemento auxiliar
	k = atoi(argv[2]);
	// Lee de la entrada estándar los n valores y los coloca en el árbol
	//Aquí falta un tercer argumento Lee el numero de threads a utilizar y reserva su memoria
	thread = malloc(NumThreads*sizeof(pthread_t));
	for (i = 0; i < N; i++)
		scanf("%d", &A[i]);
	// Inicia la medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);
	//Crear los threads con el comportamiento "segmentar"
	for (i=1; i<NumThreads; i++) 
	{
		if (pthread_create (&thread[i], NULL, procesar,(void*)i) != 0 ) 
		{
			perror("El thread no  pudo crearse");
			exit(-1);
		}
	}
	//El main ejecuta el thread 0
	procesar(0);

	//Esperar a que terminen los threads (Saludar)
	for (i=1; i<NumThreads; i++) pthread_join (thread[i], NULL);

	// /*

	printf("\n Valor a encontrar: %d", k);
	if(p == -1){
		printf("\n \033[91mNO SE ENCONTR%c EL N%cMERO\033[0m\n", 224, 233);
	}
	else{
		printf("\n Se encontr%c en la posici%cn: %d\n",162,162, p);
	}

	// */
	// Termina la medición de tiempos
	uswtime(&utime1, &stime1, &wtime1);
	// Imprime el rendimiento de la ejecución del algoritmo
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);

	return 0;
}


int Busqueda(int arr[],int inicio, int fin, int k)
{
	int i;
	for (i = inicio; i < fin; i++)
		if (arr[i] == k)
			return i;
	return -1;
}

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

void* procesar(void* id)
{	
	int n_thread=(int)id;
	int inicio,fin,i,a;
	int resbusqueda;

	//Revisar la parte de los datos a procesar	
	inicio=(n_thread*N)/NumThreads;
	if(n_thread==NumThreads-1)	
		fin=N;
	else
		fin=((n_thread+1)*N)/NumThreads-1;

	printf("\nHola desde procesar\tSoy el thread %d\tInicio %d\tTermino %d",n_thread,inicio,fin);
	resbusqueda = Busqueda(A, inicio, fin, k);
	if(resbusqueda!=-1){
		p = resbusqueda;
		printf("\n Encontrado en el thread %d, %d", n_thread, p);
	}
	
	printf("\nBye desde procesar\tSoy el thread %d\tHe terminado",n_thread);

}
