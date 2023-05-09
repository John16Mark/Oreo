/*

gcc prueba.c -o prueba.exe lib/disenio.c lib/ascii_art.c lib/menu.c lib/TADLista/TADListaDL.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
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
	FILE *archivo;
	unsigned char *A;
	double n_bytes;
	direcciones D0 = *((direcciones*)arg);

	//-----------------
	/*
	int j;
	int posicion = 0;
	int mod = 0;
	elemento *Frec;
	Frec = malloc(256 * sizeof(elemento));
	int i;
	for(i = 0; i < 256; i++){
		Frec[i].frecuencia = 0;
	}
	Frec[72].codificado = "0010";
	Frec[111].codificado = "10";
	Frec[108].codificado = "0011";
	Frec[97].codificado = "01";
	Frec[109].codificado = "1100";
	Frec[117].codificado = "1101";
	Frec[110].codificado = "000";
	Frec[100].codificado = "111";
	int tam = 6;
	unsigned char *ASalida = malloc(tam * sizeof(unsigned char));
	for(i = 0; i < tam; i++){
		ASalida[i] = 0;
	}
	for(i = 0; i < strlen(Frec[72].codificado); i++){
		//printf("%d ",CONSULTARBIT(Frec[72].codificado,i));
		printf("%d ",Frec[72].codificado[i]);
	}
	printf("\n");
	*/
	//-----------------

	//Modo binario lectura -> archivo de entrda
	archivo = fopen(D0.entrada, "rb");	
	fseek(archivo, 0, SEEK_END);
	n_bytes = ftell(archivo);
	rewind(archivo);

	//Lee todos los bytes del archivo y los almacena en el arreglo de bytes, cierra el archivo.
	A = (unsigned char *) malloc(n_bytes * sizeof(unsigned char));
	fread(A, n_bytes, 1, archivo);
	fclose(archivo);

	//-----------------
	/*
	for(i = 0; i < n_bytes; i++){
		printf("%d ",A[i]);
		Frec[A[i]].frecuencia++;
	}
	printf("\n");
	for(i = 0; i < n_bytes; i++){
		printf("%s ",Frec[A[i]].codificado);
	}
	printf("\n");
	// Recorre todos los caracteres del archivo original, busca su codificación binaria y modifica
	// los bits de los caracteres del arreglo de salida
	for(i = 0; i < n_bytes; i++){
		for(j = 0; j < strlen(Frec[A[i]].codificado); j++){
			if(Frec[A[i]].codificado[j] == '1'){
				PONE_1(ASalida[posicion], 7-mod);
			}
			//printf("%c",Frec[A[i]].codificado[j]);
			mod++;
			if(mod == 8){
				posicion++;
				mod = 0;
			}
		}
	}
	printf("\n");
	for(i = 0; i < tam; i++){
		for(j = 0; j < 8; j++){
			printf("%d",CONSULTARBIT(ASalida[i],7-j));
		}
		printf(" ");
	}
	printf("\n");
	for(i = 0; i < tam; i++){
		printf("%c",ASalida[i]);
	}
	printf("\n");
	for(i = 0; i < tam; i++){
		printf("%d ",ASalida[i]);
	}

	printf("\n frecuencia en %d (%c): %d ",111,111,Frec[111].frecuencia);
	printf("\n tamaño de %s: %d", Frec[72].codificado, strlen(Frec[72].codificado));
	esperar(2000);
	*/
	//-----------------

	//Modo binario escritura -> archivo de salida
	archivo = fopen(D0.salida, "wb");
	//fwrite(ASalida, tam, sizeof(unsigned char), archivo);
	fwrite(A, n_bytes, sizeof(unsigned char), archivo);
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