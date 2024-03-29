/*
ArbolBinario.c
V 1.2 Abril 2023
Autores:	Yael André Blásquez Martínez
			Juan Luis Molina Acuña
			Aarón Olvera Martínez
			Paola Reyes Francisco

Implementación de la búsqueda con ABB en C obtenida en https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
Toma n números enteros de la entrada estándar en la forma:
> ArbolBinario n a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo e imprime el índice del arreglo en el que se encuentra el valor.

	COMPILAR:
gcc src/ArbolBinario.c -o bin/ArbolBinario lib/tiempo.c -lm -w

	EJECUTAR:
./bin/ArbolBinario 5000000 < numeros10millones.txt

*/

#include <stdio.h>
#include <stdlib.h>
#include "lib/TADColaDin.h"
#include "lib/tiempo.h"

/*
Estructura del nodoC
 valor: numero que se busca
*izq: dirección del hijo izquierdo
*der: dirección del hijo derecho
 indice: posición del número en el arreglo A (original)
*/
struct nodoC {
    int val;
    struct nodoC *izq;
	struct nodoC *der;
	int indice;
};

//Funciones

struct nodoC* Busqueda(struct nodoC *raiz, int val);
struct nodoC* NuevoNodo(int val, int indice);
void inOrden(struct nodoC *raiz);
struct nodoC* insertar(struct nodoC *nodoC, int val, int indice);
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);
void cargarArchivo(cola *c, char *direccion);

// Variables globales para la medición de tiempos.
double u_acumulado = 0, w_acumulado = 0, s_acumulado = 0, p_acumulado = 0;

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
	// Cola donde se almacenan los valores a buscar
	cola mi_cola;
	// Variable a encontrar en el arreglo
	int k;
	// Variable del índice en el que se encontró el valor
	int p;
	// Apuntador a la raiz del arbol
	struct nodoC *raiz = NULL;
	// Apuntador al nodoC encontrado
	struct nodoC *encontrado = NULL;
	// Verifica si se reciben solo tres argumentos
	if(argc != 2)
	{
		printf("\n\n Para ejecutar el programa se necesita tamaño de arreglo");
		printf("\n Ejemplo: %s 100", argv[0]);
		exit(1);
	}
	// Lee el argumento
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	// Lee de la entrada estándar los n valores y los coloca en el árbol
	scanf("%d", &A[0]);
	raiz = insertar(raiz, A[0], 0);
	for (i = 1; i < n; i++){
		scanf("%d", &A[i]);
		insertar(raiz, A[i], i);
	}

	// Lee los números a buscar de la dirección "buscar.txt"
	Initialize(&mi_cola);
	cargarArchivo(&mi_cola, "buscar.txt");

	printf("\n\n    BÚSQUEDA CON ÁRBOL BINARIO\n    con %d números", n);

	// Ciclo para cada elemento de la cola
	for(i = 1; i <= Size(&mi_cola); i++){
		k = Element(&mi_cola, i).n;
		printf("\n\n Valor a encontrar: %d", k);

		// Inicia la medición de tiempos
		uswtime(&utime0, &stime0, &wtime0);
		// Ejecución del algoritmo de búsqueda, se le da un valor a entero a "p" (para el resultado final) con base en el resultado de la búsqueda
		encontrado = Busqueda(raiz, k);
		if(encontrado == NULL)
			p = -1;
		else
			p = encontrado->indice;
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

	/*
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
		printf("\n \033[91mNO SE ENCONTRÓ EL NÚMERO\033[0m\n");
	}
	else{
		printf("\n Se encontró en la posición: %d\n", p);
	}

	// *//*																	Fin comentario
	// Termina la medición de tiempos
	uswtime(&utime1, &stime1, &wtime1);
	// Imprime el rendimiento de la ejecución del algoritmo
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);
	*/

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

	//Libera la memoria del arreglo y del arbol
	free(raiz);
	raiz = NULL;
	free(A);

	return 0;
}

/*
struct nodoC* Busqueda(struct nodoC* raiz, int val)
Recibe:	
		*raiz: dirección del nodoC raiz del árbol
		 val: valor a encontrar

Compara el elemento del nodoC raiz y lo compara con el valor a encontrar,
en caso de ser igual a él o el nodoC ser null, retorna la dirección del nodoC.
En caso de ser el valor del nodoC menor, se realiza la búsqueda en su hijo
izquierdo, en caso de ser mayor lo hace con el hijo derecho.
Complejidad: O(log(h))
Con h como la altura del arbol.
*/
struct nodoC* Busqueda(struct nodoC *raiz, int val){
	// Casos base: raiz es null o val está en el nodoC raiz
    if (raiz == NULL || raiz->val == val)
        return raiz;
 
    // El valor a buscar es mayor al del nodoC
    if (raiz->val < val)
        return Busqueda(raiz->der, val);
 
    // El valor a buscar es menor al del nodoC
    return Busqueda(raiz->izq, val);
}

/*
struct nodoC* NuevoNodo(int val, int indice)
Recibe:	
		 val: valor con el que se quiere crear el nodoC
		 indice: posición del valor en el arreglo A

Crea un nuevo nodoC asignanando su valor y posición, además de
inicializar los apuntadores de sus hijos.
Regresa la dirección del nuevo nodoC.
*/
struct nodoC* NuevoNodo(int val, int indice){
	struct nodoC* temp = (struct nodoC*)malloc(sizeof(struct nodoC));
    temp->val = val;
    temp->izq = NULL;
	temp->der = NULL;
	temp->indice = indice;
    return temp;
}

/*
void inOrden(struct nodoC* raiz)
Recibe:	
		*raiz: dirección del nodoC raiz del árbol

Imprime los valores del nodoC en inorden.
Sirve para verificar que se insertaron correctamente los valores en el arbol
*/
void inOrden(struct nodoC* raiz){
	if (raiz != NULL) {
        inOrden(raiz->izq);
        printf("%d ", raiz->val);
        inOrden(raiz->der);
    }
}

/*
struct nodoC* insertar(struct nodoC* nodoC, int val, int indice)
Recibe:	
		*raiz: dirección del nodoC raiz del árbol
		 val: valor con el que se quiere crear el nodoC
		 indice: posición del valor en el arreglo A

Crea un nuevo nodoC asignanando su valor y posición, además de
inicializar los apuntadores de sus hijos.
Regresa la dirección del nodoC insertado si arbol está vacío.
O regresa la el apuntador al nodoC raiz
*/
struct nodoC* insertar(struct nodoC* nodoC, int val, int indice){
	// Si el arbol está vació regresa el nuevo nodoC
    if (nodoC == NULL)
        return NuevoNodo(val, indice);
 
    // De otra forma, recorre el arbol hacia abajo dependiendo el caso
    if (val < nodoC->val)
        nodoC->izq = insertar(nodoC->izq, val, indice);
    else if (val > nodoC->val)
        nodoC->der = insertar(nodoC->der, val, indice);
 
    // Regresa el apuntador al nodoC raiz
    return nodoC;
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
