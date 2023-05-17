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
#define TABLA_MAX_LINEAS 522
#define TABLA_MAX_COLUMNAS 500

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
	char tabla[150];
}direcciones;

unsigned char *Arreglodeprueba;
elemento *prueba;

int main()
{
	clrscr();

	int eleccion = 0;
	while(1){
		disenioMenu();
		scanf("%d",&eleccion);
		fflush(stdin);
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	
	//--------------------------------------------------------------//
	//																//
	//				 ENTRADA Y LECTURA DE LOS ARCHIVOS				//
	//																//
	//--------------------------------------------------------------//

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
	Arreglodeprueba = (unsigned char *) malloc(n_bytes * sizeof(unsigned char));
	fread(A, n_bytes, 1, archivo);		// Almacenar en A TODO lo que está en archivo
	for(i = 0; i < n_bytes; i++){
		Arreglodeprueba[i] = A[i];
	}
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
	prueba = malloc(tam_lista * sizeof(elemento));
	SelectionSort(&mi_lista);
	for(i = 0; i < tam_lista; i++){
		TablaResumida[i] = Element(&mi_lista, i);
		prueba[i] = Element(&mi_lista, i);
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
	/*
	while(mi_lista.tam != 0){
		printf("\n");
		for(i = 0; i < Size(&mi_lista); i++){
			printf("%d ", Element(&mi_lista,i).frecuencia);
		}
		S1 = DequeuePos(&mi_lista);
		//printf("%d ", S1->e.frecuencia);			// Comentarios para verificar en caso de ser necesario ( Se borran cuando el programa ya funcione)
		S2 = DequeuePos(&mi_lista);
		//printf("%d ", S2->e.frecuencia);			// Mismo que arriba
		
		// Modificación de los valores para agregar un nodo simple
		N.e.frecuencia = S1->e.frecuencia + S2->e.frecuencia;
		N.ramaIzq = S1;
		N.ramaDer = S2;

		// Insertar el nodo ordenado
		if(mi_lista.tam != 0){
			pos_aux = 0;
			for(i = 0; i < Size(&mi_lista); i++){
				if(N.e.frecuencia > Element(&mi_lista, i).frecuencia){
					pos_aux = i;
				}
			}
			InsertNodoIn(&mi_lista, N, pos_aux-1);
			//InsertNodoIn(&mi_lista, N, 0);				// Lo quiero ordenado
			//SelectionSort(&mi_lista);					// Si no se puede insertar ordenado
		}
		// Terminar cuando la lista esté vacía, se guarda la posición de raiz
		else{
			raiz = &N;
			break;
		}
	}*/
	while(mi_lista.tam > 1){
		//printf("\n");
		/**(i = 0; i < Size(&mi_lista); i++){
			//printf("%d ", Element(&mi_lista,i).frecuencia);
		}*/
		S1 = DequeuePos(&mi_lista);
		//printf("%d ", S1->e.frecuencia);			// Comentarios para verificar en caso de ser necesario ( Se borran cuando el programa ya funcione)
		S2 = DequeuePos(&mi_lista);
		//printf("%d ", S2->e.frecuencia);			// Mismo que arriba
		
		// Modificación de los valores para agregar un nodo simple
		N.e.frecuencia = S1->e.frecuencia + S2->e.frecuencia;
		N.ramaIzq = S1;
		N.ramaDer = S2;

		pos_aux = 0;
		for(i = 0; i < mi_lista.tam; i++){
			//printf("\n Comparando %d con %d",N.e.frecuencia,Element(&mi_lista, i).frecuencia);
			if(N.e.frecuencia > Element(&mi_lista, i).frecuencia){
				pos_aux = i;
				//printf(" ahora: %d",pos_aux);
				//i = mi_lista.tam;
			}
			else
			{
				i = mi_lista.tam;
			}
		}
		//printf("\n Se colocara en la posicion %d", pos_aux);
		if(mi_lista.tam != 0){
			InsertNodoIn2(&mi_lista, ElementPosition(&mi_lista,pos_aux), N, 0);
		}
		else{
			raiz = &N;
		}
	}
	
	VerLigas(raiz);

	//--------------------------------------------------------------//
	//																//
	//	 REALIZAR EL RECORRIDO DEL ÁRBOL PARA OBTENER EL CONJUNTO	//
	//		DE BITS CODIFICADOS Y EL TAMAÑO DE DICHO CONJUNTO		//
	//																//
	//--------------------------------------------------------------//

	//int n_bits=sizeof(unsigned char)*8;
	raiz->e.code = 0;
	raiz->e.limite = 0;		// Para el nodo raiz
	//Frec[raiz->e.c] = raiz->e;		// Se mete al arreglo
	
	//codePreOrden(raiz, Frec);
	unsigned char caux = 0;
	InordenCode(raiz, caux, 0, Frec);

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

	//--------------------------------------------------------------//
	//																//
	//	  		 TERMINAR DE IMPRIMIR EN EL ARCHIVO DE TEXTO		//
	//																//
	//--------------------------------------------------------------//
	
	fprintf(TABLA, "\nBits sobrantes: %d", 8-pos_bit);
	fprintf(TABLA, "\n\nTABLA DE FRECUENCIAS (VALOR):\n");
	for(i = 0; i < tam_lista; i++){
		fprintf(TABLA, "%d:%d\n", TablaResumida[i].c, TablaResumida[i].frecuencia);
	}
	fprintf(TABLA, "\n\nTABLA DE FRECUENCIAS (CARACTER):\n");
	for(i = 0; i < tam_lista; i++){
		fprintf(TABLA, "%c:%d\n", TablaResumida[i].c, TablaResumida[i].frecuencia);
	}
	fclose(TABLA);
	
	/*
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
	}*/
	/*
	printf("\n frecuencia en %d (%c): %d ",111,111,Frec[111].frecuencia);
	printf("\n tamaño de %s: %d", Frec[72].codificado, strlen(Frec[72].codificado));
	*/
	esperar(2000);
	
	//-----------------

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
	//fwrite(A, n_bytes, sizeof(unsigned char), archivo);
	fclose(archivo);
	procesoTerminado = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	// Lee el archivo de texto de la tabla de frecuencias y almacena los datos
	FILE *tablatxt;
	tablatxt = fopen(D0.tabla, "r");
	if(tablatxt == NULL){
		printf("\n Error al abrir el archivo: %s", D0.tabla);
		exit(1);
	}
	// Almacena línea por línea en un arreglo
	char line[TABLA_MAX_COLUMNAS];
	int n_lineas_tabla = 0;
	unsigned char linea[TABLA_MAX_LINEAS][TABLA_MAX_COLUMNAS];
	while (fgets(linea[n_lineas_tabla], TABLA_MAX_COLUMNAS, tablatxt)){
		//printf("\n%d",strlen(linea[n_lineas_tabla]));
		linea[n_lineas_tabla][strlen(linea[n_lineas_tabla]) - 1] = '\0';
		n_lineas_tabla++;
	}
	printf("\nTRUENAAAAAAAAAAAAA");
	n_bytes = atoi(strrchr(linea[2], ':')+2);
	n_bytes_salida = atoi(strrchr(linea[1], ':')+2);
	bits_sobrantes = atoi(strrchr(linea[3], ':')+2);
	printf("\nTRUENAA2");
	//printf("\n NUM BYTES:%s", strrchr(linea[1], ':')+2);
	//printf("\n NUM BYTES SALIDA:%s", strrchr(linea[2], ':')+2);
	fclose(tablatxt);


	//strrchr(D0.entrada, '.')
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
		//printf("TRUENAAAAAAAAAAAAA");
		//printf("%s\n", linea[i]);
		if(strrchr(linea[i], ':') == NULL){
			i = n_lineas_tabla;
		}
		else{
			//printf("%s\n",linea[i], i);
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
			//printf("\n%s: %s", caracter, num);
			e.c = atoi(caracter);
			e.frecuencia = atoi(num);
			Add(&mi_lista, e);
		}
		/*
		printf("%s i:%d\n",linea[i], i);
		if(empiezaTabla){
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
			printf("\n%s OwO %s", caracter, num);
			e.c = atoi(caracter);
			e.frecuencia = atoi(num);
			Add(&mi_lista, e);
		}
		if(strcmp(linea[i], "VALOR NUMERICO:") == 0){
			empiezaTabla = true;
			printf("PASA");
		}*/
	}

	printf("TRUENAAAAAAAAAAAAA");
	printf("\nNEW  ORIGINAL");
	for(i = 0; i < Size(&mi_lista); i++){
		printf("\n%c: %d\t\t%c: %d", Element(&mi_lista, i).c, Element(&mi_lista, i).frecuencia, prueba[i].c, prueba[i].frecuencia);
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
		/*printf("\n");
		for(i = 0; i < Size(&mi_lista); i++){
			printf("%d ", Element(&mi_lista,i).frecuencia);
		}*/
		S1 = DequeuePos(&mi_lista);
		//printf("%d ", S1->e.frecuencia);			// Comentarios para verificar en caso de ser necesario ( Se borran cuando el programa ya funcione)
		S2 = DequeuePos(&mi_lista);
		//printf("%d ", S2->e.frecuencia);			// Mismo que arriba
		
		// Modificación de los valores para agregar un nodo simple
		N.e.frecuencia = S1->e.frecuencia + S2->e.frecuencia;
		N.ramaIzq = S1;
		N.ramaDer = S2;

		pos_aux = 0;
		for(i = 0; i < mi_lista.tam; i++){
			//printf("\n Comparando %d con %d",N.e.frecuencia,Element(&mi_lista, i).frecuencia);
			if(N.e.frecuencia > Element(&mi_lista, i).frecuencia){
				pos_aux = i;
				//printf(" ahora: %d",pos_aux);
				//i = mi_lista.tam;
			}
			else
			{
				i = mi_lista.tam;
			}
		}
		//printf("\n Se colocara en la posicion %d", pos_aux);
		if(mi_lista.tam != 0){
			InsertNodoIn2(&mi_lista, ElementPosition(&mi_lista,pos_aux), N, 0);
		}
		else{
			raiz = &N;
		}
	}

	VerLigas(raiz);

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

	printf("\n");
	posicion p = raiz;
	for(i = 0; i < n_bytes; i++){
		//printf("%c",A[i]);
		for(j = 7; j >= 0; j--){
			//printf("%d",CONSULTARBIT(A[i],j));
			if(i == n_bytes-1 && j <= bits_sobrantes){
				j = -1;
			}
		}
		//printf(" ");
	}
	k = 0;
	for(i = 0; i < n_bytes; i++){
		//printf("%c",A[i]);
		for(j = 7; j >= 0; j--){
			if(CONSULTARBIT(A[i], j) == 1){
				p = p->ramaDer;
			}else{
				p = p->ramaIzq;
			}
			if(p->ramaDer == NULL && p->ramaIzq == NULL){
				//fprintf(archivo,"%c",p->e.c);
				//printf(archivo,"%c",p->e.c);
				ASalida[k] = p->e.c;
				k++;
				p = raiz;
				if(i == n_bytes-1 && j <= bits_sobrantes){
					j = -1;
				}
			}
		}
		//printf("  ");
	}
	bool bad =false;
	int contador = 0;
	for(i = 0; i < n_bytes_salida; i++){
		printf("\n%d\t%d",ASalida[i], Arreglodeprueba[i]);
		if(ASalida[i] != Arreglodeprueba[i]){
			//printf("NO CONCUERDAN");
			
			bad = true;
		}else{
			contador++;
		}
	}

	printf("\nConcordaron %d de %f", contador, n_bytes_salida);
	if(bad){
		printf("NO CONCUERDAN");

	}
	fwrite(ASalida, n_bytes_salida, sizeof(unsigned char), archivo);
	fclose(archivo);
int as;
	scanf("%d",&as);
	esperar(2000);
	
	procesoTerminado = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	void Comprimir()
Efecto:
	Lee las direcciones de los archivos para la compresión,
	crea un hilo en el cual se realizará lacompresión y
	muestra una pantalla de carga en lo que se realiza el proceso.
*/
void Comprimir()
{
	char direccion[150];
	char salida[150];
	char tabla[150];

	disenioCompresion();
	scanf("%s",&direccion);

	gotoxy(2, 13);
	colorForeground("blanco");
	printf("Introduzca el nombre del archivo comprimido de salida (DE PREFERENCIA OMITIR EXTENSI%cN):", 224);
	gotoxy(4, 15);
	colorDefault();
	scanf("%s",&salida);

	gotoxy(2, 19);
	colorForeground("blanco");
	printf("Introduzca el nombre del archivo con la tabla de frecuencias(DE PREFERENCIA OMITIR EXTENSI%cN):", 224);
	gotoxy(4, 24);
	colorDefault();
	scanf("%s",&tabla);

	direcciones D;
	strcpy(D.entrada, direccion);
	strcpy(D.salida, salida);
	strcpy(D.tabla, tabla);

	if(0 != pthread_create(&hilo1, NULL, procesoCompresion, &D)){
		perror("El thread no pudo crearse");
		exit(-1);
	}
	/*
	// Pantalla de carga, se seguirá realizando mientras no haya terminado la compresión
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

/*
	void Descomprimir()
Efecto:
	Lee las direcciones de los archivos para la descompresión,
	crea un hilo en el cual se realizará la descompresión y
	muestra una pantalla de carga en lo que se realiza el proceso.
*/
void Descomprimir()
{
	char direccion[150];
	char salida[150];
	char tabla[150];

	disenioDescompresion();
	scanf("%s",&direccion);
	fflush(stdin);

	gotoxy(2, 13);
	colorForeground("blanco");
	printf("Introduzca el nombre que tendr%c el archivo descomprimido (OMITIR EXTENSI%cN):",160,224);
	gotoxy(4, 15);
	colorDefault();
	scanf("%s",&salida);
	fflush(stdin);

	gotoxy(2, 19);
	colorForeground("blanco");
	printf("Introduzca el nombre del archivo de texto con la tabla de frecuencias (OMITIR EXTENSI%cN):", 224);
	gotoxy(4, 21);
	colorDefault();
	scanf("%s",&tabla);
	fflush(stdin);

	direcciones D;
	strcpy(D.entrada, direccion);
	strcpy(D.salida, salida);
	strcpy(D.tabla, tabla);

	if(0 != pthread_create(&hilo1, NULL, procesoDescompresion, &D)){
		perror("El thread no pudo crearse");
		exit(-1);
	}
	/*
	// Pantalla de carga, se seguirá realizando mientras no haya terminado la descompresión
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
	}*/
	pthread_join (hilo1, NULL);
	procesoTerminado = false;
	/*
	gotoxy(51, 19);
	printf("    TERMINADO     ");
	gotoxy(CONSOLE_WIDTH-1, CONSOLE_HEIGHT-1);*/
	esperar(700);
/*
	gotoxy(23,15);*/
}












void codePreOrden(posicion n, elemento *Frec){
	if(n!=NULL){
		// ProcesarNodo, asignando su código correspondiente
		asignarCodigo(n, Frec);

		codePreOrden(n->ramaIzq, Frec);
		codePreOrden(n->ramaDer, Frec);
	}
}

void asignarCodigo(posicion n, elemento *Frec){

	// Copia el código y límite (lo incrementa), para su hijo izquierdo
	if(n->ramaIzq != NULL){
		// Actualización del límite
		n->ramaIzq->e.limite = n->e.limite;		// Copia el límite
		(n->ramaIzq->e.limite)++;				// Lo incrementa

		// Actualización del bit
		n->ramaIzq->e.code = n->e.code;			// Copia el código
		// No es necesario poner 0 porque inicia en 0
		//PONE_0(n->ramaIzq->e.code, 7 - n->ramaIzq->e.limite); 			// 0 en el bit n->ramaIzq->e.limite
		if(n->ramaIzq->e.c != 0){
			Frec[n->ramaIzq->e.c] = n->ramaIzq->e;			// Se mete al arreglo
		}
	}

	// Copia el código y límite (lo incrementa), para su hijo derecho
	if(n->ramaDer != NULL){
		// Actualización del límite
		n->ramaDer->e.limite = n->e.limite;		// Copia el límite
		(n->ramaDer->e.limite)++;				// Lo incrementa
		//printf("\n%d ", n->ramaDer->e.limite);	// Para verificar en que nivel se está imprimiendo COMENTAR

		// Actualización del bit
		n->ramaDer->e.code = n->e.code;			// Copia el código
		PONE_1(n->ramaDer->e.code, 7 - n->ramaIzq->e.limite + 1); 			// 1 en el bit n->ramaIzq->e.limite
		if(n->ramaDer->e.c != 0){
			Frec[n->ramaDer->e.c] = n->ramaDer->e;				// Se mete al arreglo
		}
		
	// Para verificar que funciona COMENTAR

	//***********************************************************
	//Revisar el valor de cada bit
	int n_bits = 8;
	printf("Valor de los bits\n");
	for (int i=n_bits-1; i>=0; i--)
	printf("%d",CONSULTARBIT(n->ramaDer->e.code,i));			// Para verificar que funciona COMENTAR
	}
	printf("\nCaracter: %c");

	//************************************************************
}

void InordenCode(posicion p, unsigned char c, int paso, elemento *Frec){
	if((p->ramaIzq == NULL) && (p->ramaDer == NULL)){
		p->e.code = c;
		p->e.limite = paso;
		Frec[p->e.c] = p->e;
	}
	else{
		if(p->ramaIzq != NULL){
			InordenCode(p->ramaIzq, c, paso+1, Frec);
		}
		if(p->ramaDer != NULL){
			unsigned char aux = c;
			PONE_1(aux, 7-paso);
			InordenCode(p->ramaDer, aux, paso+1, Frec);
		}
	}
}