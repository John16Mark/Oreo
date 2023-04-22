/*
BLthreads.c
V 1.1 Abril 2022
Autor: Aarón Olvera Martínez

Implementación de la búsqueda lineal con threads en C obtenida en https://www.geeksforgeeks.org/linear-search/
Toma n números enteros de la entrada estándar en la forma:
> BLthreads N k Numthreads a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo, e imprime la dirección de memoria donde se encontró el valor.
*/

// gcc BLthreads.c -lpthread tiempos/tiempo.c -o BLthreads
//Ejemplo de ejecución en la terminal BLT 500000 82182077 8 < orden10millones.txt

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "tiempos/tiempo.h"

//VARIABLES GLOBALES
//*****************************************************************
int NumThreads;				//Número de threads
int N;						//Tamaño del arreglo
int k;						//Variable a encontrar en el arreglo
int *A;						// Apuntador al arreglo
int p;

//Funciones
int Busqueda(int *A, int inicio, int fin, int k);
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);
void *procesar(void* id);

int main(int argc, char *argv[])
{
	// Variables para la medición de tiempos.
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	// Arreglo de threads
	pthread_t *thread;
	// Variable contadora para leer los números
	int i;
	// Verifica si se reciben solo cuatro argumentos
	if(argc != 4)
	{
		printf("\n\n Para ejecutar el programa se necesita tama%co de arreglo, el n%cmero a buscar y el n%cmero de hilos que se quieren utilizar",164,163, 163);
		printf("\n Ejemplo: %s 100 23781 4", argv[0]);
		exit(1);
	}
	// Lee el argumento del tamaño del arreglo y reserva su memoria
	N = atoi(argv[1]);
	A = malloc(N * sizeof(int));
	/// Se lee el argumento del valor a buscar y se añade al elemento auxiliar
	k = atoi(argv[2]);
	// Lee el numero de threads a utilizar y reserva su memoria
	NumThreads = atoi(argv[3]);
	thread = malloc(NumThreads*sizeof(pthread_t));
	// Lee de la entrada estándar los n valores y los coloca en el árbol
	for (i = 0; i < N; i++)
		scanf("%d", &A[i]);
	// Inicia la medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);
	//Crear los threads con el comportamiento "segmentar"
	for (i=1; i<NumThreads; i++) 
	{
		//En esta parte es cuando se realiza la búsqueda en los threads 1, ..., a_NumThreads
		if (pthread_create (&thread[i], NULL, procesar,(void*)i) != 0 ) 
		{
			perror("El thread no  pudo crearse");
			exit(-1);
		}
	}
	//El main ejecuta el thread 0
	procesar(0);

	//Esperar a que terminen los threads (procesar)
	for (i=1; i<NumThreads; i++) pthread_join (thread[i], NULL);

	// /*																		Comentar si no se quiere imprimir la posición en donde se encontró

	//Se imprime la posición del arreglo en la que se encontró o, en su defecto, -1 si no se encuentra en arreglo
	printf("\n Valor a encontrar: %d", k);
	if(p == -1){
		printf("\n \033[91mNO SE ENCONTR%c EL N%cMERO\033[0m\n", 224, 233);
	}
	else{
		printf("\n Se encontr%c en la posici%cn: %d\n",162,162, p);
	}

	// */																		Fin comentario
	// Termina la medición de tiempos
	uswtime(&utime1, &stime1, &wtime1);
	// Imprime el rendimiento de la ejecución del algoritmo
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);
	//Libera la memoria del arreglo
	free(A);

	return 0;
}

/*
int Busqueda(int *A,int inicio, int fin, int k)
Recibe:	*A: Dirección del arreglo original a ordenar
		 inicio: Inicio del intervalo del hilo
		 fin: Fin del intervalo del hilo
		 k: Valor a buscar

Compara cada elemento del arreglo A con el valor 
a buscar k. Regresa -1 si no se encuentra.
Se hace una pequeña modificación en el caso de la implementación de los hilos,
para obtener el índice correcto en la búsqueda lineal, se tiene que comenzar a
comparar en el incio del intervalo asignado a cada hilo y terminar en fin.
Complejidad: O(n)
*/
int Busqueda(int *A,int inicio, int fin, int k)
{
	int i;
	for (i = inicio; i < fin; i++)
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

/*
void* procesar(void* id)
Recibe:	id:	id del thread
Hace los clculos necesarios para definir un intervalo dependiendo del número
de hilos que se usen y de su id e imprime el mensaje de la utilización del hilo.
Finalmente, hace la búsqueda y actualiza el valor de p solo si se encontró el
elemento en dicho intervalo.
*/
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

	printf("\nHola desde procesar\tSoy el thread %d\tInicio %d\tTermino %d",n_thread,inicio,fin);	//Comentar para la información del intervalo.
	//Realiza la búsqueda y guarda el valor del índice del arreglo o en su defecto -1.
	resbusqueda = Busqueda(A, inicio, fin, k);
	if(resbusqueda!=-1){
		//Guarda el valor de la búsqueda
		p = resbusqueda;
		printf("\n Encontrado en el thread %d, %d", n_thread, p);									//Comentar para no mostrar el índice.
	}
	
	printf("\nBye desde procesar\tSoy el thread %d\tHe terminado",n_thread);

}
