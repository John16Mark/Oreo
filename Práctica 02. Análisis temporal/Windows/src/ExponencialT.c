/*
ExponencialT.c
V 1.2 Abril 2022
Autores:	Paola Reyes Francisco
Implementaci�n de la b�squeda exponencial con threads en C obtenida en https://www.geeksforgeeks.org/exponential-search/
Toma n n�meros enteros de la entrada est�ndar en la forma:
> ExponencialT n k Numthreads a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tom� la ejecuci�n del algoritmo imprime el �ndice del arreglo en el que se encuentra el valor.
	COMPILAR:
gcc ExponencialT.c -o ExponencialT.exe lib/TADColaDin.c
	EJECUTAR:
ExponencialT.exe 10000000 4 < ordenados10millones.txt
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/TADColaDin.h"
#include <time.h>
#include <math.h>
#define min

//VARIABLES GLOBALES
//*****************************************************************
int NumThreads;				// N�mero de threads
int n;						// Tama�o del arreglo
int k;						// Variable a encontrar en el arreglo
int *A;						// Apuntador al arreglo
int p;						// Variable para guardar el indice

//Funciones
void busquedaExponencial(int *A, int inicio, int final, int k);
void busquedaBinaria(int *A, int l, int r, int k);
void *procesar(void* id);
void cargarArchivo(cola *c, char *direccion);

int main(int argc, char *argv[])
{
	// Arreglo de threads
	pthread_t *thread;
	// Variables para la medici�n de tiempos
	clock_t t_inicio, t_final;
	double t_intervalo;
	double t_acumulado = 0;
	// Variable contadora para leer los n�meros
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
	// Lee el argumento del tama�o del arreglo y reserva su memoria
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	// Lee el numero de threads a utilizar y reserva su memoria
	NumThreads = atoi(argv[2]);
	thread = malloc(NumThreads*sizeof(pthread_t));
	// Se da el valor inicial de -1 a p
	p = -1;
	
	// Lee de la entrada est�ndar los n valores y los coloca en el arreglo
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	
	// Lee los n�meros a buscar de la direcci�n "buscar.txt"
	Initialize(&mi_cola);
	cargarArchivo(&mi_cola, "buscar.txt");
	
	// Ejecuci�n del algoritmo de b�squeda
	for(j = 1; j <= Size(&mi_cola); j++){
		k = Element(&mi_cola, j).n;
		p = -1;
		
		printf("\n\n Valor a encontrar: %d", k);
		//Crear los threads con el comportamiento "segmentar"
		for (i=1; i<NumThreads; i++) 
		{
			//En esta parte es cuando se realiza la b�squeda en los threads 1, ..., a_NumThreads
			if (pthread_create (&thread[i], NULL, procesar,(void*)i) != 0 ) 
			{
				perror("El thread no pudo crearse");
				exit(-1);
			}
		}

		// Inicia la medici�n de tiempos
		t_inicio = clock();

		//El main ejecuta el thread 0
		procesar(0);
		//Esperar a que terminen los threads (procesar)
		for (i=1; i<NumThreads; i++){
			pthread_join (thread[i], NULL);}

		// Termina la medici�n de tiempos
		t_final = clock();
		t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
		t_acumulado += t_intervalo;

		// /*											Comentar si no se quiere imprimir la posici�n en donde se encontr�
		//Se imprime la posici�n del arreglo en la que se encontr� o, en su defecto, -1 si no se encuentra en arreglo
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
void busquedaBinaria(int *A, int l, int r, int k)
Recibe:	*A: Direcci�n del arreglo original a ordenar
		 l: Inicio del rango
		 r: Fin del rango
		 k: Valor a buscar
Compara cada elemento del arreglo A con el valor 
a buscar k. Termina cuando se encuentra el valor, o cuando se llega al final del intervalo.
Se hace una peque�a modificaci�n en el caso de la implementaci�n de los hilos,
para obtener el �ndice correcto en la b�squeda lineal, se tiene que comenzar a
comparar en el incio del intervalo asignado a cada hilo y terminar en fin.
Complejidad: O(log n)
*/
void busquedaBinaria(int *A, int l, int r, int k)
{
    while (l <= r) {
    	
        int medio = l + (r - l) / 2;

		if(p!=-1)
			break;

        if (A[medio] == k)
            p = medio;
 
        if (A[medio] < k)
            l = medio +1;
 
        else
            r = medio - 1;
    }
}

/*
void busquedaExponencial(int *A,int inicio, int fin, int k)
Recibe:	*A: Direcci�n del arreglo original a ordenar
		 inicio: Inicio del intervalo del hilo
		 fin: Fin del intervalo del hilo
		 k: Valor a buscar
Complejidad: O(log n)
*/
void busquedaExponencial(int *A, int inicio, int fin, int k)
{
 
    if(A[inicio]==k)
        p = inicio;
 					
    int i = 1;

    while(p != -1 && i<fin && A[inicio+i]<=k)
    {
    	
		i=i*2;
	}
	
    busquedaBinaria(A,inicio + i/2,min(inicio + i,fin-1),k);
}

/*
void* procesar(void* id)
Recibe:	id:	id del thread
Hace los calculos necesarios para definir un intervalo dependiendo del n�mero
de hilos que se usen y de su id e imprime el mensaje de la utilizaci�n del hilo.
Finalmente, hace la b�squeda y actualiza el valor de p solo si se encontr� el
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

	//printf("\nHola desde procesar\tSoy el thread %d\tInicio %d\tTermino %d",n_thread,inicio,fin);	//Comentar para la informaci�n del intervalo.
	
	//Realiza la b�squeda y guarda el valor del �ndice del arreglo o en su defecto -1.
	
	busquedaExponencial(A, inicio, fin, k);
	
	//printf("\nBye desde procesar\tSoy el thread %d\tHe terminado",n_thread);	//Comentar para no mostrar

}

/*
void cargarArchivo(cola *c, char *direccion)
Recibe:	*c: 		Cola donde se almacenar�n los n�meros a buscar
		*direccion:	Direcci�n del archivo donde est�n los n�meros
		
Abre un archivo de texto y almacena los n�meros del archivo en una cola.
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
	
	//Lee l�nea por l�nea el archivo de texto y los almacena en la cola
	char line[500];
	while (fgets(line, sizeof(line), flujo)){
		e.n = atoi(line);
		Queue(c,e);
	}
    
	fclose(flujo);
	return;
}
