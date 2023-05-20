/*

gcc prueba.c -o prueba lib/disenio.c lib/ascii_art.c lib/menu.c lib/TADLista/TADListaDL.c lib/tiempo.c -lm -w

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <math.h>
#include "lib/disenio.h"
#include "lib/ascii_art.h"
#include "lib/menu.h"
#include "lib/TADLista/TADListaDL.h"
#include "lib/tiempo.h"

#include <unistd.h> 

#define CONSOLE_WIDTH 120
#define CONSOLE_HEIGHT 30
#define TABLA_MAX_LINEAS 522
#define TABLA_MAX_COLUMNAS 500

#define PESOBIT(bpos) 1<<bpos
#define CONSULTARBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)

void menuCompresion();
void menuDescompresion();

void InordenCode2(posicion p, int paso, elemento *Frec, unsigned char c1, unsigned char c2);
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1, int bytes, bool cd, char nombre[150]);

bool procesoTerminado = false;
pthread_t hilo1;
pthread_t hilo2;

typedef struct direcciones{
	char entrada[150];
	char salida[150];
	char tabla[150];
}direcciones;

unsigned char *Arreglodeprueba;
int arreglopruebatam = 0;

int main()
{
	int i;
	clrscr();

	for(i = 0; i < CONSOLE_WIDTH; i++){
		printf(" ");
	}
	int eleccion = 0;
	while(1){
		disenioMenu();
		scanf("%d",&eleccion);
		switch(eleccion){
		case 1:
			menuCompresion();
			break;
		case 2:
			menuDescompresion();
			break;
		case 3:
			clrscr();
			pochita(42,4);
			gotoxy(0,19);
			exit(0);
			break;
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void *procesoCompresion(void *arg)
Efecto:
	Recibe un struct direcciones y realiza la compresión aplicando el algoritmo de Huffman
	Se crea un archivo de salida comprimido y un archivo de texto con las frecuencias.
*/
void *procesoCompresion(void *arg)
{
	FILE *archivo;			// Dirección de tipo FILE que vamos a manipular
	unsigned char *A;		// Arreglo que almacena todos los bytes (caracteres) del archivo de entrada
	double n_bytes;			// Cantidad de bytes que tiene el archivo de entrada
	unsigned char *ASalida;	// Arreglo que almacena todos los bytes (caracteres) del archivo de salida
	double n_bytes_salida;	// Cantidad de bytes que tiene el archivo de salida
	
	direcciones D0 = *((direcciones*)arg);
	int pos_byte = 0;		// En qué byte del nuevo arreglo estás
	int pos_bit = 0;		// En qué bit de cada byte estás
	elemento *Frec;			// Tabla de frecuencias
	int i, j;
	lista mi_lista;
	Initialize(&mi_lista);
	
	// Variables para la medición de tiempos.
	double utime0, stime0, wtime0, utime1, stime1, wtime1;

	//--------------------------------------------------------------//
	//																//
	//				 ENTRADA Y LECTURA DE LOS ARCHIVOS				//
	//																//
	//--------------------------------------------------------------//
	
	// Inicia la medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);

	// Modo binario lectura -> archivo de entrda
	archivo = fopen(D0.entrada, "rb");
	if(!archivo){
		printf("\n Error al abrir el archivo: %s", D0.entrada);
		exit(1);
	}
	fseek(archivo, 0, SEEK_END);		// Se posiciona al final del archivo
	n_bytes = ftell(archivo);			// Regresa el valor de la posición en donde está
	rewind(archivo);					// Vuelve al inicio
	
	// Lee todos los bytes del archivo y los almacena en el arreglo de bytes, cierra el archivo.
	A = (unsigned char *) malloc(n_bytes * sizeof(unsigned char));
	fread(A, n_bytes, 1, archivo);		// Almacenar en A TODO lo que está en archivo
	fclose(archivo);					// Cerrar archivo
	
	//--------------------------------------------------------------//
	//																//
	//				CONTAR FRECUENCIA DE LOS CARACTERES				//
	//																//
	//--------------------------------------------------------------//

	// Crea la tabla de frecuencias con tamaño 256 e inicializa en 0 la frecuencia de todos los bytes
	Frec = malloc(256 * sizeof(elemento));
	for(i = 0; i < 256; i++){
		Frec[i].frecuencia = 0;
	}
	
	// Recorre todos los bytes del archivo original, y va almacenando la frecuencia de aparición de los
	// caracteres (bytes)
	for(i = 0; i < n_bytes; i++){
		Frec[A[i]].frecuencia++;
	}

	//--------------------------------------------------------------//
	//																//
	//	   CREAR LA LISTA Y UN ARREGLO QUE SERVIRÁ PARA IMPRIMIR	//
	//					  LA LISTA DE FRECUENCIAS					//
	//																//
	//--------------------------------------------------------------//
	
	// Añadir a la lista los elementos con frecuencia positiva del arreglo
	for(i = 0; i < 256; i++){
		if(Frec[i].frecuencia != 0){
			Frec[i].c = i;
			Add(&mi_lista, Frec[i]);
		}
	}
	int tam_lista = Size(&mi_lista);
	
	// Arreglo de elementos para imprimir la lista de frecuencias
	elemento *TablaResumida;
	TablaResumida = malloc(tam_lista * sizeof(elemento));
	SelectionSort(&mi_lista);
	for(i = 0; i < tam_lista; i++){
		TablaResumida[i] = Element(&mi_lista, i);
	}
	
	//--------------------------------------------------------------//
	//																//
	//	 		    CREAR EL ÁRBOL A PARTIR DE LA LISTA				//
	//																//
	//--------------------------------------------------------------//

	posicion raiz = NULL;
	nodo N;
	posicion S1 = NULL; 
	posicion S2 = NULL;
	int pos_aux = 0;

	while(mi_lista.tam > 1){
		S1 = DequeuePos(&mi_lista);
		S2 = DequeuePos(&mi_lista);
		
		// Modificación de los valores para agregar un nodo simple
		N.e.frecuencia = S1->e.frecuencia + S2->e.frecuencia;
		N.ramaIzq = S1;
		N.ramaDer = S2;

		pos_aux = 0;
		for(i = 0; i < mi_lista.tam; i++){
			if(N.e.frecuencia > Element(&mi_lista, i).frecuencia){
				pos_aux = i;
			}
			else{
				i = mi_lista.tam;
			}
		}
		if(mi_lista.tam != 0){
			InsertNodoIn2(&mi_lista, ElementPosition(&mi_lista,pos_aux), N, 0);
		}
		else{
			raiz = &N;
		}
	}

	//--------------------------------------------------------------//
	//																//
	//	 REALIZAR EL RECORRIDO DEL ÁRBOL PARA OBTENER EL CONJUNTO	//
	//		DE BITS CODIFICADOS Y EL TAMAÑO DE DICHO CONJUNTO		//
	//																//
	//--------------------------------------------------------------//
	
	unsigned char caux = 0;
	unsigned char caux2 = 0;
	InordenCode2(raiz, 0, Frec, caux, caux2);

	//--------------------------------------------------------------//
	//																//
	//	 		  OBTENER EL TAMAÑO DEL ARREGLO DE SALIDA			//
	//			A PARTIR DE LA LONGITUD DEL CONJUNTO DE n_bits		//
	//				 Y LA FRECUENCIA DE LOS CARACTERES				//
	//																//
	//--------------------------------------------------------------//
	
	// Obtener el tama�o del arreglo de salida
	n_bytes_salida = 0;
	for(i = 0; i < 256; i++){
		if(Frec[i].frecuencia != 0){
			n_bytes_salida += ((double) Frec[i].frecuencia * (double) Frec[i].limite);
		}
	}
	n_bytes_salida /= 8;
	n_bytes_salida = ceil(n_bytes_salida);

	//--------------------------------------------------------------//
	//																//
	//	 	CREAR UN ARCHIVO DE TEXTO AL CUAL SE LE IMPRIMIRÁN		//
	//			LOS DATOS VARIOS Y LA TABLA DE FRECUENCIAS			//
	//																//
	//--------------------------------------------------------------//

	// Crear archivo de texto para la tabla de frecuencias y m�s informaci�n
	FILE *TABLA = fopen(strcat(D0.tabla,".txt"), "w");
	if(TABLA == NULL){
		printf("\n Error al abrir el archivo: %s", D0.tabla);
		exit(1);
	}
	fprintf(TABLA, "Tipo de archivo de entrada: %s", strrchr(D0.entrada, '.'));
	fprintf(TABLA, "\nArchivo de entrada (bytes): %0.0lf", n_bytes);
	fprintf(TABLA, "\nArchivo de salida (bytes): %0.0lf", n_bytes_salida);
	
	//--------------------------------------------------------------//
	//																//
	//	 CREAR EL ARREGLO DE SALIDA, LEER EL ARREGLO DE CARACTERES	//
	//		ORIGINAL E IR COLOCANDO 0 Y 1 EN DONDE CORRESPONDA,		//
	//				SEGÚN AL CONJUNTO DE BITS CODIFICADO			//
	//																//
	//--------------------------------------------------------------//

	// Crea el arreglo de bytes de salida inicializa los caracteres en 0
	ASalida = malloc(n_bytes_salida * sizeof(unsigned char));
	for(i = 0; i < n_bytes_salida; i++){
		ASalida[i] = 0;
	}
	
	// Recorre todos los bytes del archivo original, busca su codificaci�n binaria y modifica
	// los bits de los caracteres del arreglo de salida
	int a;
	int a1;
	for(i = 0; i < n_bytes; i++){
		for(j = 0; j < Frec[A[i]].limite; j++){
			
			if(j < 8){
				if(CONSULTARBIT(Frec[A[i]].code, 7-j) == 1){
					PONE_1(ASalida[pos_byte], 7-pos_bit);
				}
			}else{
				a = pos_bit-8;
				a1 = j - 8;
				if(CONSULTARBIT(Frec[A[i]].code2, 7-a1) == 1){
					PONE_1(ASalida[pos_byte], 7-pos_bit);
				}
			}
			
			pos_bit++;
			if(pos_bit == 8){
				pos_byte++;
				pos_bit = 0;
			}
		}
	}

	//--------------------------------------------------------------//
	//																//
	//	  		 TERMINAR DE IMPRIMIR EN EL ARCHIVO DE TEXTO		//
	//																//
	//--------------------------------------------------------------//
	
	int b = 8-pos_bit;
	if(b == 8){
		b = 0;
	}
	fprintf(TABLA, "\nBits sobrantes: %d", b);
	fprintf(TABLA, "\n\nTABLA DE FRECUENCIAS (VALOR):\n");
	for(i = 0; i < tam_lista; i++){
		fprintf(TABLA, "%d:%d\n", TablaResumida[i].c, TablaResumida[i].frecuencia);
	}
	fprintf(TABLA, "\n\nTABLA DE FRECUENCIAS (CARACTER):\n");
	for(i = 0; i < tam_lista; i++){
		fprintf(TABLA, "%c:%d\n", TablaResumida[i].c, TablaResumida[i].frecuencia);
	}
	fclose(TABLA);

	//--------------------------------------------------------------//
	//																//
	//	   	  CREAR EL ARCHIVO DE SALIDA Y ESCRIBIR LOS BYTES		//
	//																//
	//--------------------------------------------------------------//

	//Modo binario escritura -> archivo de salida
	archivo = fopen(D0.salida, "wb");
	if(archivo == NULL){
		printf("\n Error al abrir el archivo: %s", D0.salida);
		exit(1);
	}
	fwrite(ASalida, n_bytes_salida, sizeof(unsigned char), archivo);
	fclose(archivo);

	// Termina la medición de tiempos
	uswtime(&utime1, &stime1, &wtime1);
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1, n_bytes, true, D0.entrada);

	procesoTerminado = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void *procesoDescompresion(void *arg)
