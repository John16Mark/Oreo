/*
Treesort.c
V 1.0 Marzo 2022
Autor: Yael Andr� Blazquez Mart�nez, Aar�n Olvera Mart�nez.

Implementaci�n del ordenamiento por �rbol binario en C.
Toma n n�meros enteros de la entrada est�ndar en la forma:
> mezcla.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime el tiempo que tom� la ejecuci�n del algoritmo e imprime el arreglo ordenado(opcional).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
struct Nodo
Contiene:
	int v				n�mero almacenado
	struct Nodo *izq	apuntador a nodo, hijo izquierdo
	struct Nodo *der	apuntador a nodo, hijo derecho
	int cont 			veces que se repite el n�mero almacenado
*/
typedef struct Nodo {
	int v;
	struct Nodo *izq;
	struct Nodo *der;
	int cont;
} Nodo;

// Funciones del �rbol
Nodo *nuevonodo(int v);
void buscar(Nodo **r, int v, Nodo **actual, Nodo **anterior);
void insertar(Nodo **r, int v);
void procesarNodo(Nodo* n, int *A, int *i);
void inOrden(Nodo* n, int *A, int *i);
// Ordenamiento
void TreeSort(int *A, int n);
// Imprimir arreglo
void imprimir(int *A, int n);
// Mostrar estad�sticas
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);

int main(int argc, char *argv[])
{
	// Variables para la medici�n de tiempos
	clock_t t_inicio, t_final;
	double t_intervalo;
	int i, n;
	int *A;
	
	if(argc != 2)
	{
		printf("\n\n Para compilar el programa se necesita tamanio de arreglo");
		printf("\n Ejemplo: %s 100", argv[0]);
		exit(1);
	}
	// Lee el argumento y crea un arreglo con el tama�o recibido
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	if (A == NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n", n);
		exit(1);
	}
	// Lee de la entrada est�ndar los n valores y los coloca en el arreglo
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	printf("\n\n    TREESORT\n    con %d n�meros\n",n);
	
	// Ejecuci�n del algoritmo de ordenamiento
	t_inicio = clock();
	TreeSort(A,n);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	
	// Imprime el arreglo
	// imprimir(A, n);
	
	return 1;
}

/*
void TreeSort(int *A, int n)
Recibe:	*A: Direcci�n del arreglo original a ordenar
		 n:	Cantidad/tama�o del arreglo a ordenar
Crea el nodo ra�z y una variable que marca la posici�n de hasta d�nde se ha llenado el arreglo
Inserta todos los valores de A en el �rbol, y los realmacena usando el recorrdo InOrden
*/
void TreeSort(int *A, int n)
{
	int i;
	Nodo *r = NULL;
	
	for(i=0; i<n; i++){
		insertar(&r, A[i]);
	}
	
	i=0;
	inOrden(r, A, &i);
}


void imprimir(int *A, int n)
{
	int i, j;
	printf("\n\n  ARREGLO ORDENADO:\n");
	
	for(i=0; i<n; i++)
	{
		printf("\n%d: %d",i,A[i]);
	}
}

//Funciones arbol

/*
Nodo *nuevonodo(int v)
Recibe:
	v: N�mero a acomodar.
Crea un nuevo nodo que ser� a�adido al �rbol
Regresa:
	Nodo creado dentro de la funci�n
*/
Nodo *nuevonodo(int v)
{
	Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
	if(nuevo==NULL){
		printf("No se gener� correctamente el nodo");
		exit(1);
	}	
	nuevo->v=v;
	nuevo->der=NULL;
	nuevo->izq=NULL;
	nuevo->cont=0;
	return nuevo; //<- Preguntarle al profe
}

/*
void buscar(Nodo **r, int v, Nodo **actual, Nodo **anterior)
Recibe:	  **r:	Apuntador a nodo ra�z.
			v:	Valor a buscar
     **actual:	Apuntador al apuntador del nodo actual
   **anterior:	Apuntador al apuntador del nodo padre
Revisa si el valor recibido ya existe en el �rbol. Actualiza el padre de un nuevo nodo.
*/
void buscar(Nodo **r, int v, Nodo **actual, Nodo **anterior)
{
	*anterior = NULL;
	*actual=*r;
	int encontrado=0;
	
	
	while( !encontrado && *actual!=NULL){
		
		if(v==(*actual)->v){
			encontrado=1;
		}else{
			*anterior=*actual;			//Se recorre al nodo padre
			if(v<(*actual)->v){			//Si v es menor que el valor del nodo
				*actual=(*actual)->izq;		//Se ubica en el hijo izquierdo
			}else{
				*actual=(*actual)->der;		//Se ubica en el hijo derecho
			}
		}
		
	}

}

/*
void insertar(Nodo **r, int v)
Recibe:	**r:	Apuntador a nodo ra�z.
		  v:	Valor a buscar
De un nodo creado en la funci�n nuevonodo(v), llama a la funci�n buscar para saber si a�adir en la ra�z y para actualizar
al padre del nodo nuevo. Posteriormente, a�ade el nodo en su posici�n correcta.
*/
void insertar(Nodo **r, int v)
{
	Nodo *nuevo=nuevonodo(v);
	Nodo *actual=NULL;
	Nodo *anterior=NULL;
	
	buscar(r, v, &actual, &anterior);
	
	if(actual!=NULL){
		//printf("\n\tEl elemento ya esta en el arbol");
		(actual->cont)++;
	}else{
		if(anterior==NULL){
			*r=nuevo;
		}else{
			if(v<anterior->v){     //Si el elemento es menor que su padre
				anterior->izq=nuevo;
			}else{
				anterior->der=nuevo;
			}
		}
	}
}

/*
void procesarNodo(Nodo* n, int *A, int *i)
Recibe:	*n:	Apuntador a nodo.
		*A:	Apuntador a arreglo.
		*i: Apuntador a entero que marca posici�n.
Del nodo recibido, a�ade al arreglo las veces que se repite ese valor.
*/
void procesarNodo(Nodo* n, int *A, int *i)
{
	int j;
	//Se hace este ciclo para contemplar los casos cuando se repite
	for(j=0; j<=n->cont; j++){
		A[*i]=n->v;
		(*i)++;								//Se va recorriendo el arreglo conforme i se incrementa
	}
}

/*
void inOrden(Nodo *n, int *A, int *i)
Recibe:	*n:	Apuntador a nodo.
		*A:	Apuntador a arreglo.
		*i: Apuntador a entero que marca posici�n.
Realiza el recorrido inOrden del �rbol de manera recursiva y llama a la funci�n procesarNodo()
para almacenar los valores en el arreglo A.
*/
void inOrden(Nodo *n, int *A, int *i)
{
	if(n!=NULL){
		inOrden(n->izq, A, i);
		procesarNodo(n, A, i);
		inOrden(n->der, A, i);
	}
}
