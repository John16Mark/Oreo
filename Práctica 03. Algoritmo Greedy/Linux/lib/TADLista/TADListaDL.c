/*
IMPLEMENTACIONES DE LA LIBRERIA DEL TAD LISTA (TADLista.h)
AUTOR: Juan Luis Molina Acu�a - Enero 2023
VERSI�N: 1.0

Frente                                                       Final
	 ******    ******    ******    ******    ******    ******
 NULL <- *    * <- *    * <- *    * <- *    * <- *    * <- *    *
	 * N1 *    * N2 *    * N3 *    * N4 *    * N5 *    * N6 *
	 *    * -> *    * -> *    * -> *    * -> *    * -> *    * -> NULL
	 ******    ******    ******    ******    ******    ******    

COMPILACIÓN PARA GENERAR EL CÓDIGO OBJETO: gcc TADListaSL.c -c 
*/

//LIBRER�AS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TADListaDL.h"
/***************************************************************************************
								OPERACIONES DE CONSTRUCCI�N
***************************************************************************************/
void Initialize(lista *l){
	l -> frente = NULL;
	l -> final = NULL;
	l -> tam = 0;
	return;
}

void Destroy(lista *l){
	posicion aux; 
	aux = l->frente; 
	while(aux!=NULL)
	{
		l->frente = aux->siguiente; 
		free(aux); 
		aux = l->frente; 
	}
	l->final=NULL; 
	l->tam=0; 
	return;
}
/***************************************************************************************
								OPERACIONES DE MODIFICACI�N
***************************************************************************************/
void Add (lista *l, elemento e){
	posicion aux;
	aux=malloc(sizeof(nodo));
	if(aux==NULL){
		printf("ERROR: Add(lista *l, elemento e)\n       desbordamiento de lista");
		exit(1);}

	aux->e = e;
	aux->ramaIzq = NULL;
	aux->ramaDer = NULL;
	if(l->tam>0){
		aux->anterior = l->final;
		l->final->siguiente=aux;
	}else{
		aux->anterior = NULL;
		l->frente=aux;
	}
	l->final=aux;
	l->final->siguiente = NULL;
	l->tam++;
	return;
}

void Insert (lista *l, posicion p, elemento e, boolean b)
{
	posicion aux, aux2;
	aux=malloc(sizeof(nodo));
	if(aux==NULL){
		printf("ERROR: Insert(lista *l, posicion p, elemento e, boolean b)\n       Desbordamiento de lista.");
		exit(1);
	}
	aux->e=e;
	aux->ramaIzq = NULL;
	aux->ramaDer = NULL;
	if(ValidatePosition(l,p)){
		//Enfrente de p
		if(b){
			aux2=Previous(l,p);
			//p es el frente, se inserta al frente de la lista
			if(aux2==NULL){
				aux->anterior=NULL;
				p->anterior = aux;
				aux->siguiente=l->frente;
				l->frente=aux;
			}
			//Si p no era el frente de la lista
			else{
				aux->anterior=aux2;
				aux2->siguiente=aux;
				p->anterior=aux;
				aux->siguiente=p;
			}
		}
		//Atras de p
		else{
			aux2=Following(l,p);
			//p es el final, se inserta al final de la lista
			if(aux2==NULL){
				aux->anterior=p;
				p->siguiente=aux;
				l->final=aux;
				aux->siguiente=NULL;
			}
			//Si p no era el frente de la lista
			else{
				aux->anterior=p;
				aux2->anterior=aux;
				p->siguiente=aux;
				aux->siguiente=aux2;
			}
		}
	}
	//si p es invalido, se inserta el elemento enfrente
	else{
		aux->siguiente=l->frente;
		l->frente=aux;
		if(l->tam==0){
			l->final=aux;}
	}
	l->tam++;
	return;
}

