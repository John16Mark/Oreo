/*
Fibonacci.c
V 1.1 Abril 2022
Autores:	Aarón Olvera Martínez
			Juan Luis Molina Acuña

Implementación de la búsqueda de Fibonacci en C obtenida en https://www.geeksforgeeks.org/fibonacci-search/
Toma n números enteros de la entrada estándar en la forma:
> BusquedaLineal n k a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo, e imprime la dirección de memoria donde se encontró el valor.

	COMPILAR:
gcc Fibonacci.c -o Fibonacci.exe lib/TADColaDin.c

	EJECUTAR:
Fibonacci.exe 10000000 < ordenados10millones.txt

*/

#include <stdio.h>
#include <stdlib.h>
#include "lib/TADColaDin.h"
#include <time.h>

int Fibonacci(int *A, int n, int k);
void cargarArchivo(cola *c, char *direccion);
int min(int x, int y) { return (x <= y) ? x : y; }

int main(int argc, char *argv[])
{
	// Variables para la medición de tiempos
	clock_t t_inicio, t_final;
	double t_intervalo;
	double t_acumulado = 0;
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
	// Lee de la entrada estándar los n valores y los coloca en el arreglo
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
		
	// Lee los números a buscar de la dirección "buscar.txt"
	Initialize(&mi_cola);
	cargarArchivo(&mi_cola, "buscar.txt");

	printf("\n\n    B%cSQUEDA DE FIBONACCI\n    con %d n%cmeros", 233, n, 163);
	
	// Ciclo para cada elemento de la cola
	for(i = 1; i <= Size(&mi_cola); i++){

		printf("\n\n Valor a encontrar: %d", Element(&mi_cola, i).n);
		// Inicia la medición de tiempos
		t_inicio = clock();
		// Ejecución del algoritmo de búsqueda
		p = Fibonacci(A, n, Element(&mi_cola, i).n);
		// Termina la medición de tiempos
		t_final = clock();
		t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
		t_acumulado += t_intervalo;
		
		// /*											Comentar si no se quiere imprimir la posición en donde se encontró
		//Se imprime la posición del arreglo en la que se encontró o, en su defecto, -1 si no se encuentra en arreglo
		if(p == -1){
			printf("\n \033[91mNO SE ENCONTR%c EL N%cMERO\033[0m", 224, 233);
		}
		else{
			printf("\n \033[92mSe encontr%c en la posici%cn:\033[0m %d",162,162, p);
		}
		// */											Fin comentario
		printf("\n Tiempo medido: %.8f segundos.\n", t_intervalo);
	}
	t_acumulado /= Size(&mi_cola);
	printf("\n\n    PROMEDIO DE MEDICI%cN DE TIEMPOS\n    %.8f segundos.\n", 224, t_acumulado);

	//Libera la memoria del arreglo
	free(A);
	return 0;
}

/* Returns index of k if present,  else returns -1 */
int Fibonacci(int *A, int n, int k)
{
    /* Initialize fibonacci numbers */
    int fibMMm2 = 0; // (m-2)'th Fibonacci No.
    int fibMMm1 = 1; // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci
 
    /* fibM is going to store the smallest Fibonacci
       Number greater than or equal to n */
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
 
    // Marks the eliminated range from front
    int offset = -1;
 
    /* while there are elements to be inspected. Note that
       we compare A[fibMm2] with k. When fibM becomes 1,
       fibMm2 becomes 0 */
    while (fibM > 1) {
        // Check if fibMm2 is a valid location
        int i = min(offset + fibMMm2, n - 1);
 
        /* If k is greater than the value at index fibMm2,
           cut the subarray array from offset to i */
        if (A[i] < k) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
 
        /* If k is greater than the value at index fibMm2,
           cut the subarray after i+1  */
        else if (A[i] > k) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
 
        /* element found. return index */
        else
            return i;
    }
 
    /* comparing the last element with k */
    if (fibMMm1 && A[offset + 1] == k)
        return offset + 1;
 
    /*element not found. return -1 */
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
