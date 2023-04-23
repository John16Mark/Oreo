/*
BABB.c
V 1.0 Abril 2022
Autor: Aarón Olvera Martínez

Implementación de la búsqueda con ABB en C obtenida en https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
Toma n números enteros de la entrada estándar en la forma:
> BABB n k a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo e imprime el índice del arreglo en el que se encuentra el valor.
*/

//gcc BABB.c -o BABB tiempos/tiempo.c
//BABB 5000000 1813412181 < 10millones.txt			//Debe estar en 3165239

#include <stdio.h>
#include <stdlib.h>
#include "tiempos/tiempo.h"

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

//Funciones

struct nodo* Busqueda(struct nodo *raiz, int val);
struct nodo* NuevoNodo(int val, int indice);
void inOrden(struct nodo *raiz);
struct nodo* insertar(struct nodo *nodo, int val, int indice);
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
	// Apuntador a la raiz del arbol
	struct nodo *raiz = NULL;
	// Apuntador al nodo encontrado
	struct nodo *encontrado = NULL;
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
	scanf("%d", &A[0]);
	raiz = insertar(raiz, A[0], 0);
	for (i = 1; i < n; i++){
		scanf("%d", &A[i]);
		insertar(raiz, A[i], i);
	}
	
	// Inicia la medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);
	// Ejecución del algoritmo de búsqueda, se le da un valor a entero a "p" (para el resultado final) con base en el resultado de la búsqueda
	encontrado = Busqueda(raiz, k);
	if(encontrado == NULL)
		p = -1;
	else
		p = encontrado->indice;


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
	//Libera la memoria del arreglo y del arbol
	free(raiz);
	raiz = NULL;
	free(A);

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