void InsertIn(lista *l, elemento e, int n)
{
	posicion aux=l->frente;
	int i = 0;
	if(n >= l->tam || n < 0){
		printf ("ERROR: InsertInPosition(lista *l, elemento e, int n)\n       n inv%clido", 160);
		exit (1);
	}

	while(i<n){
		i++;
		aux=aux->siguiente;
	}

	posicion aux2;
	aux2=malloc(sizeof(nodo));
	if(aux2==NULL){
		printf("ERROR: InsertInPosition(lista *l, elemento e, int n)\n       Desbordamiento de lista.");
		exit(1);
	}

	aux2->e = e;
	aux2->ramaIzq = NULL;
	aux2->ramaDer = NULL;
	aux2->siguiente = aux;

	if(aux->anterior != NULL){
		aux2->anterior = Previous(l, aux);
		posicion aux3 = Previous(l, aux);
		aux3->siguiente = aux2;
	}
	else{
		aux2->anterior = NULL;
		l->frente = aux2;
	}
	aux->anterior = aux2;
	l->tam++;
}

void InsertNodoIn(lista *l, nodo newNodo, int n)
{
	posicion aux=l->frente;
	int i = 0;
	if(n >= l->tam || n < 0){
		printf ("ERROR: InsertInPosition(lista *l, elemento e, int n)\n       n inv%clido", 160);
		exit (1);
	}

	while(i<n){
		i++;
		aux=aux->siguiente;
	}

	posicion aux2;
	aux2=malloc(sizeof(nodo));
	if(aux==NULL){
		printf("ERROR: Add(lista *l, elemento e)\n       desbordamiento de lista");
		exit(1);}

	aux2->e = newNodo.e;
	aux2->ramaIzq = newNodo.ramaIzq;
	aux2->ramaDer = newNodo.ramaDer;
	aux2->anterior = NULL;
	aux2->siguiente = NULL;
	posicion aux3;
	
	aux2->siguiente = aux;
	if(aux->anterior != NULL){
		aux2->anterior = Previous(l, aux);
		aux3 = Previous(l, aux);
		aux3->siguiente = aux2;
	}else{
		aux2->anterior = NULL;
		l->frente = aux2;
	}

	aux->anterior = aux2;
	l->tam++;
}

void InsertNodoIn2 (lista *l, posicion p, nodo newNodo, boolean b)
{
	posicion aux, aux2;
	aux=malloc(sizeof(nodo));
	if(aux==NULL){
		printf("ERROR: Insert(lista *l, posicion p, elemento e, boolean b)\n       Desbordamiento de lista.");
		exit(1);
	}
	aux->e=newNodo.e;
	aux->ramaIzq = newNodo.ramaIzq;
	aux->ramaDer = newNodo.ramaDer;
	if(ValidatePosition(l,p)){
		//Enfrente de p
		if(b){
			aux2=Previous(l,p);
			//p es el frente, se inserta al frente de la lista
			if(aux2==NULL){
				aux->anterior=NULL;
				p->anterior = aux;
				aux->siguiente=l->frente;
				l->frente=aux;
			}
			//Si p no era el frente de la lista
			else{
				aux->anterior=aux2;
				aux2->siguiente=aux;
				p->anterior=aux;
				aux->siguiente=p;
			}
		}
		//Atras de p
		else{
			aux2=Following(l,p);
			//p es el final, se inserta al final de la lista
			if(aux2==NULL){
				aux->anterior=p;
				p->siguiente=aux;
				l->final=aux;
				aux->siguiente=NULL;
			}
			//Si p no era el frente de la lista
			else{
				aux->anterior=p;
				aux2->anterior=aux;
				p->siguiente=aux;
				aux->siguiente=aux2;
			}
		}
	}
	//si p es invalido, se inserta el elemento enfrente
	else{
		aux->siguiente=l->frente;
		l->frente=aux;
		if(l->tam==0){
			l->final=aux;}
	}
	l->tam++;
	return;
}

