/*
Busqueda Lineal.c
V 1.1 Abril 2022
Autor: Aarón Olvera Martínez

Implementación de la búsqueda lineal en C obtenida en https://www.geeksforgeeks.org/linear-search/
Toma n números enteros de la entrada estándar en la forma:
> BusquedaLineal n k a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo, e imprime la dirección de memoria donde se encontró el valor.
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
	// Variable contadora para leer los números
	int i;
	// Apuntador al arreglo
	int *A;
	// Cola donde se almacenan los valores a buscar
	cola mi_cola;
	// Variable del índice en el que se encontró el valor
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
	// Lee de la entrada estándar los n valores y los coloca en el árbol
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
		
	// Lee los números a buscar de la dirección "buscar.txt"
	Initialize(&mi_cola);
	cargarArchivo(&mi_cola, "buscar.txt");
	
	// Ejecución del algoritmo de búsqueda
	for(i = 1; i <= Size(&mi_cola); i++){
		p = Busqueda(A, n, Element(&mi_cola, i).n);
		// /*											Comentar si no se quiere imprimir la posición en donde se encontró
		//Se imprime la posición del arreglo en la que se encontró o, en su defecto, -1 si no se encuentra en arreglo
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
Recibe:	*A: Dirección del arreglo original a ordenar
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
