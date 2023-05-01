/*
BABB.c
V 1.0 Abril 2022
Autor: Aarón Olvera Martínez

Implementación de la búsqueda con ABB en C obtenida en https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
Toma n números enteros de la entrada estándar en la forma:
> BABB n k a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo e imprime el índice del arreglo en el que se encuentra el valor.
*/

//gcc BABBthreads.c -o BABBthreads tiempos/tiempo.c -lm
//Ejemplos para la verificación del funcionamiento
	//./BABBthreads 5000000 1813412181 8 < 10millones.txt			//Debe estar en 3165239
	//./BABBthreads 5000000 865201447 8 < 10millones.txt			//Debe estar en 265

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "tiempos/tiempo.h"
#include <math.h>

/*
Estructura del nodo
 valor: numero que se busca
*izq: dirección del hijo izquierdo
*der: dirección del hijo derecho
 indice: posición del número en el arreglo A (original)
*/
struct nodo {
    int val;
    struct nodo *izq;
	struct nodo *der;
	int indice;
};

//VARIABLES GLOBALES
//*****************************************************************
int NumThreads;				// Número de threads
int N;						// Tamaño del arreglo
int v;						// Variable a encontrar en el arreglo
int *A;						// Apuntador al arreglo
int p;						// Variable para guardar el indice
struct nodo *R = NULL;		// Apuntador a la raiz del arbol
int **B = NULL;				// Apuntador a la matriz para los hilos
int k, c;					// Variables auxiliares para la implementacion de hilos


//Funciones

struct nodo* Busqueda(struct nodo *raiz, int val);
struct nodo* NuevoNodo(int val, int indice);
void inOrden(struct nodo *raiz);
struct nodo* insertar(struct nodo *nodo, int val, int indice);
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);
void* procesar(void* id);

int main(int argc, char *argv[])
{
	// Variables para la medición de tiempos.
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	// Arreglo de threads
	pthread_t *thread;
	// Variables contadoras
	int i, j, l;
	// Variables para la inicializar la matriz para los hilos
	int m, n, d;
	// Verifica si se reciben solo cuatro argumentos
	if(argc != 4)
	{
		printf("\n\n Para ejecutar el programa se necesita tama%co de arreglo y el n%cmero a buscar",164,163);
		printf("\n Ejemplo: %s 100 23781", argv[0]);
		exit(1);
	}
	// Lee el argumento
	N = atoi(argv[1]);
	A = malloc(N * sizeof(int));
	// Se lee el argumento del valor a buscar y se añade al elemento auxiliar
	v = atoi(argv[2]);
	// Lee el numero de threads a utilizar y reserva su memoria
	NumThreads = atoi(argv[3]);
	thread = malloc(NumThreads*sizeof(pthread_t));
	// Se da el valor inicial de -1 a p
	p = -1;
	// Lee de la entrada estándar los n valores y los coloca en el árbol
	scanf("%d", &A[0]);
	R = insertar(R, A[0], 0);
	for (i = 1; i < N; i++){
		scanf("%d", &A[i]);
		insertar(R, A[i], i);
	}
	
	// Inicia la medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);

	//Conocer c y k
	for(i=0; NumThreads>=pow(2,i); i++);			// (Solo se ejecuta lo del parentesis)

	k = i;											// Se define el valor de k
	c = pow(2,k)-NumThreads;						// Se define el valor de c

	// CREACIÓN DE LA MATRIZ PARA LOS HILOS
	//Matriz con base en d y k
	m = pow(2,k);						//Número de filas
	n = k;								//Número de columnas
	B = (int **)malloc(m*sizeof(int*)); 	//Memoria para el numero de filas
	//Tamaño a las filas (numero de columnas)
	for(i=0; i<m; i++){
		B[i] = (int*)malloc(n*sizeof(int));
	}
	// Asignacion de los valores de la matriz de hilos
	for(j=0; j<n; j++){
		d = pow(2, k-1-j);
		for(i=0; i<m; i+=2*d){
			for(l=i; l<d+i; l++){
				B[l][j] = 0;
				B[l+d][j] = 1;
			}
		}
	}

//****************************************************************************
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
//*********************************************************************************************


	// /*																	Comentar si no se quiere imprimir la posición en donde se encontró

	//Se imprime la posición del arreglo en la que se encontró o, en su defecto, -1 si no se encuentra en arreglo
	printf("\n Valor a encontrar: %d", v);
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
	//Libera la memoria de los arreglos y del arbol
	
	free(R);
	R = NULL;
	free(A);
	for(i=0; i<n; i++ ){
	free(B[i]);
	}
	free(B);
	
	return 0;
}