void Remove(lista *l, posicion p)
{
	posicion aux,aux2;
	if (!ValidatePosition(l,p))
	{
		printf ("ERROR: Remove(lista *l, posicion p)\n       p es invalida");
		exit (1);
	}	
	if (p==l->frente)
	{
		l->frente=p->siguiente;
		l->frente->anterior=NULL;
	}
	else if (p==l->final)
	{
		aux=Previous (l,p);
		aux->siguiente=NULL;
		l->final=aux;
	}
	else
	{
		aux=Previous (l,p);
		aux2=Following(l,p);
		aux->siguiente = p->siguiente;
		aux2->anterior = p->anterior;
	}
	free (p);
	l->tam--;
	if (l->tam==0)
		l->final=NULL;
	return;
}

void Replace (lista *l,posicion p, elemento e)
{
	if(ValidatePosition(l,p)){
		p->e=e;
	}else{
		printf("ERROR: Replace(l,p,e) Posición invalida");
		exit(1);
	}
	return;
}

nodo Dequeue(lista *l)
{
	posicion aux;
	nodo NO;
	elemento e; //Elemento a retornar 
	if(l->tam == 0){
		printf("ERROR: Dequeue(lista *l)\n        Subdesbordamiento de lista");
		exit(1);
	}else {
		if(l->tam > 1){
			posicion aux2 = First(l)->siguiente;
			aux2->anterior = NULL;
		}
		
		aux = l->frente;
		l->frente = l->frente->siguiente;
		l->tam--;
		if(l->tam==0)
			l->final=NULL;
	}

	//Retornar al elemento
	return *aux;
}

posicion DequeuePos(lista *l)
{
	posicion aux;
	nodo NO;
	elemento e; //Elemento a retornar 
	if(l->tam == 0){
		printf("ERROR: Dequeue(lista *l)\n        Subdesbordamiento de lista");
		exit(1);
	}else {
		if(l->tam > 1){
			posicion aux2 = First(l)->siguiente;
			aux2->anterior = NULL;
		}
		
		aux = l->frente;
		l->frente = l->frente->siguiente;
		l->tam--;
		if(l->tam==0)
			l->final=NULL;
	}

	//Retornar la posición
	return aux;
}

nodo PopNodoIn(lista *l, int n)
{
	posicion aux=l->frente;
	int i = 0;
	if(n >= l->tam || n < 0){
		printf ("ERROR: PopNodoIn(lista *l, elemento e, int n)\n       n inv%clido", 160);
		exit (1);
	}

	while(i<n){
		i++;
		aux=aux->siguiente;
	}

	posicion aux2, aux3;
	aux2=malloc(sizeof(nodo));
	aux3=malloc(sizeof(nodo));
	if(aux2==NULL || aux3==NULL){
		printf("ERROR: Add(lista *l, elemento e)\n       desbordamiento de lista");
		exit(1);}

	aux2=Previous(l, aux);
	aux3=Following(l,aux);

	if(aux2 != NULL){
		if(aux3 != NULL){
			aux3->anterior = aux2;}
	}else{
		if(aux3 != NULL){
			aux3->anterior = NULL;}
		l->frente = aux3;
	}
	//printf("TRUENA");
	if(aux3 != NULL){
		if(aux2 != NULL){
			aux2->siguiente = aux3;}
	}else{
		if(aux2 != NULL){
			aux2->siguiente = NULL;}
		l->final = aux2;
	}

	l->tam--;
	return *aux;
}

void SelectionSort(lista *l){
	posicion aux, aux2, aux3;
	nodo NEWNODO;
	aux=malloc(sizeof(nodo));
	aux2=malloc(sizeof(nodo));
	aux3=malloc(sizeof(nodo));
	if(aux==NULL || aux2==NULL || aux3==NULL){
		printf("ERROR: SelectionSort(lista *l)\n       desbordamiento de lista");
		exit(1);}

	int i, j;
	int indice;
	int n = Size(l);

	for(i = 0; i < n-1; i++){
		indice = i;
		for(j = i+1; j < n; j++){
			if(Element(l, j).frecuencia < Element(l, indice).frecuencia){
				indice = j;
			}
		}
		//temp = A[indice]
		NEWNODO = PopNodoIn(l, indice);
		//A[indice] = A[i]
		InsertNodoIn(l, NEWNODO, i);
	}
}

