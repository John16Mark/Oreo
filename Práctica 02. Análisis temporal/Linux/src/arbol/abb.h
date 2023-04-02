#ifndef __TADABB_H
#define __TADABB_H
/*
IMPLEMENTACIONES DEL TAD ABB (TADABB.h)
AUTOR: Padilla Escobar Karel Roman (C) Marzo 2017
VERSIÓN: 1.0

DESCRIPCIÓN: TAD ABB (Árbol Binario de Búsqueda)
Estructura de datos en la que se cumple:
Los elementos se consultan, añaden y se remueven con base en posiciones
dentro de un arreglo de arbol binario de busqueda.
el cual cuenta con un no do que tiene hijos izquierdo y derecho.
cada hijo es mayor que el padre y si el padre es mayor que el hijo, se intercambian de lugar.

Observaciones: Este archivo solo incluye las estructuras, tipos de datos y
declaración de las operaciones del TAD  ABB.
*/
#include <stdbool.h>

typedef struct elemento
{
	int num;
} elemento;

typedef struct nodo
{
    elemento dato;
    struct nodo *izq;
    struct nodo *der;
    struct nodo *padre;
} nodo;

// Se define una posicion como un apuntador a nodo
typedef nodo *posicion;

// Estructura de un ABB
typedef struct abb
{
    int tam;
    posicion raiz;
} abb;

void Initialize (abb *a);									// Efecto: Recibe un ABB a y lo inicializa para su trabajo normal.
//OPERACIONES DE POSICIONAMIENTO Y B�SQUEDA
posicion Busqueda(abb *a, elemento e);                      // Efecto: Recibe un ABB a y un elemento e, devuelve la posici�n del elemento en el �rbol.
posicion BuscarPosicion(posicion nodo, int num);            // Efecto: Recibe una posicion nodo y una palabra[101] y busca recursivamente si la palabra se encuentra en el �rbol
//OPERACIONES DE CONSULTA
bool Empty (abb *a);                                        // Efecto: Recibe un ABB a y devuelve si la lista est� vac�a.
void Add(abb *a, elemento e);								// Efecto: Recibe un ABB a y un elemento e, el elemento e se agregar� al �rbol dependiendo de su tama�o
void VerLigas(abb *a);										// Efecto: Imprime c�mo est� enlazado el �rbol binario a detalle.
void InOrdenDetallado(nodo *nodo);                       // Efecto: Recibe una posici�n e imprime el InOrden de los elementos del �rbol a partir de la posici�n dada.
void Detalles(nodo *nodo);                               // Efecto: Imprime los detalles de un elemento del �rbol.
#endif // __TADABB_H