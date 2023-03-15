#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Nodo
{

int v;									//Valor
struct Nodo *izq;					 	//hijo izquierdo
struct Nodo *der;						//hijo derecho
int cont;								//Numero de veces que se REPITE el valor en el arreglo
}Nodo;

//Funciones arbol

Nodo *nuevonodo(int v);
void buscar(Nodo **r, int v, Nodo **actual, Nodo **anterior);
void insertar(Nodo **r, int v);
void procesarNodo(Nodo* n, int *A, int *i);
void inOrden(Nodo* n, int *A, int *i);

//Ordenamiento
void OrdenABB(int *A, int n);

//Imprimir arreglo
void imprimir(int *A, int n);

int main(int argc, char *argv[])
{
	// Variables para la medición de tiempos
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
	// Lee el argumento y crea un arreglo con el tamaño recibido
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	if (A == NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n", n);
		exit(1);
	}
	// Lee de la entrada estándar los n valores y los coloca en el arreglo
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	printf("\n\n    ORDENABB\n   con %d números",n);
	// Ejecución del algoritmo de ordenamiento
	
	
	
	t_inicio = clock();
	OrdenABB(A,n);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	
	
	
	
	// Imprime el arreglo
	imprimir(A, n);
	
	
	return 1;
}

void OrdenABB(int *A, int n)
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

Nodo *nuevonodo(int v){
	Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
	if(nuevo==NULL){
		printf("No se generó correctamente el nodo");
		exit(1);
	}	
	nuevo->v=v;
	nuevo->der=NULL;
	nuevo->izq=NULL;
	nuevo->cont=0;
}

void buscar(Nodo **r, int v, Nodo **actual, Nodo **anterior){
	
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

void insertar(Nodo **r, int v){
	
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

void procesarNodo(Nodo* n, int *A, int *i){
	int j;
	//Se hace este ciclo para contemplar los casos cuando se repite
	for(j=0; j<=n->cont; j++){
		A[*i]=n->v;
		(*i)++;								//Se va recorriendo el arreglo conforme i se incrementa
	}
}

void inOrden(Nodo *n, int *A, int *i){
	if(n!=NULL){
		inOrden(n->izq, A, i);
		procesarNodo(n, A, i);
		inOrden(n->der, A, i);
	}
}