/***************************************************************************************
						OPERACIONES DE POSICIONAMIENTO Y B�SQUEDA
***************************************************************************************/
posicion Final (lista *l)
{
	return l->final;
}

posicion First (lista *l)
{
	return l->frente;
}

posicion Following (lista *l,posicion p)
{
	if(ValidatePosition(l,p))
		return p->siguiente;
	printf("ERROR:Following(L,p) la posicion es invalida");
	exit(1);
}

posicion Previous (lista *l,posicion p)
{
	if(ValidatePosition(l,p))
		return p->anterior;
	printf("ERROR: Previous(lista *l, posicion p)\n       la posicion es invalida");
	exit(1);
}
/***************************************************************************************
									OPERACIONES DE CONSULTA
***************************************************************************************/
int Size (lista *l)
{
	return l->tam;
}

boolean Empty (lista *l)
{
	boolean r;
	if(l->tam==0)
		r=TRUE;
	else
		r=FALSE;
	return r;
}

elemento Element(lista *l, int n)
{
	int i=0;
	posicion aux=l->frente;
	if(n>=0 && n<l->tam)
	{
		while(i<n)
		{
			i++;
			aux=aux->siguiente;
		}
		return aux->e;
	}
	printf("ERROR: Element(lista *l, int n)\n       n inv%clido",160);	
	exit(1);
}

elemento Position(lista *l, posicion p)
{
	if(ValidatePosition(l, p))
		return p->e;
	printf("ERROR: Position(lista *l, posicion p)\n       la posici%cn es inv%clida", 162, 160);
	exit(1);
}

posicion posicionSearch (lista *l, elemento e)
{
	posicion aux=l->frente;
	while(aux!=NULL)
	{
		if(memcmp(&aux->e,&e,sizeof(elemento))==0)
		{
			return aux;			
		}
		aux=aux->siguiente;
	}
	return NULL;
}

posicion ElementPosition(lista *l, int n)
{
	int i=0;
	posicion aux=l->frente;
	if(n>=0 && n<l->tam)
	{
		while(i<n)
		{
			i++;
			aux=aux->siguiente;
		}
		return aux;
	}
	printf("ERROR: ElementPosition(lista *l, int n)\n       n inv%clido", 160);	
	exit(1);			
}

boolean ValidatePosition(lista *l,posicion p)
{
	boolean b = FALSE;
	posicion aux = l->frente;
	int i;
	for(i = 0; i < l->tam; i++){
		if(p == aux){
			return TRUE;
		}
		aux=aux->siguiente;
	}
	return b;	
}
/***************************************************************************************
							  OPERACIONES DE CONSULTA (DEPURACI�N)
***************************************************************************************/
void VerLigasLista(lista *l)
{
	posicion aux;	
	aux=l->frente;	
	printf("\n*****************************************************************************************************");
	while(aux!=NULL)
	{
		//printf("\nPosicion=%d\tAnterior=%d\tSiguiente=%d\tCaracter=%c",aux,aux->anterior,aux->siguiente,aux->e.c);
		printf("\nPosici%cn=%d\tAnterior=%d\t",162,aux,aux->anterior);
		if(aux->anterior == 0)
		{
			printf("\t");
		}
		printf("Siguiente=%d\t",aux->siguiente);
		if(aux->siguiente == 0)
		{
			printf("\t");
		}
		printf("Caracter=%c\tEntero=%d",aux->e.c,aux->e.frecuencia);
		aux=aux->siguiente;
	}
	printf("\n*****************************************************************************************************");

	return;
}

