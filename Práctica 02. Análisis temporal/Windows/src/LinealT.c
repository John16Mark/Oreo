/*
BusquedaLinealT.c
V 1.2 Abril 2022
Autores:	Aarón Olvera Martínez
			Juan Luis Molina Acuña

Implementación de la búsqueda lineal con threads en C obtenida en https://www.geeksforgeeks.org/linear-search/
Toma n números enteros de la entrada estándar en la forma:
> BusquedaLinealT n k Numthreads a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo imprime el índice del arreglo en el que se encuentra el valor.

	COMPILAR:
gcc BusquedaLinealT.c -o BusquedaLinealT.exe lib/TADColaDin.c

	EJECUTAR:
BusquedaLinealT.exe 10000000 4 < numeros10millones.txt

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/TADColaDin.h"
#include <time.h>

//VARIABLES GLOBALES
//*****************************************************************
int NumThreads;				// Número de threads
int n;						// Tamaño del arreglo
int k;						// Variable a encontrar en el arreglo
int *A;						// Apuntador al arreglo
int p;						// Variable para guardar el indice

//Funciones
void Busqueda(int *A, int inicio, int fin, int k);
void *procesar(void* id);
void cargarArchivo(cola *c, char *direccion);

int main(int argc, char *argv[])
{
	// Arreglo de threads
	pthread_t *thread;
	// Variables para la medición de tiempos
	clock_t t_inicio, t_final;
	double t_intervalo;
	double t_acumulado = 0;
	// Variable contadora para leer los números
	int i;
	// Variable para ciclo
	int j;
	// Cola donde se almacenan los valores a buscar
	cola mi_cola;
	// Verifica si se reciben solo cuatro argumentos
	if(argc != 3)
	{
		printf("\n\n Para ejecutar el programa se necesita tama%co de arreglo, y el n%cmero de hilos que se quieren utilizar",164, 163);
		printf("\n Ejemplo: %s 100 4", argv[0]);
		exit(1);
	}
	// Lee el argumento del tamaño del arreglo y reserva su memoria
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	// Lee el numero de threads a utilizar y reserva su memoria
	NumThreads = atoi(argv[2]);
	thread = malloc(NumThreads*sizeof(pthread_t));
	// Se da el valor inicial de -1 a p
	p = -1;
	
	// Lee de la entrada estándar los n valores y los coloca en el arreglo
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	
	// Lee los números a buscar de la dirección "buscar.txt"
	Initialize(&mi_cola);
	cargarArchivo(&mi_cola, "buscar.txt");
	
	// Ejecución del algoritmo de búsqueda
	for(j = 1; j <= Size(&mi_cola); j++){
		k = Element(&mi_cola, j).n;
		p = -1;
		
		printf("\n\n Valor a encontrar: %d", k);
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

		// Inicia la medición de tiempos
		t_inicio = clock();

		//El main ejecuta el thread 0
		procesar(0);
		//Esperar a que terminen los threads (procesar)
		for (i=1; i<NumThreads; i++){
			pthread_join (thread[i], NULL);}

		// Termina la medición de tiempos
		t_final = clock();
		t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
		t_acumulado += t_intervalo;

		// /*											Comentar si no se quiere imprimir la posición en donde se encontró
		//Se imprime la posición del arreglo en la que se encontró o, en su defecto, -1 si no se encuentra en arreglo
		if(p == -1){
			printf("\n \033[91mNO SE ENCONTR%c EL N%cMERO\033[0m", 224, 233);
		}
		else{
			printf("\n \033[92mSe encontr%c en la posici%cn:\033[0m %d",162,162, p);
		}
		// */											Fin comentario
		printf("\n Tiempo medido: %.8f segundos.\n", t_intervalo);
	}
	t_acumulado /= Size(&mi_cola);
	printf("\n\n    PROMEDIO DE MEDICI%cN DE TIEMPOS\n    %.8f segundos.\n", 224, t_acumulado);
	
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
	inicio=(n_thread*n)/NumThreads;
	if(n_thread==NumThreads-1)	
		fin=n;
	else
		fin=((n_thread+1)*n)/NumThreads-1;

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