Efecto:
	Recibe un struct direcciones y realiza la descompresión correspondiente del algoritmo
	de Huffman. Crea un archivo de salida descomprimido.
*/
void *procesoDescompresion(void *arg)
{
	FILE *archivo;			// Direcci�n de tipo FILE que vamos a manipular
	unsigned char *A;		// Arreglo que almacena todos los bytes (caracteres) del archivo de entrada
	double n_bytes;			// Cantidad de bytes que tiene el archivo de entrada
	unsigned char *ASalida;	// Arreglo que almacena todos los bytes (caracteres) del archivo de salida
	double n_bytes_salida;	// Cantidad de bytes que tiene el archivo de salida
	int bits_sobrantes;
	
	direcciones D0 = *((direcciones*)arg);
	int pos_byte = 0;		// En qu� byte del nuevo arreglo est�s
	int pos_bit = 0;		// En qu� bit de cada byte est�s
	elemento *Frec;			// Tabla de frecuencias
	int i, j;
	lista mi_lista;
	Initialize(&mi_lista);

	// Variables para la medición de tiempos.
	double utime0, stime0, wtime0, utime1, stime1, wtime1;

	//--------------------------------------------------------------//
	//																//
	//		   ENTRADA Y LECTURA DE LA TABLA DE FRECUENCIAS			//
	//																//
	//--------------------------------------------------------------//

	// Inicia la medición de tiempos
	uswtime(&utime0, &stime0, &wtime0);

	// Lee el archivo de texto de la tabla de frecuencias y almacena los datos
	FILE *tablatxt;
	tablatxt = fopen(strcat(D0.tabla, ".txt"), "r");
	if(tablatxt == NULL){
		printf("\n Error al abrir el archivo: %s", D0.tabla);
		exit(1);
	}

	// Almacena línea por línea en un arreglo
	char line[TABLA_MAX_COLUMNAS];
	int n_lineas_tabla = 0;
	unsigned char linea[TABLA_MAX_LINEAS][TABLA_MAX_COLUMNAS];
	while (fgets(linea[n_lineas_tabla], TABLA_MAX_COLUMNAS, tablatxt)){
		linea[n_lineas_tabla][strlen(linea[n_lineas_tabla]) - 1] = '\0';
		n_lineas_tabla++;
	}
	fclose(tablatxt);

	n_bytes = atoi(strrchr(linea[2], ':')+2);
	n_bytes_salida = atoi(strrchr(linea[1], ':')+2);
	bits_sobrantes = atoi(strrchr(linea[3], ':')+2);

	// Almacena el caracter y la frecuencia y los añade a la lista
	elemento e;
	fflush(stdout);
	char caracter[16];
	char caracterAux;
	char num[16];
	bool empiezaTabla = false;
	bool empiezaNum;
	int k;
	for(i=6; i < n_lineas_tabla; ++i){
		strcpy(caracter,"");
		strcpy(num,"");
		k = 0;
		if(strrchr(linea[i], ':') == NULL){
			i = n_lineas_tabla;
		}
		else{
			empiezaNum = false;
			for(j = 0; j< strlen(linea[i]); j++){
				if(empiezaNum){
					caracterAux = linea[i][j];
					num[k] = caracterAux;
					num[k+1] = '\0';
					k++;
				}
				else if(linea[i][j] == ':'){
					empiezaNum = true;

				}
				else{
					caracterAux = linea[i][j];
					caracter[j] = caracterAux;
					caracter[j+1] = '\0';
				}
			}
			e.c = atoi(caracter);
			e.frecuencia = atoi(num);
			Add(&mi_lista, e);
		}
	}

	//--------------------------------------------------------------//
	//																//
	//	 		    CREAR EL ÁRBOL A PARTIR DE LA LISTA				//
	//																//
	//--------------------------------------------------------------//

	posicion raiz = NULL;
	nodo N;
	posicion S1 = NULL; 
	posicion S2 = NULL;
	int pos_aux = 0;

	while(mi_lista.tam > 1){
		S1 = DequeuePos(&mi_lista);
		S2 = DequeuePos(&mi_lista);
		
		// Modificación de los valores para agregar un nodo simple
		N.e.frecuencia = S1->e.frecuencia + S2->e.frecuencia;
		N.ramaIzq = S1;
		N.ramaDer = S2;

		pos_aux = 0;
		for(i = 0; i < mi_lista.tam; i++){
			if(N.e.frecuencia > Element(&mi_lista, i).frecuencia){
				pos_aux = i;
			}
			else{
				i = mi_lista.tam;
			}
		}
		if(mi_lista.tam != 0){
			InsertNodoIn2(&mi_lista, ElementPosition(&mi_lista,pos_aux), N, 0);
		}
		else{
			raiz = &N;
		}
	}

	//--------------------------------------------------------------//
	//																//
	//				 ENTRADA Y LECTURA DE LOS ARCHIVOS				//
	//																//
	//--------------------------------------------------------------//

	// Modo binario lectura -> archivo de entrda
	archivo = fopen(D0.entrada, "rb");
	if(archivo == NULL){
		printf("\n Error al abrir el archivo: %s", D0.entrada);
		exit(1);
	}
	// Lee todos los bytes del archivo y los almacena en el arreglo de bytes, cierra el archivo.
	A = (unsigned char *) malloc(n_bytes * sizeof(unsigned char));
	fread(A, n_bytes, 1, archivo);		// Almacenar en A TODO lo que está en archivo
	fclose(archivo);					// Cerrar archivo

	//--------------------------------------------------------------//
	//																//
	//	   	  CREAR EL ARCHIVO DE SALIDA Y ESCRIBIR LOS BYTES		//
	//																//
	//--------------------------------------------------------------//

	//Modo binario escritura -> archivo de salida
	archivo = fopen(strcat(D0.salida, strrchr(linea[0], ':')+2), "wb");
	if(!archivo){
		printf("\n Error al abrir el archivo: %s", D0.salida);
		exit(1);
	}

	// Crea el arreglo de bytes de salida inicializa los caracteres en 0
	ASalida = malloc(n_bytes_salida * sizeof(unsigned char));
	for(i = 0; i < n_bytes_salida; i++){
		ASalida[i] = 0;
	}
	
	//--------------------------------------------------------------//
	//																//
	//			  LEER BYTES COMPRIMIDOS Y DECODIFICARLOS			//
	//																//
	//--------------------------------------------------------------//

	posicion p = raiz;
	for(i = 0; i < n_bytes; i++){
		for(j = 7; j >= 0; j--){
			if(i == n_bytes-1 && j <= bits_sobrantes){
				j = -1;
			}
		}
	}
	k = 0;
	for(i = 0; i < n_bytes; i++){
		for(j = 7; j >= 0; j--){
			if(CONSULTARBIT(A[i], j) == 1){
				p = p->ramaDer;
			}else{
				p = p->ramaIzq;
			}
			if(p->ramaDer == NULL && p->ramaIzq == NULL){
				ASalida[k] = p->e.c;
				k++;
				p = raiz;
				if(i == n_bytes-1 && j <= bits_sobrantes){
					j = -1;
				}
			}
		}
	}

	fwrite(ASalida, n_bytes_salida, sizeof(unsigned char), archivo);
	fclose(archivo);

	// Termina la medición de tiempos
	uswtime(&utime1, &stime1, &wtime1);
	rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1, n_bytes, false, D0.entrada);

	procesoTerminado = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	void menuCompresion()
