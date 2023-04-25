/*
Busqueda Lineal.c
V 1.1 Abril 2022
Autor: Aar�n Olvera Mart�nez

Implementaci�n de la b�squeda lineal en C obtenida en https://www.geeksforgeeks.org/linear-search/
Toma n n�meros enteros de la entrada est�ndar en la forma:
> BusquedaLineal n k a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tom� la ejecuci�n del algoritmo, e imprime la direcci�n de memoria donde se encontr� el valor.
*/

//gcc BusquedaLineal.c -o BusquedaLineal tiempos/tiempo.c
//BusquedaLineal 500000 82182077 < orden10millones.txt

#include <stdio.h>
#include <stdlib.h>
#include "lib/TADColaDin.h"
#include <windows.h>

int Busqueda(int *A, int n, int k);
void cargarArchivo(cola *c, char *direccion);

int main(int argc, char *argv[])
{
	// Variable para determinar la longitud del arreglo
	int n;
	// Variable contadora para leer los n�meros
	int i;
	// Apuntador al arreglo
	int *A;
	// Cola donde se almacenan los valores a buscar
	cola mi_cola;
	// Variable del �ndice en el que se encontr� el valor
	int p;
	// Verifica si se reciben solo tres argumentos
	if(argc != 2)
	{
		printf("\n\n Para ejecutar el programa se necesita tama%co de arreglo y el n%cmero a buscar",164,163);
		printf("\n Ejemplo: %s 100", argv[0]);
		exit(1);
	}
	
	// Lee el argumento
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	// Lee de la entrada est�ndar los n valores y los coloca en el �rbol
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
		
	// Lee los n�meros a buscar de la direcci�n "buscar.txt"
	Initialize(&mi_cola);
	cargarArchivo(&mi_cola, "buscar.txt");
	
	// Ejecuci�n del algoritmo de b�squeda
	for(i = 1; i <= Size(&mi_cola); i++){
		p = Busqueda(A, n, Element(&mi_cola, i).n);
		// /*											Comentar si no se quiere imprimir la posici�n en donde se encontr�
		//Se imprime la posici�n del arreglo en la que se encontr� o, en su defecto, -1 si no se encuentra en arreglo
		printf("\n Valor a encontrar: %d", Element(&mi_cola, i).n);
		if(p == -1){
			printf("\n \033[91mNO SE ENCONTR%c EL N%cMERO\033[0m\n", 224, 233);
		}
		else{
			printf("\n \033[92mSe encontr%c en la posici%cn:\033[0m %d\n",162,162, p);
		}
		// */											Fin comentario
	}
	
	//Libera la memoria del arreglo
	free(A);
	return 0;
}

/*
int Busqueda(int *A, int n, int k)
Recibe:	*A: Direcci�n del arreglo original a ordenar
		 n: Numero de elementos en el arreglo
		 k: Valor a buscar

Compara cada elemento del arreglo A con el valor 
a buscar k. Regresa -1 si no se encuentra.
Complejidad: O(n)
*/
int Busqueda(int *A, int n, int k)
{
	int i;
	for (i = 0; i < n; i++)
		if (A[i] == k)
			return i;
	return -1;
}

/*
void cargarArchivo(cola *c, char *direccion)
Recibe:	*c: 		Cola donde se almacenar�n los n�meros a buscar
		*direccion:	Direcci�n del archivo donde est�n los n�meros
		
Abre un archivo de texto y almacena los n�meros del archivo en una cola.
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
	
	//Lee l�nea por l�nea el archivo de texto y los almacena en la cola
	char line[500];
	while (fgets(line, sizeof(line), flujo)){
		e.n = atoi(line);
		Queue(c,e);
	}
    
	fclose(flujo);
	return;
}
