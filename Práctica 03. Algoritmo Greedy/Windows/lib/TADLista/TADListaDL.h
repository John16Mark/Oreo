#ifndef __TADLista_H
#define __TADLista_H
/*
IMPLEMENTACIÓN DE TAD LISTA DOBLEMENTE LIGADA
AUTOR: Juan Luis Molina Acuña - enero 2023
VERSIÓN 1.5

EL CODIGO QUE IMPLEMENTA LAS FUNCIONES ES EL ARCHIVO: TADListaDL.c
*/
#define TRUE 1
#define FALSE 0

typedef unsigned char boolean;

typedef struct elemento
{
	unsigned char c;
	int frecuencia;
	unsigned char code;
	int limite;
}elemento;

typedef struct nodo
{
	elemento e;
	struct nodo *siguiente;
	struct nodo *anterior;
	struct nodo *ramaIzq;
	struct nodo *ramaDer;
} nodo;

typedef nodo* posicion;

typedef struct lista
{
	int tam;
	posicion frente;
	posicion final;
}lista;

//OPERACIONES DE CONSTRUCCIÓN
void Initialize (lista *l);			//Efecto: Recibe una lista l y la inicializa para su trabajo normal.
void Destroy (lista *l);			//Efecto: Recibe una lista l y la libera completamente.
//OPERACIONES DE MODIFICACIÓN
void Add (lista *l,elemento e);		//Efecto: Recibe una lista l y un elemento e; el elemento se agrega al final de la lista.
void Insert(lista * l, posicion p, elemento e, boolean b);
void InsertIn(lista *l, elemento e, int n);
void InsertNodoIn(lista *l, nodo e, int n);
void Remove (lista *l,posicion p);
void Replace (lista *l,posicion p, elemento e);
nodo Dequeue(lista *l);
//OPERACIONES DE POSICIONAMIENTO Y BÚSQUEDA
posicion Final (lista *l);			//Efecto: Recibe una lista l y retorna la posición del elemento al final de esta.
posicion First (lista *l);			//Efecto: Recibe una lista l y devuelve la posición del elemento al inicio de esta.
posicion Previous (lista *l,posicion p);
posicion Following (lista *l,posicion p);
posicion Search (lista *l,elemento e);
//OPERACIONES DE CONSULTA
int Size (lista *l);				//Efecto: Recibe una lista l y devuelve el tamaño de la lista.
boolean Empty (lista *l);			//Efecto: Recibe una lista l y devuelve TRUE en caso de que la lista este vacía y FALSE en caso contrario.
elemento Element(lista *l, int n);
elemento Position (lista *l,posicion p);
posicion posicionSearch (lista *l, elemento e);
posicion ElementPosition(lista *l, int n);
boolean ValidatePosition (lista *l,posicion p);//Efecto: Recibe una lista l, una posici�n p, devuelve TRUE si la posición es válida, FALSE en caso contrario.
//OPERACIONES DE CONSULTA (DEPURADOR)
void VerLigasLista(lista *l);
#endif    // __TADLista_H