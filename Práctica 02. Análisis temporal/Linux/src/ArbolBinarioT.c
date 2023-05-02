/*
ArbolBinarioT.c
V 1.0 Abril 2022
Autor: Aarón Olvera Martínez

Implementación de la búsqueda con ABB con hilos en C obtenida en https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
Toma n números enteros de la entrada estándar en la forma:
> ArbolBinarioT n k a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo e imprime el índice del arreglo en el que se encuentra el valor.
*/

//gcc ArbolBinarioT.c -o ArbolBinarioT lib/tiempo.c -lm -w
//Ejemplos para la verificación del funcionamiento
	//./bin/ArbolBinarioT 5000000 1813412181 8 < numeros10millones.txt			//Debe estar en 3165239
	//./bin/ArbolBinarioT 5000000 865201447 8 < numeros10millones.txt			//Debe estar en 265

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/TADColaDin.h"
#include "lib/tiempo.h"
#include <math.h>

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

//VARIABLES GLOBALES
//*****************************************************************
int NumThreads;				// Número de threads
int N;						// Tamaño del arreglo
int v;						// Variable a encontrar en el arreglo
int *A;						// Apuntador al arreglo
int p;						// Variable para guardar el indice
struct nodoC *R = NULL;		// Apuntador a la raiz del arbol
int **B = NULL;				// Apuntador a la matriz para los hilos
int k, c;					// Variables auxiliares para la implementacion de hilos


//Funciones

struct nodoC* Busqueda(struct nodoC *raiz, int val);
struct nodoC* NuevoNodo(int val, int indice);
void inOrden(struct nodoC *raiz);
struct nodoC* insertar(struct nodoC *nodoC, int val, int indice);
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);
void* procesar(void* id);
void cargarArchivo(cola *c, char *direccion);

// Variables globales para la medición de tiempos.
double u_acumulado = 0, w_acumulado = 0, s_acumulado = 0, p_acumulado = 0;

