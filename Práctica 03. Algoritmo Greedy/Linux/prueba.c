/*

gcc prueba.c -o prueba.exe lib/disenio.c lib/ascii_art.c lib/menu.c lib/TADLista/TADListaDL.c

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

#include <windows.h>

#define CONSOLE_WIDTH 120
#define CONSOLE_HEIGHT 30

#define PESOBIT(bpos) 1<<bpos
#define CONSULTARBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)

void Comprimir();
void Descomprimir();

bool procesoTerminado = false;
pthread_t hilo1;
pthread_t hilo2;

typedef struct direcciones{
	char entrada[150];
	char salida[150];
}direcciones;

int main()
{
	clrscr();

	int eleccion = 0;
	while(1){
		disenioMenu();
		scanf("%d",&eleccion);
		switch(eleccion){
		case 1:
			Comprimir();
			break;
		case 2:
			Descomprimir();
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

void *proceso(void *arg)
{
	FILE *archivo;			// Direcci�n de tipo FILE que vamos a manipular
	unsigned char *A;		// Arreglo que almacena todos los bytes (caracteres) del archivo de entrada
	double n_bytes;			// Cantidad de bytes que tiene el archivo de entrada
	unsigned char *ASalida;	// Arreglo que almacena todos los bytes (caracteres) del archivo de salida
	double n_bytes_salida;	// Cantidad de bytes que tiene el archivo de salida
	
	direcciones D0 = *((direcciones*)arg);
	int pos_byte = 0;		// En qu� byte del nuevo arreglo est�s
	int pos_bit = 0;		// En qu� bit de cada byte est�s
	elemento *Frec;			// Tabla de frecuencias
	int i, j;
	lista mi_lista;

	Initialize(&mi_lista);
	
	// Modo binario lectura -> archivo de entrda
	archivo = fopen(D0.entrada, "rb");	
	fseek(archivo, 0, SEEK_END);		// Se posiciona al final del archivo
	n_bytes = ftell(archivo);			// Regresa el valor de la posici�n en donde est�
	rewind(archivo);					// Vuelve al inicio
	
	// Lee todos los bytes del archivo y los almacena en el arreglo de bytes, cierra el archivo.
	A = (unsigned char *) malloc(n_bytes * sizeof(unsigned char));
	fread(A, n_bytes, 1, archivo);		// Almacenar en A
	fclose(archivo);					// Cerrar archivo
	
	// Crear archivo de texto para la tabla de frecuencias y m�s informaci�n
	FILE *TABLA = fopen("Tabla.txt", "w");
	fprintf(TABLA, "Tipo de archivo de entrada: %s", strrchr(D0.entrada, '.'));
	fprintf(TABLA, "\nArchivo de entrada: %0.0lf bytes", n_bytes);
	
	// Crea la tabla de frecuencias con tama�o 256 e inicializa en 0 la frecuencia de todos los bytes
	Frec = malloc(256 * sizeof(elemento));
	for(i = 0; i < 256; i++){
		Frec[i].frecuencia = 0;
	}
	
	// Recorre todos los bytes del archivo original, y va almacenando la frecuencia de aparici�n de los
	// caracteres (bytes)
	for(i = 0; i < n_bytes; i++){
		Frec[A[i]].frecuencia++;
	}
	
	// Obtener el tama�o del arreglo de salida
	n_bytes_salida = 0;
	for(i = 0; i < 256; i++){
		if(Frec[i].frecuencia != 0){
			Frec[i].c = i;
			printf("\n%c",Frec[i].c);
			Add(&mi_lista, Frec[i]);
		}
	}
	int tam_lista = Size(&mi_lista);
	elemento *TablaResumida;
	TablaResumida = malloc(tam_lista * sizeof(elemento));
	SelectionSort(&mi_lista);
	for(i = 0; i < tam_lista; i++){
		TablaResumida[i] = Element(&mi_lista, i);
	}
	
	//----------------------------------------------------------------------------------//
	//																					//
	//		TODO: ORDENAR LA LISTA, Y A PARTIR DE LA LISTA EMPLEAR EL ALGORITMO DE		//
	//			HUFFMAN PARA CREAR EL �RBOL. (IR ALMACENANDO EN UN STRING LAS			//
	//		   FRECUENCIAS PARA EL ARCHIVO DE TEXTO CON LA TABLA DE FRECUENCIAS			//
	//																					//
	//----------------------------------------------------------------------------------//
	
	//----------------------------------------------------------------------------------//
	//																					//
	//		TODO: SE IMPLEMENTAR� EL �RBOL PARA OBTENER LOS BINARIOS CODIFICADOS		//
	//		DE CADA CARACTER, EL TAMA�O DE ESOS BINARIOS, Y EL TAMA�O DEL ARREGLO		//
	//								DE CARACTERES DE SALIDA								//
	//																					//
	//----------------------------------------------------------------------------------//
	
	//-----------------
	
	PONE_1(Frec[72].code,5);
	Frec[72].limite = 4;
	PONE_1(Frec[111].code,7);
	Frec[111].limite = 2;
	PONE_1(Frec[108].code,5);
	PONE_1(Frec[108].code,4);
	Frec[108].limite = 4;
	PONE_1(Frec[97].code,6);
	Frec[97].limite = 2;
	PONE_1(Frec[109].code,7);
	PONE_1(Frec[109].code,6);
	Frec[109].limite = 4;
	PONE_1(Frec[117].code,7);
	PONE_1(Frec[117].code,6);
	PONE_1(Frec[117].code,4);
	Frec[117].limite = 4;
	Frec[110].limite = 3;
	PONE_1(Frec[100].code,7);
	PONE_1(Frec[100].code,6);
	PONE_1(Frec[100].code,5);
	Frec[100].limite = 3;
	
	//-----------------
	
	// Obtener el tama�o del arreglo de salida
	n_bytes_salida = 0;
	for(i = 0; i < 256; i++){
		if(Frec[i].frecuencia != 0){
			n_bytes_salida += ((double) Frec[i].frecuencia * (double) Frec[i].limite);
		}
	}
	n_bytes_salida /= 8;
	n_bytes_salida = ceil(n_bytes_salida);
	fprintf(TABLA, "\nArchivo de salida: %0.0lf bytes", n_bytes_salida);
	
	// Crea el arreglo de bytes de salida inicializa los caracteres en 0
	ASalida = malloc(n_bytes_salida * sizeof(unsigned char));
	for(i = 0; i < n_bytes_salida; i++){
		ASalida[i] = 0;
	}
	
	// Recorre todos los bytes del archivo original, busca su codificaci�n binaria y modifica
	// los bits de los caracteres del arreglo de salida
	for(i = 0; i < n_bytes; i++){
		for(j = 0; j < Frec[A[i]].limite; j++){

			if(CONSULTARBIT(Frec[A[i]].code, 7-j) == 1){
				PONE_1(ASalida[pos_byte], 7-pos_bit);
			}
			pos_bit++;
			if(pos_bit == 8){
				pos_byte++;
				pos_bit = 0;
			}
		}
	}
	
	fprintf(TABLA, "\nBits sobrantes: %d bits", 8-pos_bit);
	fprintf(TABLA, "\n\nTABLA DE FRECUENCIAS:");
	for(i = 0; i < tam_lista; i++){
		fprintf(TABLA, "\n%c:%d", TablaResumida[i].c, TablaResumida[i].frecuencia);
	}
	fclose(TABLA);
	
	
	printf("\n");
	for(i = 0; i < n_bytes_salida; i++){
		for(j = 0; j < 8; j++){
			printf("%d",CONSULTARBIT(ASalida[i],7-j));
		}
		printf(" ");
	}
	printf("\n");
	for(i = 0; i < n_bytes_salida; i++){
		printf("%c",ASalida[i]);
	}
	printf("\n");
	for(i = 0; i < n_bytes_salida; i++){
		printf("%d ",ASalida[i]);
	}
	/*
	printf("\n frecuencia en %d (%c): %d ",111,111,Frec[111].frecuencia);
	printf("\n tamaño de %s: %d", Frec[72].codificado, strlen(Frec[72].codificado));
	*/
	esperar(2000);
	
	//-----------------

	//Modo binario escritura -> archivo de salida
	archivo = fopen(D0.salida, "wb");
	fwrite(ASalida, n_bytes_salida, sizeof(unsigned char), archivo);
	//fwrite(A, n_bytes, sizeof(unsigned char), archivo);
	fclose(archivo);
	procesoTerminado = true;
}

