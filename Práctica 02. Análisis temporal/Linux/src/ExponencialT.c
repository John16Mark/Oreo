/*
ExponencialT.c
V 1.1 Abril 2022
Autores:	Yael André Blásquez Martínez
			Juan Luis Molina Acuña
			Aarón Olvera Martínez
			Paola Reyes Francisco

Implementación de la búsqueda exponencial con threads en C obtenida en https://www.geeksforgeeks.org/exponential-search/
Toma n números enteros de la entrada estándar en la forma:
> ExponencialT n k Numthreads a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo imprime el índice del arreglo en el que se encuentra el valor.

	COMPILAR:
gcc ExponencialT.c -o ExponencialT lib/TADColaDin.c lib/tiempo.c

	EJECUTAR:
./ExponencialT 10000000 4 < 10millones.txt

*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/TADColaDin.h"
#include "lib/tiempo.h"
#include <math.h>

#define min

//VARIABLES GLOBALES
//*****************************************************************
int NumThreads;				// Número de threads
int n;						// Tamaño del arreglo
int k;						// Variable a encontrar en el arreglo
int *A;						// Apuntador al arreglo
int p;						// Variable para guardar el indice

//Funciones
int busquedaExponencial(int *A, int inicio, int final, int k);
int busquedaBinaria(int *A, int l, int r, int k);
void *procesar(void* id);
void cargarArchivo(cola *c, char *direccion);
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);

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
		printf("\n\n Para ejecutar el programa se necesita tamaño de arreglo, y el número de hilos que se quieren utilizar");
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
void busquedaBinaria(int *A, int l, int r, int k)
Recibe:	*A: Dirección del arreglo original a ordenar
		 l: Inicio del rango
		 r: Fin del rango, valor minimo entre los valores i,fina-1
		 k: Valor a buscar
Divide el rango en mitades y compara el valor k con el valor del indice
mitad hasta que se encuentre el valor k o se determine que no esta 
presente en el arreglo. Devuelve la posicion del indice mitad si se 
encuentra, o -1 si no esta presente en el arreglo.
Complejidad: O(log n)
*/
int busquedaBinaria(int *A, int l, int r, int k)
{
    if(r>=l)
    {
    	//Calcula el índice medio del rango
        int mitad = l+(r-l)/2;
 
        //Si el valor k es igual al valor del índice medio del rango
        if(A[mitad]==k)
            return mitad;
            
 		/*Si el valor k es mas pequeño que el valor del índice 
		 medio del rango, entonces k solo puede estar presente 
		 en la mitad izquierda del rango */
        if(A[mitad]>k)
            return busquedaBinaria(A,l,mitad-1,k);
 
        /*Si el valor k es mas grande que el valor del índice 
		 medio del rango, entonces k solo puede estar presente 
		 en la mitad derecha del rango */
        return busquedaBinaria(A,mitad+1,r,k);
    }
 
    //Si el valor no se encuentra en el arreglo
    return -1;
}

/*
void busquedaExponencial(int *A,int inicio, int fin, int k)
Recibe:	*A: Dirección del arreglo original a ordenar
		 inicio: Inicio del intervalo del hilo
		 fin: Fin del intervalo del hilo
		 k: Valor a buscar
Compara el primer elemento con el inicio del intervalo asignado a cada hilo con el valor
a buscar k. Retorna la posicion si es el valor a buscar.
Si no, sumamos una posición a inicio donde el elemento en la posicion del arreglo deberá
ser menor a final y menor o igual al valor a buscar k, esto con la finalidad de encontrar
el rango donde se encuentre nuestro valor k, en cada iteracion el valor i se actualiza
multiplicandolo por 2. Termina cuando encuentra el rango y regresa la posicion del valor
a buscar implementando busqueda binaria.
Complejidad: O(log n)
*/
int busquedaExponencial(int *A, int inicio, int fin, int k)
{
    //Caso base: si k esta en la primera posición
    if(A[inicio]==k)
        return inicio;
 
    int i = 1;
    int posicion = i;

    //Busca el rango donde se encuentra el valor k
    while(posicion<fin&&A[posicion]<=k)
    {
    	i=i*2;
    	posicion = inicio + i;
	}
	
	//Llama a la funcion busquedaBinaria para el rango encontrado
    return busquedaBinaria(A,i/2+posicion,min(i+posicion,fin-1),k);
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
	
	busquedaExponencial(A, inicio, fin, k);
	
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