/*
struct nodo* Busqueda(struct nodo* raiz, int val)
Recibe:	
		*raiz: dirección del nodo raiz del árbol
		 val: valor a encontrar

Compara el elemento del nodo raiz y lo compara con el valor a encontrar,
en caso de ser igual a él o el nodo ser null, retorna la dirección del nodo.
En caso de ser el valor del nodo menor, se realiza la búsqueda en su hijo
izquierdo, en caso de ser mayor lo hace con el hijo derecho.
Complejidad: O(log(h))
Con h como la altura del arbol.
*/
struct nodo* Busqueda(struct nodo *raiz, int val){
	// Caso cuando el valor ya fue encontrado
	if(p!=-1)
		return NULL;
	// Casos base: raiz es null o val está en el nodo raiz
    if (raiz == NULL || raiz->val == val)
        return raiz;
    // El valor a buscar es mayor al del nodo
    if (raiz->val < val)
        return Busqueda(raiz->der, val);
 
    // El valor a buscar es menor al del nodo
    return Busqueda(raiz->izq, val);
}

/*
struct nodo* NuevoNodo(int val, int indice)
Recibe:	
		 val: valor con el que se quiere crear el nodo
		 indice: posición del valor en el arreglo A

Crea un nuevo nodo asignanando su valor y posición, además de
inicializar los apuntadores de sus hijos.
Regresa la dirección del nuevo nodo.
*/
struct nodo* NuevoNodo(int val, int indice){
	struct nodo* temp
        = (struct nodo*)malloc(sizeof(struct nodo));
    temp->val = val;
    temp->izq = NULL;
	temp->der = NULL;
	temp->indice = indice;
    return temp;
}

/*
void inOrden(struct nodo* raiz)
Recibe:	
		*raiz: dirección del nodo raiz del árbol

Imprime los valores del nodo en inorden.
Sirve para verificar que se insertaron correctamente los valores en el arbol
*/
void inOrden(struct nodo* raiz){
	if (raiz != NULL) {
        inOrden(raiz->izq);
        printf("%d ", raiz->val);
        inOrden(raiz->der);
    }
}

/*
struct nodo* insertar(struct nodo* nodo, int val, int indice)
Recibe:	
		*raiz: dirección del nodo raiz del árbol
		 val: valor con el que se quiere crear el nodo
		 indice: posición del valor en el arreglo A

Crea un nuevo nodo asignanando su valor y posición, además de
inicializar los apuntadores de sus hijos.
Regresa la dirección del nodo insertado si arbol está vacío.
O regresa la el apuntador al nodo raiz
*/
struct nodo* insertar(struct nodo* nodo, int val, int indice){
	// Si el arbol está vació regresa el nuevo nodo
    if (nodo == NULL)
        return NuevoNodo(val, indice);
 
    // De otra forma, recorre el arbol hacia abajo dependiendo el caso
    if (val < nodo->val)
        nodo->izq = insertar(nodo->izq, val, indice);
    else if (val > nodo->val)
        nodo->der = insertar(nodo->der, val, indice);
 
    // Regresa el apuntador al nodo raiz
    return nodo;
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
Hace los calculos necesarios para definir un intervalo dependiendo del número
de hilos que se usen y de su id e imprime el mensaje de la utilización del hilo.
Finalmente, hace la búsqueda y actualiza el valor de p solo si se encontró el
elemento en dicho intervalo.
*/
void* procesar(void* id)
{	
	int n_thread=(int)id;
	int fila;
	int i, j;
	int noprocesar = 0;
	// Apuntador al nodo encontrado
	struct nodo *encontrado = NULL;
	//Apuntador auxiliar para inicial la busqueda
	struct nodo *aux = R;

	//Revisar la parte de los datos a procesar	
	if(n_thread<(pow(2,k)-2*c)){
		i = 0;
		fila = n_thread;
	}
	else{
		i = 1;
		fila = 2*n_thread - (pow(2,k)-2*c);
	}
		

	for(j=0; j<k-i; j++){
		if(aux==NULL){
			noprocesar = 1;
			break;
		}
		if(aux!=NULL){
			if(aux->val==v){
				encontrado = aux;
				noprocesar = 1;
				break;
			}
			if(B[fila][j]==0){
				aux=aux->izq;
			}else{
				aux=aux->der;
			}
		}
	}

	if(noprocesar==0){
		printf("\nHola desde procesar\tSoy el thread %d\t He comenzado",n_thread);	//Comentar para la información del hilo
	// Ejecución del algoritmo de búsqueda, se le da un valor a entero a "p" (para el resultado final) con base en el resultado de la búsqueda
	encontrado = Busqueda(aux, v);
	if(encontrado != NULL){
		p = encontrado->indice;
		printf("\n Encontrado en el thread %d, %d", n_thread, p);									//Comentar para no mostrar el índice.
	}
	
	printf("\nBye desde procesar\tSoy el thread %d\t He terminado",n_thread);	//Comentar para no mostrar
	}else{
		printf("\nHola desde procesar\tSoy el thread %d NO ME TOCÓ PROCESAR DATOS",n_thread);	//Comentar que no se procesará en ese hilo
		if(encontrado!=NULL){
			p = encontrado->indice;
		}
		printf("\nBye desde procesar\tSoy el thread %d\t He terminado",n_thread);	//Comentar para no mostrar
	}
}