void Comprimir()
{
	char direccion[150];
	char salida[150];

	disenioCompresion();
	scanf("%s",direccion);

	gotoxy(2, 13);
	colorForeground("blanco");
	printf("Introduzca el nombre del archivo comprimido de salida (DE PREFERENCIA OMITIR EXTENSI%cN):", 224);
	gotoxy(4, 15);
	colorDefault();
	scanf("%s",salida);

	direcciones D;
	strcpy(D.entrada, direccion);
	strcpy(D.salida, salida);

	if(0 != pthread_create(&hilo1, NULL, proceso, &D)){
		perror("El thread no pudo crearse");
		exit(-1);
	}
	/*
	clrscr();
	pochita(42,4);
	gotoxy(52, 19);
	colorForeground("rojo claro");
	printf("Comprimiendo");
	while(!procesoTerminado){
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		esperar(500);
		gotoxy(64, 19);
		printf(".  ");
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		esperar(500);
		gotoxy(65, 19);
		printf(".");
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		esperar(500);
		gotoxy(66, 19);
		printf(".");
	}*/
	pthread_join (hilo1, NULL);
	procesoTerminado = false;
	gotoxy(52, 19);
	printf("   TERMINADO   ");
	gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
	esperar(700);

	gotoxy(23,15);
}

void Descomprimir()
{
	char direccion[150];
	char salida[150];

	disenioDescompresion();
	scanf("%s",direccion);

	gotoxy(2, 13);
	colorForeground("blanco");
	printf("Introduzca el nombre del archivo comprimido de salida (DE PREFERENCIA OMITIR EXTENSI%cN):", 224);
	gotoxy(4, 15);
	colorDefault();
	scanf("%s",salida);

	direcciones D;
	strcpy(D.entrada, direccion);
	strcpy(D.salida, salida);

	if(0 != pthread_create(&hilo1, NULL, proceso, &D)){
		perror("El thread no pudo crearse");
		exit(-1);
	}

	clrscr();
	pochita(42,4);
	gotoxy(51, 19);
	colorForeground("rojo claro");
	printf("Descomprimiendo");
	while(!procesoTerminado){
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		esperar(500);
		gotoxy(66, 19);
		printf(".  ");
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		esperar(500);
		gotoxy(67, 19);
		printf(".");
		gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
		esperar(500);
		gotoxy(68, 19);
		printf(".");
	}
	pthread_join (hilo1, NULL);
	procesoTerminado = false;
	gotoxy(51, 19);
	printf("    TERMINADO     ");
	gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);
	esperar(700);

	gotoxy(23,15);
}