#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "abb.h"

void Initialize(abb *a)
{
    a->raiz = NULL;
    a->tam = 0;
    return;
}

void Add(abb *a, elemento e)
{
	bool EsDerecho;
    posicion nuevo;
    posicion aux = a->raiz;
    posicion aux2 = NULL;

    // Inicializando el nuevo nodo
    nuevo = (posicion)malloc(sizeof(struct nodo));
    nuevo->padre = NULL;
	nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->dato = e;

    // Si el árbol está vacío, se añade a la raíz
	if (a->raiz == NULL)
    {
    	a->raiz = nuevo;
	}
	else
	{
		while(aux != NULL)
		{
			aux2 = aux;	
			if(e.num > aux->dato.num)
			{
				EsDerecho = true;
				aux = aux->der;
			}
			else
			{
				EsDerecho = false;
				aux = aux->izq;
			}
		}
		if(EsDerecho)
		{
			aux2->der = nuevo;
		}
		else
		{
			aux2->izq = nuevo;
		}
		nuevo->padre = aux2;
	}
	a->tam++;
}

// Recibe un ABB a y un elemento e, devuelve la posici�n del elemento en el �rbol.
posicion Busqueda(abb *a, elemento e)
{
	//ultimabusqueda = 0;
	//a->ultbusq = 0;
	posicion aux = BuscarPosicion(a->raiz, e.num);
	//a->ultbusq = ultimabusqueda;
	return aux;
}
// Recibe una posicion p y una palabra[101] y recursivamente busca si la palabra se encuentra en el �rbol
posicion BuscarPosicion(posicion nodo, int num)
{
	posicion aux = NULL;
	if(nodo == NULL)
	{
	}
	else if(nodo->dato.num == num){
		aux = nodo;
	}
	else
	{
		if(num > nodo->dato.num)
		{
			aux = BuscarPosicion(nodo->der, num);
		}
		else{
			aux = BuscarPosicion(nodo->izq, num);
		}
	}
	//ultimabusqueda++;
	return aux;
}

void VerLigas(abb *a)
{
	int i = 0;
	posicion aux;	
	aux=a->raiz;
	printf("\n*****************************************************************************************************");
	InOrdenDetallado(aux);
	printf("\n*****************************************************************************************************");
	printf("\n  Cantidad de elementos=%d",a->tam);
	return;
}

void InOrdenDetallado(nodo *nodo)
{
	if(nodo == NULL)
	{
		return;
	}
	InOrdenDetallado(nodo->izq);
	Detalles(nodo);
	InOrdenDetallado(nodo->der);
}

void Detalles(nodo *nodo)
{
	printf("\nPos=%d\t",nodo);
	printf("Padre=");
	if(nodo->padre == 0){
		printf("\033[31m%d\033[0m\t\t\t", nodo->padre);
	}
	else{
		if(nodo->padre->dato.num > 999999999)
		{
			printf("%d\t",nodo->padre->dato.num);
		}
		else if(nodo->padre->dato.num < 10)
		{
			printf("%d\t\t\t",nodo->padre->dato.num);
		}
		else{
			printf("%d\t\t",nodo->padre->dato.num);
		}
	}
	printf("HijoIzq=");
	if(nodo->izq == 0){
		printf("\033[31m%d\033[0m\t\t", nodo->izq);
	}
	else{
		printf("%d\t",nodo->izq->dato.num);
	}
	printf("HijoDer=");
	if(nodo->der == 0){
		printf("\033[31m%d\033[0m\t\t", nodo->der);
	}
	else{
		printf("%d\t",nodo->der->dato.num);
	}
	printf("Palabra: %d",nodo->dato.num);
}
