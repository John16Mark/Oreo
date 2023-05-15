/*
Exponencial.c
V 1.1 Abril 2022
Autores:	Yael André Blásquez Martínez
			Juan Luis Molina Acuña
			Aarón Olvera Martínez
			Paola Reyes Francisco

Implementación de la búsqueda Exponencial en C obtenida en https://www.geeksforgeeks.org/exponential-search/
Toma n números enteros de la entrada estándar en la forma:
> BusquedaLineal n k a0 a1 a2 a3 ... an (en linux)
Imprime el tiempo que tomó la ejecución del algoritmo, e imprime la dirección de memoria donde se encontró el valor.

	COMPILAR:
gcc Exponencial.c -o Exponencial lib/TADColaDin.c lib/tiempo.c

	EJECUTAR:
./Exponencial 10000000 < 10millones.txt

*/

#include <stdio.h>
#include <stdlib.h>
#include "lib/TADColaDin.h"
#include "lib/tiempo.h"
#include <math.h>

#define min

int busquedaExponencial(int *A, int n, int k);
int busquedaBinaria(int *A, int l, int r, int k);
void cargarArchivo(cola *c, char *direccion);
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1);

// Variables globales para la medición de tiempos.
double u_acumulado = 0, w_acumulado = 0, s_acumulado = 0, p_acumulado = 0;

int main(int argc, char *argv[])
{
	// Variables para la medición de tiempos.
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
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
		printf("\n\n Para ejecutar el programa se necesita tamaño de arreglo");
		printf("\n Ejemplo: %s 1000000", argv[0]);
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

	printf("\n\n    BÚSQUEDA EXPONENCIAL\n    con %d números", n);
	
	// Ciclo para cada elemento de la cola
	for(i = 1; i <= Size(&mi_cola); i++){

		printf("\n\n Valor a encontrar: %d", Element(&mi_cola, i).n);
		// Inicia la medición de tiempos
		uswtime(&utime0, &stime0, &wtime0);
		// Ejecución del algoritmo de búsqueda
		p = busquedaExponencial(A, n, Element(&mi_cola, i).n);
		// Termina la medición de tiempos
		uswtime(&utime1, &stime1, &wtime1);
		
		// /*											Comentar si no se quiere imprimir la posición en donde se encontró
		//Se imprime la posición del arreglo en la que se encontró o, en su defecto, -1 si no se encuentra en arreglo
		if(p == -1){
			printf("\n \033[91mNO SE ENCONTRÓ EL NÚMERO\033[0m");
		}
		else{
			printf("\n \033[92mSe encontró en la posición:\033[0m %d", p);
		}
		// */											Fin comentario
		rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);
	}
	w_acumulado /= Size(&mi_cola);
	u_acumulado /= Size(&mi_cola);
	s_acumulado /= Size(&mi_cola);
	p_acumulado /= Size(&mi_cola);
	// Cálculo del promedio de medición del algoritmo
	printf("\n\n    PROMEDIO DE MEDICIÓN DE TIEMPOS\n");
	printf("real (Tiempo total)  %.10f s\n",  w_acumulado);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  u_acumulado);
	printf("sys (Tiempo en acciones de E/S)  %.10f s\n",  s_acumulado);
	printf("CPU/Wall   %.10f %% \n", p_acumulado);
	printf("\n");

	// Mostrar los promedios en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  w_acumulado);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  u_acumulado);
	printf("sys (Tiempo en acciones de E/S)  %.10e s\n",  s_acumulado);
	printf("CPU/Wall   %.10f %% \n", p_acumulado);
	printf("\n");

	//Libera la memoria del arreglo
	free(A);
	return 0;
}

/*
int busquedaExponencial(int *A, int n, int k)
Recibe:	*A: Dirección del arreglo original ordenado
	n: Numero de elementos en el arreglo
	k: Valor a buscar

Compara el primer elemento del arreglo A con el valor a buscar k, si lo
es retorna la posición 0.
Sino, busca el rango en el que se encuentra el valor k realizando un 
incremento exponencial de nuestro índice i hasta que encuentre una posición 
mayor a la posición en que se encuentra el valor k o hasta que alcance el 
final del arreglo A. Una vez que encuentra el rango llama a la función
busquedaBinaria para encontrar el valor a buscar en el rango establecido.

Complejidad: O(log n)
*/
int busquedaExponencial(int *A, int n, int k)
{
    //Caso base: si k esta en la primera posición
    if(A[0]==k)
        return 0;
	
    int i = 1;
    
    while(i<n&&A[i]<=k)
    {
    	i=i*2;
    }
    return busquedaBinaria(A,i/2,min(i,n-1),k);
}

// A recursive binary search function. It returns
// location of x in  given array arr[l..r] is
// present, otherwise -1
int busquedaBinaria(int *A, int l, int r, int k)
{
    if(r>=l)
    {
        int mitad = l+(r-l)/2;
 
        //Si el valor se encuentra en la mitad del arreglo
        if(A[mitad]==k)
            return mitad;
            
            
 		/*Si el valor a buscar es mas pequeño que el valor posicionado
		 en la mitad del arreglo, entonces se encuentra en el
		 subarreglo izquierdo */
        if(A[mitad]>k)
            return busquedaBinaria(A,l,mitad-1,k);
 
        /*Si el valor a buscar es mas grande que el valor posicionado
		 en la mitad del arreglo, entonces se encuentra en el
		 subarreglo derecho */
        return busquedaBinaria(A,mitad+1,r,k);
    }
 
    //Si el valor no se encuentra en el arreglo
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


/*
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1)
Recibe:	u0:	inicio tiempo usuario
		s0:	inicio tiempo sistema
		w0: inicio tiempo real
		u1: final tiempo usuario
		s1: final tiempo sistema
		w1: final tiempo real
Muestra los resultados del rendimiento temporal dentro de un espacio de tiempo acotado
*/
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1)
{
	// Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  w1 - w0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  u1 - u0);
	printf("sys (Tiempo en acciones de E/S)  %.10f s\n",  s1 - s0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (u1 - u0 + s1 - s0) / (w1 - w0));
	printf("\n");
	
	// Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  w1 - w0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  u1 - u0);
	printf("sys (Tiempo en acciones de E/S)  %.10e s\n",  s1 - s0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (u1 - u0 + s1 - s0) / (w1 - w0));
	printf("\n");

	w_acumulado += (w1 - w0);
	u_acumulado += (u1 - u0);
	s_acumulado += (s1 - s0);
	p_acumulado += 100.0 * (u1 - u0 + s1 - s0) / (w1 - w0);
}