/***************************************************************************************
									OPERACIONES DEL ÁRBOL
***************************************************************************************/
/*
Ver Ligas (VerLigas): recibe<-arbol (a)
VerLigas(a);
Efecto: Recibe un árbol (a) e imprime todos los enlaces que tienen los nodos del árbol.
*/
void VerLigas(posicion raiz)
{
	int i = 0;
	posicion aux;	
	aux=raiz;
	printf("\n*****************************************************************************************************");
	PreOrdenDetallado(aux);
	printf("\n*****************************************************************************************************");
	/*if(!Empty(a))
	{
		printf("\n  Ra%cz del %crbol: %c",161, 160,aux->dato.c);
	}
	//printf("\n  Altura del %crbol: %d", 160, altura(Root(a)));
	printf("\n  Cantidad de elementos=%d",a->tam);*/
	return;
}

/*
Ver Ligas (VerLigas): recibe<-arbol (a)
VerLigas(a);
Efecto: Recibe un árbol (a) e imprime todos los enlaces que tienen los nodos del árbol.
*/
void PreOrdenDetallado(nodo *nodo)
{
	if(nodo == NULL)
	{
		return;
	}
	
	Detalles(nodo);
	PreOrdenDetallado(nodo->ramaIzq);
	PreOrdenDetallado(nodo->ramaDer);
}

void Detalles(nodo *nodo)
{
	printf("\nPos=%d\t",nodo);
	printf("Izq=");
	if(nodo->ramaIzq == 0){
		printf("\033[31m%d\033[0m\t", nodo->ramaIzq);
	}
	else{
		printf("%d: %c\t", nodo->ramaIzq, nodo->ramaIzq->e.c);
	}
	printf("Der=");
	if(nodo->ramaDer == 0){
		printf("\033[31m%d\033[0m\t", nodo->ramaDer);
	}
	else{
		printf("%d: %c\t", nodo->ramaDer,nodo->ramaDer->e.c);
	}
	printf("Palabra: %c",nodo->e.c);
	printf("\tFrecuencia: %d",nodo->e.frecuencia);
}

void VerLigasArchivo(FILE *f, posicion raiz)
{
	int i = 0;
	posicion aux;	
	aux=raiz;
	fprintf(f,"\n*****************************************************************************************************");
	PreOrdenDetalladoArchivo(f,aux);
	fprintf(f,"\n*****************************************************************************************************");
	/*if(!Empty(a))
	{
		printf("\n  Ra%cz del %crbol: %c",161, 160,aux->dato.c);
	}
	//printf("\n  Altura del %crbol: %d", 160, altura(Root(a)));
	printf("\n  Cantidad de elementos=%d",a->tam);*/
	return;
}

void PreOrdenDetalladoArchivo(FILE *f, nodo *nodo)
{
	if(nodo == NULL)
	{
		return;
	}
	
	DetallesArchivo(f, nodo);
	PreOrdenDetalladoArchivo(f,nodo->ramaIzq);
	PreOrdenDetalladoArchivo(f,nodo->ramaDer);
}

void DetallesArchivo(FILE *f, nodo *nodo)
{
	fprintf(f,"\nPos=%d\t",nodo->e.c);
	fprintf(f,"Izq=");
	if(nodo->ramaIzq == 0){
		fprintf(f,"%d\t", nodo->ramaIzq);
	}
	else{
		fprintf(f,"%d: %d\t", nodo->ramaIzq->e.c, nodo->ramaIzq->e.c);
	}
	fprintf(f,"Der=");
	if(nodo->ramaDer == 0){
		fprintf(f,"%d\t", nodo->ramaDer);
	}
	else{
		fprintf(f,"%d: %d\t", nodo->ramaDer->e.c,nodo->ramaDer->e.c);
	}
	fprintf(f,"Palabra: %d",nodo->e.c);
	fprintf(f,"\tFrecuencia: %d",nodo->e.frecuencia);
}