Efecto:
	Lee las direcciones de los archivos para la compresión,
	crea un hilo en el cual se realizará lacompresión y
	muestra una pantalla de carga en lo que se realiza el proceso.
*/
void menuCompresion()
{
	char direccion[150];
	char salida[150];
	char tabla[150];

	disenioCompresion();
	scanf("%s",&direccion);

	gotoxy(2, 13);
	colorForeground("blanco");
	printf("Introduzca el nombre del archivo comprimido de salida (DE PREFERENCIA OMITIR EXTENSIÓN):");
	gotoxy(4, 15);
	colorDefault();
	scanf("%s",&salida);

	gotoxy(2, 19);
	colorForeground("blanco");
	printf("Introduzca el nombre del archivo con la tabla de frecuencias(DE PREFERENCIA OMITIR EXTENSIÓN):");
	gotoxy(4, 21);
	colorDefault();
	scanf("%s",&tabla);

	direcciones D;
	strcpy(D.entrada, direccion);
	strcpy(D.salida, salida);
	strcpy(D.tabla, tabla);

	clrscr();
	pochita(42,4);
	gotoxy(52, 19);
	colorForeground("rojo claro");
	printf("Comprimiendo");
	fflush(stdout);
	gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
	fflush(stdout);

	if(0 != pthread_create(&hilo1, NULL, procesoCompresion, &D)){
		perror("El thread no pudo crearse");
		exit(-1);
	}

	//esperar(500);
	gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
	fflush(stdout);
	while(!procesoTerminado){
		gotoxy(64, 19);
		printf(".  ");
		fflush(stdout);
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		fflush(stdout);
		esperar(400);
		fflush(stdout);
		gotoxy(65, 19);
		printf(".");
		fflush(stdout);
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		fflush(stdout);
		esperar(400);
		fflush(stdout);
		gotoxy(66, 19);
		printf(".");
		fflush(stdout);
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		fflush(stdout);
		esperar(400);
	}

	pthread_join (hilo1, NULL);
	procesoTerminado = false;

	gotoxy(52, 19);
	printf("   TERMINADO   ");
	fflush(stdout);
	gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
	fflush(stdout);
	esperar(800);
	clrscr();

	gotoxy(23,15);
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	void menuDescompresion()
Efecto:
	Lee las direcciones de los archivos para la descompresión,
	crea un hilo en el cual se realizará la descompresión y
	muestra una pantalla de carga en lo que se realiza el proceso.
*/
void menuDescompresion()
{
	char direccion[150];
	char salida[150];
	char tabla[150];

	disenioDescompresion();
	scanf("%s",&direccion);

	gotoxy(2, 13);
	colorForeground("blanco");
	printf("Introduzca el nombre que tendrá el archivo descomprimido (OMITIR EXTENSIÓN):");
	gotoxy(4, 15);
	colorDefault();
	scanf("%s",&salida);
	fflush(stdin);

	gotoxy(2, 19);
	colorForeground("blanco");
	printf("Introduzca el nombre del archivo de texto con la tabla de frecuencias (OMITIR EXTENSIÓN):");
	gotoxy(4, 21);
	colorDefault();
	scanf("%s",&tabla);
	fflush(stdin);

	direcciones D;
	strcpy(D.entrada, direccion);
	strcpy(D.salida, salida);
	strcpy(D.tabla, tabla);
	
	clrscr();
	pochita(42,4);
	gotoxy(52, 19);
	colorForeground("rojo claro");
	printf("Descomprimiendo");
	fflush(stdout);
	gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
	fflush(stdout);

	if(0 != pthread_create(&hilo1, NULL, procesoDescompresion, &D)){
		perror("El thread no pudo crearse");
		exit(-1);
	}
	
	//esperar(500);
	gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
	fflush(stdout);
	while(!procesoTerminado){
		gotoxy(67, 19);
		printf(".  ");
		fflush(stdout);
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		fflush(stdout);
		esperar(400);
		fflush(stdout);
		gotoxy(68, 19);
		printf(".");
		fflush(stdout);
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		fflush(stdout);
		esperar(400);
		fflush(stdout);
		gotoxy(69, 19);
		printf(".");
		fflush(stdout);
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		fflush(stdout);
		esperar(400);
	}

	pthread_join (hilo1, NULL);
	procesoTerminado = false;
	
	gotoxy(52, 19);
	printf("     TERMINADO    ");
	fflush(stdout);
	gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
	fflush(stdout);
	esperar(800);
	clrscr();

	gotoxy(23,15);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	void InordenCode2(posicion p, int paso, elemento *Frec, unsigned char c1, unsigned char c2)
Recibe:
	posicion p:			posicion del nodo en donde se encuentra
	int paso:			nivel del árbol en el que estamos posicionados
	elemento *Frec:		tabla de frecuencias
 	unsigned char c1:	byte donde se almacena el conjunto de bits codificados
 	unsigned char c2:	misma función que c1, solo se usa cuando c1 ya está lleno y todavía faltan bits.
Efecto:
	realiza un recorrido del árbol, una vez llega a una hoja, almacena los conjuntos de bits codificados
	en los elementos de esos nodos y actualiza la tabla de frecuencias con una copia de esos elementos.
*/
void InordenCode2(posicion p, int paso, elemento *Frec, unsigned char c1, unsigned char c2){
	// Caso base: Si es una hoja, almacena los valores en el elemento del nodo y actualiza la tabla
	// de frecuencias
	if((p->ramaIzq == NULL) && (p->ramaDer == NULL)){
		p->e.code = c1;
		p->e.code2 = c2;
		p->e.limite = paso;
		Frec[p->e.c] = p->e;
	}
	// Si no, continúa el recorrido
	else{
		// Si existe rama izquierda, continúa el recorrido por ahí
		if(p->ramaIzq != NULL){
			InordenCode2(p->ramaIzq, paso+1, Frec, c1, c2);
		}
		// Si existe rama derecha, continúa el recorrido por ahí, añadiendo un "1" en el byte codificado
		if(p->ramaDer != NULL){
			unsigned char aux1 = c1;
			unsigned char aux2 = c2;
			int a = paso - 8;
			if(paso < 8){
				PONE_1(aux1, 7-paso);
			}
			else{
				PONE_1(aux2, 7-a);
			}
			InordenCode2(p->ramaDer, paso+1, Frec, aux1, aux2);
		}
	}
}

/*
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1)
Recibe:	u0:	inicio tiempo usuario
		s0:	inicio tiempo sistema
		w0: inicio tiempo real
		u1: final tiempo usuario
		s1: final tiempo sistema
		w1: final tiempo real
	 bytes:	tamaño del archivo original
	    cd: boolean para saber si es compresión o descompresión
Muestra los resultados del rendimiento temporal dentro de un espacio de tiempo acotado
*/
void rendimiento(double u0, double s0, double w0, double u1, double s1, double w1, int bytes, bool cd, char nombre[150])
{
	FILE *rendimiento;
	if(cd){
		rendimiento = fopen("out/compresion.txt", "a");
		fprintf(rendimiento, "\n\n    COMPRESIÓN\n    de archivo %s de %d bytes\n", nombre, bytes);
	}
	else{
		rendimiento = fopen("out/descompresion.txt", "a");
		fprintf(rendimiento, "\n\n    DESCOMPRESIÓN\n    de archivo %s de %d bytes\n", nombre, bytes);
	}
	// Cálculo del tiempo de ejecución del programa
	fprintf(rendimiento, "\n");
	fprintf(rendimiento, "real (Tiempo total)  %.10f s\n",  w1 - w0);
	fprintf(rendimiento, "user (Tiempo de procesamiento en CPU) %.10f s\n",  u1 - u0);
	fprintf(rendimiento, "sys (Tiempo en acciones de E/S)  %.10f s\n",  s1 - s0);
	fprintf(rendimiento, "CPU/Wall   %.10f %% \n",100.0 * (u1 - u0 + s1 - s0) / (w1 - w0));
	fprintf(rendimiento, "\n");
	
	// Mostrar los tiempos en formato exponecial
	fprintf(rendimiento, "\n");
	fprintf(rendimiento, "real (Tiempo total)  %.10e s\n",  w1 - w0);
	fprintf(rendimiento, "user (Tiempo de procesamiento en CPU) %.10e s\n",  u1 - u0);
	fprintf(rendimiento, "sys (Tiempo en acciones de E/S)  %.10e s\n",  s1 - s0);
	fprintf(rendimiento, "CPU/Wall   %.10f %% \n",100.0 * (u1 - u0 + s1 - s0) / (w1 - w0));
	fprintf(rendimiento, "\n");
	fclose(rendimiento);
}
