/*
LinealT.c
V 1.2 Abril 2022
Autores:	Yael André Blásquez Martínez
			Juan Luis Molina Acuña
			Aarón Olvera Martínez
			Paola Reyes Francisco

Implementación de la búsqueda lineal con threads en C obtenida en https://www.geeksforgeeks.org/linear-search/
Toma n números enteros de la entrada estándar en la forma:
> BLthreads N k Numthreads a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmoe imprime el índice del arreglo en el que se encuentra el valor.

	COMPILAR:
gcc LinealT.c -o LinealT lib/TADColaDin.c lib/tiempo.c

	EJECUTAR:
./LinealT 10000000 4 < numeros10millones.txt

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/TADColaDin.h"
#include "lib/tiempo.h"

//VARIABLES GLOBALES
//*****************************************************************
int NumThreads;				// Número de threads
int N;						// Tamaño del arreglo
int k;						// Variable a encontrar en el arreglo
int *A;						// Apuntador al arreglo
int p;						// Variable para guardar el indice

//Funciones
void Busqueda(int *A, int inicio, int fin, int k);
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);
void *procesar(void* id);
void cargarArchivo(cola *c, char *direccion);

// Variables globales para la medición de tiempos.
double u_acumulado = 0, w_acumulado = 0, s_acumulado = 0, p_acumulado = 0;

int main(int argc, char *argv[])
{
	// Arreglo de threads
	pthread_t *thread;
	// Variables para la medición de tiempos.
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	// Variable contadora para leer los números
	int i;
	// Variable para ciclo
	int j;
	// Cola donde se almacenan los valores a buscar
	cola mi_cola;

	// Verifica si se reciben solo tres argumentos
	if(argc != 3)
	{
		printf("\n\n Para ejecutar el programa se necesita tamaño de arreglo y el número de hilos que se quieren utilizar");
		printf("\n Ejemplo: %s 1000000 4", argv[0]);
		exit(1);
	}

	// Lee el argumento del tamaño del arreglo y reserva su memoria
	N = atoi(argv[1]);
	A = malloc(N * sizeof(int));
	// Lee el numero de threads a utilizar y reserva su memoria
	NumThreads = atoi(argv[2]);
	thread = malloc(NumThreads*sizeof(pthread_t));
	// Se da el valor inicial de -1 a p
	p = -1;

	// Lee de la entrada estándar los n valores y los coloca en el arreglo
	for (i = 0; i < N; i++)
		scanf("%d", &A[i]);
	// Lee los números a buscar de la dirección "buscar.txt"
	Initialize(&mi_cola);
	cargarArchivo(&mi_cola, "buscar.txt");

	printf("\n\n    BÚSQUEDA LINEAL\n    con %d números", N);

	// Ejecución del algoritmo de búsqueda
	for(j = 1; j <= Size(&mi_cola); j++){
		k = Element(&mi_cola, j).n;
		p = -1;
		printf("\n\n Valor a encontrar: %d", k);

		// Inicia la medición de tiempos
		uswtime(&utime0, &stime0, &wtime0);
		//Crear los threads con el comportamiento "segmentar"
		for (i=1; i<NumThreads; i++) 
		{
			//En esta parte es cuando se realiza la búsqueda en los threads 1, ..., a_NumThreads
			if (pthread_create (&thread[i], NULL, procesar,(void*)i) != 0 ) 
			{
				perror("El thread no pudo crearse");
				exit(-1);
			}
		}

		//El main ejecuta el thread 0
		procesar(0);
		//Esperar a que terminen los threads (procesar)
		for (i=1; i<NumThreads; i++){
			pthread_join (thread[i], NULL);}

		// Termina la medición de tiempos
		uswtime(&utime1, &stime1, &wtime1);

		// /*											Comentar si no se quiere imprimir la posición en donde se encontró
		//Se imprime la posición del arreglo en la que se encontró o, en su defecto, -1 si no se encuentra en arreglo
		if(p == -1){
			printf("\n \033[91mNO SE ENCONTRÓ EL NÚMERO\033[0m");
		}
		else{
			printf("\n \033[92mSe encontró en la posición:\033[0m %d", p);
		}
		// */											Fin comentario
		rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);
	}
	w_acumulado /= Size(&mi_cola);
	u_acumulado /= Size(&mi_cola);
	s_acumulado /= Size(&mi_cola);
	p_acumulado /= Size(&mi_cola);
	// Cálculo del promedio de medición del algoritmo
	printf("\n\n    PROMEDIO DE MEDICIÓN DE TIEMPOS\n");
	printf("real (Tiempo total)  %.10f s\n",  w_acumulado);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  u_acumulado);
	printf("sys (Tiempo en acciones de E/S)  %.10f s\n",  s_acumulado);
	printf("CPU/Wall   %.10f %% \n", p_acumulado);
	printf("\n");

	// Mostrar los promedios en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  w_acumulado);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  u_acumulado);
	printf("sys (Tiempo en acciones de E/S)  %.10e s\n",  s_acumulado);
	printf("CPU/Wall   %.10f %% \n", p_acumulado);
	printf("\n");

	//Libera la memoria del arreglo
	free(A);

	return 0;
}

/*
void Busqueda(int *A,int inicio, int fin, int k)
Recibe:	*A: Dirección del arreglo original a ordenar
		 inicio: Inicio del intervalo del hilo
		 fin: Fin del intervalo del hilo
		 k: Valor a buscar

Compara cada elemento del arreglo A con el valor 
a buscar k. Termina cuando se encuentra el valor, o cuando se llega al final del intervalo.
Se hace una pequeña modificación en el caso de la implementación de los hilos,
para obtener el índice correcto en la búsqueda lineal, se tiene que comenzar a
comparar en el incio del intervalo asignado a cada hilo y terminar en fin.
Complejidad: O(n)
*/
void Busqueda(int *A,int inicio, int fin, int k)
{
	int i;
	for (i = inicio; i < fin; i++){
		if(p!=-1)
			break;
		if (A[i] == k){
			p = i;
		}
	}
		
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

	w_acumulado += (w1 - w0);
	u_acumulado += (u1 - u0);
	s_acumulado += (s1 - s0);
	p_acumulado += 100.0 * (u1 - u0 + s1 - s0) / (w1 - w0);
}

/*
void* procesar(void* id)
Recibe:	id:	id del thread
Hace los calculos necesarios para definir un intervalo dependiendo del número
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

	//printf("\nHola desde procesar\tSoy el thread %d\tInicio %d\tTermino %d",n_thread,inicio,fin);	//Comentar para la información del intervalo.
	//Realiza la búsqueda y guarda el valor del índice del arreglo o en su defecto -1.
	Busqueda(A, inicio, fin, k);
	
	//printf("\nBye desde procesar\tSoy el thread %d\tHe terminado",n_thread);	//Comentar para no mostrar

}

/*
void cargarArchivo(cola *c, char *direccion)
Recibe:	*c: 		Cola donde se almacenarán los números a buscar
		*direccion:	Dirección del archivo donde están los números
		
Abre un archivo de texto y almacena los números del archivo en una cola.
*/
void cargarArchivo(cola *c, char *direccion)
{
	elemento e;
	FILE *flujo = fopen(direccion, "r");
	size_t len = 0;
	ssize_t read;
	
	if(!flujo){
		printf("\n Error al abrir el archivo: %s", direccion);
		exit(1);
	}
	
	//Lee línea por línea el archivo de texto y los almacena en la cola
	char line[500];
	while (fgets(line, sizeof(line), flujo)){
		e.n = atoi(line);
		Queue(c,e);
	}
    
	fclose(flujo);
	return;
}