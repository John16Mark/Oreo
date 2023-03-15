/*
Heapsort.c
V 1.0 Marzo 2022
Autor: Yael André Blazquez Martínez, Aarón Olvera Martínez.

Implementación del ordenamiento por montículo en C.
Toma n números enteros de la entrada estándar en la forma:
> mezcla.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime el tiempo que tomó la ejecución del algoritmo e imprime el arreglo ordenado(opcional).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
struct Heap
Contiene:
	int* num		arreglo de números
	int tam 		indica cuántos elementos lleva almacenados en el montículo
	int capacidad	indica la capacidad máxima del montículo
*/
typedef struct Heap{
    int* num;
    int tam;
    int capacidad;
} Heap;


void HeapSort(int *A, int n);
void intercambiar(int* a, int* b);
void heapify_down(Heap* heap, int i);
void heapify_up(Heap* heap, int i);
void insertar(Heap* heap, int valor);
int extraer(Heap* heap);
//void imprime_heap(Heap* heap);
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
	printf("\n\n    HEAPSORT\n    con %d números\n",n);
	// Ejecución del algoritmo de ordenamiento
	
	t_inicio = clock();
	HeapSort(A,n);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);
	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	
	// Imprime el arreglo
	imprimir(A, n);
	
	
	return 1;
}

/*
void HeapSort(int *A, int n)
Recibe:	*A: Dirección del arreglo original a ordenar
		 n:	Cantidad/tamaño del arreglo a ordenar
Crea el montículo, lo inicializa, inserta todos los números del arreglo dentro
de la estructura y finalmente los extrae ya ordenados.
*/
void HeapSort(int *A, int n)
{
	int i;
	Heap heap = {
        .num = (int*)malloc(sizeof(int) * n),			//Por n, que es el tamaño del heap
        .tam = 0,
        .capacidad = n
    };
	
	for(i=0; i<n; i++){
		insertar(&heap, A[i]);
	}
	
	for(i=0; i<n; i++){
		A[i]=extraer(&heap);
	}
}



/*
void intercambiar(int* a, int* b)
Recibe:	*a: Dirección del primer valor
		*b: Dirección del segundo valor
Realiza el intercambio de los elementos a y b
*/
void intercambiar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
void heapify_down(Heap* heap, int i)
Recibe:	*heap: 	Dirección del heap
		*i: 	Valor del número a acomodar
Crea una variable (smallest) para almacenar la posición del número más pequeño (inicia en la cima).
Realiza una serie comparaciones con sus hijos para obtener la posición correcta y finalmente intercambia la cima
con este número. Esto lo hace de manera recursiva hasta que llegue al fondo.
*/
void heapify_down(Heap* heap, int i) {
    int hijo_izq = 2 * i + 1;
    int hijo_der = 2 * i + 2;
    int smallest = i;

    if (hijo_izq < heap->tam && heap->num[hijo_izq] < heap->num[smallest]) {
        smallest = hijo_izq;
    }

    if (hijo_der < heap->tam && heap->num[hijo_der] < heap->num[smallest]) {
        smallest = hijo_der;
    }

    if (smallest != i) {
        intercambiar(&heap->num[i], &heap->num[smallest]);
        heapify_down(heap, smallest);
    }
}

/*
void insertar(Heap* heap, int valor)
Recibe:	*heap: 	Dirección del heap
		*i: 	Valor del número a añadir
Pregunta si llegó a la capacidad máxima que cabe dentro de la estructura. Si no ha llegado, añade el número hasta abajo.
Posteriormente revisa si su posición es correcta con la función heapify_up.
*/
void insertar(Heap* heap, int valor) {
    if (heap->tam < heap->capacidad) {
        heap->num[heap->tam] = valor;
        heap->tam++;
        heapify_up(heap, heap->tam - 1);
    }
}

/*
void heapify_up(Heap* heap, int i)
Recibe:	*heap: 	Dirección del heap
		*i: 	Valor del número a comparar
Calcula quién es el padre del número y compara cuál es mayor; si el hijo es menor, los intercambia
Realiza la operación de manera recursiva hasta que llegue lo más arriba que puede
*/
void heapify_up(Heap* heap, int i) {
    int padre = (i - 1) / 2;

    if (i > 0 && heap->num[i] < heap->num[padre]) {
        intercambiar(&heap->num[i], &heap->num[padre]);
        heapify_up(heap, padre);
    }
}

/*
int extraer(Heap* heap)
Recibe:
	*heap: 	Dirección del heap
Toma el número más pequeño del montículo (posición 0) y pone en su lugar el más grande (última posición).
Posteriormente reacomoda los números con la función heapidy_down
Regresa:
	int min_valor:	Número más pequeño dentro del montículo.
*/
int extraer(Heap* heap) {
    if (heap->tam == 0) {
        //printf("Heap is empty.\n");
        return -1;
    }

    int min_valor = heap->num[0];
    heap->num[0] = heap->num[heap->tam - 1];
    heap->tam--;
    heapify_down(heap, 0);

    return min_valor;
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

/*
void imprime_heap(Heap* heap) {
    int i;
	printf("Heap: ");

    for (i = 0; i < heap->tam; i++) {
        printf("%d ", heap->num[i]);
    }

    printf("\n");
}*/
