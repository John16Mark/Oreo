/*
IMPLEMENTACIONES DE LA LIBRERIA DEL TAD LISTA (TADLista.h)
AUTOR: Juan Luis Molina Acuña - Enero 2023
VERSIÓN: 1.0

Frente                                                       Final
         ******    ******    ******    ******    ******    ******
 NULL <- *    * <- *    * <- *    * <- *    * <- *    * <- *    *
         * N1 *    * N2 *    * N3 *    * N4 *    * N5 *    * N6 *
         *    * -> *    * -> *    * -> *    * -> *    * -> *    * -> NULL
         ******    ******    ******    ******    ******    ******    

COMPILACIÃ“N PARA GENERAR EL CÃ“DIGO OBJETO: gcc TADListaSL.c -c 
*/

//LIBRERÍAS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TADListaDL.h"
/***************************************************************************************
								OPERACIONES DE CONSTRUCCIÓN
***************************************************************************************/
void Initialize (lista *l)
{
	l -> frente = NULL;
	l -> final = NULL;
	l -> tam = 0;
	l -> apellido=l;
	return;
}

void Destroy (lista *l)	
{
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
							   OPERACIONES DE MODIFICACIÓN
***************************************************************************************/
void Add (lista *l, elemento e)
{
	posicion aux;
	aux=malloc(sizeof(nodo));
	if(aux==NULL)
	{
		printf("ERROR: Add (l,e) desbordamiento de lista");
		exit(1);
	}
	aux->e = e;
	aux->apellido = l->apellido;
	if(l->tam>0)
	{
		aux->anterior = l->final;
		l->final->siguiente=aux;
	}
	else
	{
		aux->anterior = NULL;
		l->frente=aux;
	}
	l->final=aux;
	l->final->siguiente = NULL;
	l->tam++;
	return;
}

void Insert (lista * l, posicion p, elemento e, boolean b)
{
	posicion aux, aux2, aux3;
	aux=malloc(sizeof(nodo));
	if(aux==NULL)
	{
		printf("ERROR: Insert (l,p,e,b) Desbordamiento de lista.");
		exit(1);
	}
	aux->e=e;
	aux->apellido=l->apellido;
	if(ValidatePosition(l,p))
	{
		if(b)	//Enfrente de p
		{
			aux2=Previous(l,p);
			if(aux2==NULL)	//p es el frente, se inserta al frente de la lista
			{
				aux->anterior=NULL;
				p->anterior = aux;
				aux->siguiente=l->frente;
				l->frente=aux;
				l->tam++;
			}
			else	//Si p no era el frente de la lista
			{
				aux->anterior=aux2;
				aux2->siguiente=aux;
				p->anterior=aux;
				aux->siguiente=p;
				l->tam++;
			}
		}
		else	//Atras de p
		{
			aux2=Following(l,p);
			if(aux2==NULL)	//p es el final, se inserta al final de la lista
			{
				aux->anterior=p;
				p->siguiente=aux;
				l->final=aux;
				aux->siguiente=NULL;
				l->tam++;
			}
			else	//Si p no era el frente de la lista
			{
				aux->anterior=p;
				aux2->anterior=aux;
				p->siguiente=aux;
				aux->siguiente=aux2;
				l->tam++;
			}
		}
	}
	else //si p es invalido, se inserta e enfrente
	{
		aux->siguiente=l->frente;
		l->frente=aux;
		if(l->tam==0)
			l->final=aux;
		l->tam++;
	}
	return;
}

void Remove (lista *l,posicion p)
{
	posicion aux,aux2;
	if (!ValidatePosition(l,p))
	{
		printf ("ERROR: Remove (l,p), p es invalida");
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
	if(ValidatePosition(l,p))
	{
		p->e=e;
	}
	else
	{
		printf("ERROR: Replace(l,p,e) PosiciÃ³n invalida");
		exit(1);
	}
	return;
}
/***************************************************************************************
						OPERACIONES DE POSICIONAMIENTO Y BÚSQUEDA
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
	printf("ERROR:Following(L,p) la posicion es invalida");
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
	int i=1;
	posicion aux=l->frente;
	if(n>0 && n<=l->tam)
	{
		while(i<n)
		{
			i++;
			aux=aux->siguiente;
		}
		return aux->e;
	}
	printf("ERROR:Element(L,n)n invalido");	
	exit(1);
}

elemento Position (lista *l,posicion p)
{
	if(ValidatePosition(l,p))
		return p->e;
	printf("ERROR:Position(L,p) la posicion es invalida");
	exit(1);
}

posicion Search (lista *l,elemento e)
{		posicion aux=l->frente;
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
	int i=1;
	
	posicion aux=l->frente;
	if(n>0 && n<=l->tam)
	{
		while(i<n)
		{
			i++;
			aux=aux->siguiente;
		}
		return aux;
	}
	printf("ERROR: ElementPosition(L,n)n invalido");	
	exit(1);			
}

boolean ValidatePosition(lista *l,posicion p)
{
	boolean b = FALSE;
	if(p!=NULL)
		if(p->apellido==l->apellido)
			b = TRUE;
	return b;	
}
/***************************************************************************************
						  OPERACIONES DE CONSULTA (DEPURACIÓN)
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