int main(int argc, char *argv[])
{
	// Variables para la medición de tiempos.
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	// Arreglo de threads
	pthread_t *thread;
	// Variables contadoras
	int i, j, l;
	// Cola donde se almacenan los valores a buscar
	cola mi_cola;
	// Variables para la inicializar la matriz para los hilos
	int m, n, d;

	// Verifica si se reciben solo cuatro argumentos
	if(argc != 3)
	{
		printf("\n\n Para ejecutar el programa se necesita tamaño de arreglo y el número de hilos que se quieren utilizar");
		printf("\n Ejemplo: %s 100 8\n", argv[0]);
		exit(1);
	}

	// Lee el argumento
	N = atoi(argv[1]);
	A = malloc(N * sizeof(int));
	// Lee el numero de threads a utilizar y reserva su memoria
	NumThreads = atoi(argv[2]);
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
	
	// Lee los números a buscar de la dirección "buscar.txt"
	Initialize(&mi_cola);
	cargarArchivo(&mi_cola, "buscar.txt");

	printf("\n\n    BÚSQUEDA CON ÁRBOL BINARIO\n    con %d números y %d hilos", N, NumThreads);

	/*
	Para asignar hilos a ciertos nodos del árbol:
	Se buscan los valores k y c utilizados para crear una "tabla de combinaciones" con ceros y unos,
	que en el algoritmo representa las combinaciones posibles para llegar a cada nodoC del árbol
	encontrado en el nivel k. Así, por ejemplo, si se eligen 8 hilos k=3, por 2^k=8. Si el numero
	de hilos no es una potencia de 2, se toma el número de k, al elegir el menor 2^k que es mayor
	al número de hilos, como ejemplo, si son 5 hilos k = 3, puesto que se utilizarán algunos de los
	nodos que pertenecen al nivel k. 
	
	Ahora bien, se ocupa otra variable llamada C, que nos servirá
	en caso de que el número de hilos no sea una potencia de 2, para poder elegir nodos del nivel
	superior utilizando la tabla de combinaciones.
	El numero de hilos se puede expresar como

	NumThreads=2^k-c   ---- Ecuación para obtener c despejando

	C también sirve para no repetir combinaciones el el nivel superior (como se explica en la
	función void* procesar(void* id))
	*/
	for(i=0; NumThreads>=pow(2,i); i++);			// (Solo se ejecuta lo del parentesis)

	k = i;											// Se define el valor de k
	c = pow(2,k)-NumThreads;						//NumThreads=2^k-c   ---- Ecuación para obtener C despejando

	// CREACIÓN DE LA MATRIZ PARA LOS HILOS (tabla de combinaciones)
		/*Matriz con base en d, k y l (Utlizando memoria dinámica)
		En donde k: número de filas
				 d: variable auxiliar para llenar TODA la columna
				 l: variable auxiliar para llenar un conjunto de 0...1...
			Por ejemplo, si se tiene una matriz que 2^k filas y k columnas
			Para llenar la primera columna, el número de valores unos o ceros consecutivos es d=2^(k-1)
			En el mismo ejemplo, al llenar la columna 2, d=2^(k-2)
			De manera generalizada d=2^(k-1-j) para 0<=j<n
		*/
	m = pow(2,k);												// Número de filas
	n = k;														// Número de columnas
	B = (int **)malloc(m*sizeof(int*)); 						// Memoria para el numero de filas
	//Tamaño a las filas (numero de columnas)
	for(i=0; i<m; i++){
		B[i] = (int*)malloc(n*sizeof(int));
	}
	// Asignacion de los valores de la tabla de combinaciones
	for(j=0; j<n; j++){
		d = pow(2, k-1-j);
		for(i=0; i<m; i+=2*d){				//Salto de 2*d porque ya se llenaron los unos
			for(l=i; l<d+i; l++){
				B[l][j] = 0;				// Asigna los ceros
				B[l+d][j] = 1;				// Asigna los unos consecutivos a los ceros
			}
		}
	}

	
	// Ejecución del algoritmo de búsqueda
	for(j = 1; j <= Size(&mi_cola); j++){
		v = Element(&mi_cola, j).n;
		p = -1;
		printf("\n\n Valor a encontrar: %d", v);

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
		// *//*											Fin comentario
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
	// Caso cuando el valor ya fue encontrado
	if(p!=-1)
		return NULL;
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
	struct nodoC* temp
        = (struct nodoC*)malloc(sizeof(struct nodoC));
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
void* procesar(void* id)
Recibe:	id:	id del thread
Hace los calculos necesarios para seleccionar el nodoC raiz del subárbol en donde
trabajará el hilo seleccionado e imprime el mensaje de la utilización del hilo.
Finalmente, hace la búsqueda y actualiza el valor de p solo si se encontró el
elemento en dicho intervalo.
*/
void* procesar(void* id)
{	
	int n_thread=(int)id;						// Número de hilo
	int fila;									// Fila de la combinación correspondiente al hilo
	int i, j;									// Variables contadoras
	int noprocesar = 0;							// Dentiene la búsqueda si se encuentra el valor o aux apunta a NULL
	// Apuntador para guardar el nodoC en donde se encontró el valor
	struct nodoC *encontrado = NULL;
	//Apuntador auxiliar para iniciar la busqueda
	struct nodoC *aux = R;

	//Revisar la parte de los datos a procesar	
	if(n_thread<(pow(2,k)-2*c)){
		i = 0;									// Si es del nivel k, se toman todos los valores de la combinación
		fila = n_thread;
	}
	else{
		i = 1;									// Si es del nivel k-1, no se toma el último valor de la combinación
		fila = 2*n_thread - (pow(2,k)-2*c);					// Cálculo de la fila (se toma la primera)
	}
		
	//Ciclo para recorrer el árbol y posicionarse en el nodoC en donde se iniciará la búsqueda
	for(j=0; j<k-i; j++){
		// Caso donde no hay valores en el subárbol
		if(aux==NULL){
			noprocesar = 1;									// Indica que no se realizará la búsqueda
			break;
		}
		// Caso donde si hay valores en el subárbol
		if(aux!=NULL){
			//Caso donde el valor se encontró en el proceso
			if(aux->val==v){
				encontrado = aux;							//Asigna el valor en donde se encontró
				noprocesar = 1;								// Indica que no se realizará la búsqueda
				break;
			}
			// Caso elegir hijo izquierdo
			if(B[fila][j]==0){
				aux=aux->izq;
			}
			// Caso elegir hijo derecho
			else{
				aux=aux->der;
			}
		}
	}

	// Caso en donde se indicó que se debía procesar
	if(noprocesar==0){
		//printf("\nHola desde procesar\tSoy el thread %d\t He comenzado",n_thread);	//Comentar para la información del hilo
		// Ejecución del algoritmo de búsqueda, se le da un valor entero a "p" (para el resultado final) con base en el resultado de la búsqueda
		encontrado = Busqueda(aux, v);
		// Caso en el que si se encontró
		if(encontrado != NULL){
			p = encontrado->indice;
			//printf("\n Encontrado en el thread %d, %d", n_thread, p);									//Comentar para no mostrar el índice.
		}
		
		//printf("\nBye desde procesar\tSoy el thread %d\t He terminado",n_thread);	//Comentar para no mostrar
	}
	// Caso en donde se indicó que no se debía procesar
	else{
		//printf("\nHola desde procesar\tSoy el thread %d NO ME TOCÓ PROCESAR DATOS",n_thread);	//Comentar que no se procesará en ese hilo
		if(encontrado!=NULL){
			p = encontrado->indice;
		}
		//printf("\nBye desde procesar\tSoy el thread %d\t He terminado",n_thread);	//Comentar para no mostrar
	}
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