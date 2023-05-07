#include <stdio.h>
#include "disenio.h"
#include "ascii_art.h"
#include "menu.h"

void disenioMenu()
{
	clrscr();

	short margen_izq = 20;
	int m = margen_izq;
	menu(m, 1, 'C');
	m += 5;
	menu(m, 1, 'O');
	m += 7;
	menu(m, 1, 'D');
	m += 6;
	menu(m, 1, 'I');
	m += 4;
	menu(m, 1, 'F');
	m += 5;
	menu(m, 1, 'I');
	m += 4;
	menu(m, 1, 'C');
	m += 5;
	menu(m, 1, 'A');
	m += 6;
	menu(m, 1, 'C');
	m += 5;
	menu(m, 1, 'I');
	m += 4;
	menu(m, 1, 'O');
	m += 7;
	menu(m, 1, 'N');
	m += 5;

	m += 7;

	menu(m, 1, 'D');
	m += 6;
	menu(m, 1, 'E');

	margen_izq = 39;
	m = margen_izq;
	menu(m, 6, 'H');
	m += 6;
	menu(m, 6, 'U');
	m += 6;
	menu(m, 6, 'F');
	m += 5;
	menu(m, 6, 'F');
	m += 5;
	menu(m, 6, 'M');
	m += 8;
	menu(m, 6, 'A');
	m += 6;
	menu(m, 6, 'N');
	m += 5;

	gotoxy(3, 12);
	colorForeground("blanco");
	printf("1. Comprimir un archivo.\n   2. Descomprimir un archivo.\n   3. Salir.");
	gotoxy(2, 16);
	printf("Seleccione la opci%cn deseada: ",162);
	colorDefault();
}

void disenioCompresion()
{
	clrscr();

	short margen_izq = 10;
	int m = margen_izq;
	letra(m, 1, 'C');
	m += 5;
	letra(m, 1, 'O');
	m += 7;
	letra(m, 1, 'M');
	m += 8;
	letra(m, 1, 'P');
	m += 6;
	letra(m, 1, 'R');
	m += 6;
	letra(m, 1, 'I');
	m += 4;
	letra(m, 1, 'M');
	m += 8;
	letra(m, 1, 'I');
	m += 4;
	letra(m, 1, 'R');
	m += 6;

	m += 7;

	letra(m, 1, 'A');
	m += 6;
	letra(m, 1, 'R');
	m += 6;
	letra(m, 1, 'C');
	m += 5;
	letra(m, 1, 'H');
	m += 6;
	letra(m, 1, 'I');
	m += 4;
	letra(m, 1, 'V');
	m += 6;
	letra(m, 1, 'O');

	gotoxy(2, 7);
	colorForeground("blanco");
	printf("Introduzca la direcci%cn del archivo a comprimir:",162);
	gotoxy(4, 9);
	colorDefault();
}

void disenioDescompresion()
{
	clrscr();

	short margen_izq = 2;
	int m = margen_izq;
	letra(m, 1, 'D');
	m += 6;
	letra(m, 1, 'E');
	m += 5;
	letra(m, 1, 'S');
	m += 5;

	letra(m, 1, 'C');
	m += 5;
	letra(m, 1, 'O');
	m += 7;
	letra(m, 1, 'M');
	m += 8;
	letra(m, 1, 'P');
	m += 6;
	letra(m, 1, 'R');
	m += 6;
	letra(m, 1, 'I');
	m += 4;
	letra(m, 1, 'M');
	m += 8;
	letra(m, 1, 'I');
	m += 4;
	letra(m, 1, 'R');
	m += 6;

	m += 7;

	letra(m, 1, 'A');
	m += 6;
	letra(m, 1, 'R');
	m += 6;
	letra(m, 1, 'C');
	m += 5;
	letra(m, 1, 'H');
	m += 6;
	letra(m, 1, 'I');
	m += 4;
	letra(m, 1, 'V');
	m += 6;
	letra(m, 1, 'O');

	gotoxy(2, 7);
	colorForeground("blanco");
	printf("Introduzca la direcci%cn del archivo a comprimir:",162);
	gotoxy(4, 9);
	colorDefault();
}