/*
Heapsort.c
V 1.0 Marzo 2022
Autor: Yael Andr� Blazquez Mart�nez, Aar�n Olvera Mart�nez.

Implementaci�n del ordenamiento por mont�culo en C.
Toma n n�meros enteros de la entrada est�ndar en la forma:
> mezcla.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime el tiempo que tom� la ejecuci�n del algoritmo e imprime el arreglo ordenado(opcional).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
struct Heap
Contiene:
	int* num		arreglo de n�meros
	int tam 		indica cu�ntos elementos lleva almacenados en el mont�culo
	int capacidad	indica la capacidad m�xima del mont�culo
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
	// Variables para la medici�n de tiempos
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
	// Lee el argumento y crea un arreglo con el tama�o recibido
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	if (A == NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n", n);
		exit(1);
	}
	// Lee de la entrada est�ndar los n valores y los coloca en el arreglo
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	printf("\n\n    HEAPSORT\n    con %d n�meros\n",n);
	// Ejecuci�n del algoritmo de ordenamiento
	
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
Recibe:	*A: Direcci�n del arreglo original a ordenar
		 n:	Cantidad/tama�o del arreglo a ordenar
Crea el mont�culo, lo inicializa, inserta todos los n�meros del arreglo dentro
de la estructura y finalmente los extrae ya ordenados.
*/
void HeapSort(int *A, int n)
{
	int i;
	Heap heap = {
        .num = (int*)malloc(sizeof(int) * n),			//Por n, que es el tama�o del heap
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
Recibe:	*a: Direcci�n del primer valor
		*b: Direcci�n del segundo valor
Realiza el intercambio de los elementos a y b
*/
void intercambiar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
void heapify_down(Heap* heap, int i)
Recibe:	*heap: 	Direcci�n del heap
		*i: 	Valor del n�mero a acomodar
Crea una variable (smallest) para almacenar la posici�n del n�mero m�s peque�o (inicia en la cima).
Realiza una serie comparaciones con sus hijos para obtener la posici�n correcta y finalmente intercambia la cima
con este n�mero. Esto lo hace de manera recursiva hasta que llegue al fondo.
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
Recibe:	*heap: 	Direcci�n del heap
		*i: 	Valor del n�mero a a�adir
Pregunta si lleg� a la capacidad m�xima que cabe dentro de la estructura. Si no ha llegado, a�ade el n�mero hasta abajo.
Posteriormente revisa si su posici�n es correcta con la funci�n heapify_up.
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
Recibe:	*heap: 	Direcci�n del heap
		*i: 	Valor del n�mero a comparar
Calcula qui�n es el padre del n�mero y compara cu�l es mayor; si el hijo es menor, los intercambia
Realiza la operaci�n de manera recursiva hasta que llegue lo m�s arriba que puede
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
	*heap: 	Direcci�n del heap
Toma el n�mero m�s peque�o del mont�culo (posici�n 0) y pone en su lugar el m�s grande (�ltima posici�n).
Posteriormente reacomoda los n�meros con la funci�n heapidy_down
Regresa:
	int min_valor:	N�mero m�s peque�o dentro del mont�culo.
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
