#include <stdio.h>
#include "disenio.h"
#include "ascii_art.h"

void letra(short x, short y, char l){
	gotoxy(x,y);
	switch(l){
	case 'C':
		colorForeground("magenta claro");
		printf("%c%c%c%c",220,223,223,223);
		gotoxy(x,y+1);
		colorBackground("azul");
		printf("%c",223);
		gotoxy(x,y+2);
		printf(" ");
		colorForeground("verde claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x+1,y+4);
		printf("%c%c%c",223,223,223);

		colorDefault();
		break;

	case 'O':
		colorForeground("magenta claro");
		printf("%c%c%c%c%c%c",220,223,223,223,223,220);
		gotoxy(x,y+1);
		colorBackground("azul");
		printf("%c",223);
		gotoxy(x+5,y+1);
		printf("%c",223);
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+5,y+2);
		printf(" ");
		colorForeground("verde claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x+5,y+3);
		printf("%c",219);
		gotoxy(x+1,y+4);
		printf("%c%c%c%c",223,223,223,223);

		colorDefault();
		break;

	case 'M':
		colorForeground("magenta claro");
		printf("%c%c   %c%c",219,220,220,219);
		gotoxy(x+2,y+1);
		printf("%c %c",223,223);
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+6,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x+3,y+1);
		printf("%c",220);
		gotoxy(x,y+2);
		printf("%c     %c",219,219);
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("%c     %c",219,219);
		gotoxy(x,y+4);
		printf("%c     %c",223,223);

		colorDefault();
		break;

	case 'P':
		colorForeground("magenta claro");
		printf("%c%c%c%c%c",219,223,223,223,220);
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x,y+2);
		printf("%c%c%c%c",219,223,223,223);
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x,y+4);
		printf("%c",223);

		colorDefault();
		break;

	case 'R':
		colorForeground("magenta claro");
		printf("%c%c%c%c%c",219,223,223,223,220);
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x,y+2);
		printf("%c%c%c%c%c",219,223,223,223,220);
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("%c   %c",219,219);
		gotoxy(x,y+4);
		printf("%c   %c",223,223);

		colorDefault();
		break;

	case 'I':
		colorForeground("magenta claro");
		printf("%c%c%c",223,219,223);
		colorBackground("azul");
		gotoxy(x+1,y+1);
		printf("%c",223);
		gotoxy(x+1,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("verde claro");
		gotoxy(x+1,y+3);
		printf("%c",219);
		gotoxy(x,y+4);
		printf("%c%c%c",223,223,223);

		colorDefault();
		break;

	case 'A':
		colorForeground("magenta claro");
		printf("%c%c%c%c%c",220,223,223,223,220);
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x,y+2);
		printf("%c%c%c%c%c",219,223,223,223,219);
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("%c   %c",219,219);
		gotoxy(x,y+4);
		printf("%c   %c",223,223);

		colorDefault();
		break;

	case 'H':
		colorForeground("magenta claro");
		printf("%c   %c",219,219);
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x+1,y+2);
		printf("%c%c%c",223,223,223);
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("%c   %c",219,219);
		gotoxy(x,y+4);
		printf("%c   %c",223,223);

		colorDefault();
		break;

	case 'V':
		colorForeground("magenta claro");
		printf("%c   %c",219,219);
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("%c%c %c%c",223,220,220,223);
		gotoxy(x+2,y+4);
		printf("%c",223);

		colorDefault();
		break;

	case 'D':
		colorForeground("magenta claro");
		printf("%c%c%c%c%c",219,223,223,223,220);
		gotoxy(x,y+1);
		colorBackground("azul");
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorForeground("verde claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x+4,y+3);
		printf("%c",219);
		gotoxy(x,y+4);
		printf("%c%c%c%c",223,223,223,223);

		colorDefault();
		break;

	case 'E':
		colorForeground("magenta claro");
		printf("%c%c%c%c",219,223,223,223);
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x,y+2);
		printf("%c%c%c",219,223,223);
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x,y+4);
		printf("%c%c%c%c",223,223,223,223);

		colorDefault();
		break;

	case 'S':
		colorForeground("magenta claro");
		printf("%c%c%c%c",220,223,223,223);
		gotoxy(x,y+1);
		colorBackground("azul");
		printf("%c",223);
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x+1,y+2);
		printf("%c%c%c",223,223,220);
		colorForeground("verde claro");
		gotoxy(x+3,y+3);
		printf("%c",219);
		gotoxy(x,y+4);
		printf("%c%c%c",223,223,223);

		colorDefault();
		break;
	}
}

void menu(short x, short y, char l){
	gotoxy(x,y);
	switch(l){
	case 'C':
		colorForeground("blanco");
		printf("%c%c%c%c",220,223,223,223);
		gotoxy(x,y+1);
		colorBackground("cian claro");
		printf("%c",223);
		gotoxy(x,y+2);
		printf(" ");
		colorForeground("magenta claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x+1,y+4);
		printf("%c%c%c",223,223,223);

		colorDefault();
		break;

	case 'O':
		colorForeground("blanco");
		printf("%c%c%c%c%c%c",220,223,223,223,223,220);
		gotoxy(x,y+1);
		colorBackground("cian claro");
		printf("%c",223);
		gotoxy(x+5,y+1);
		printf("%c",223);
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+5,y+2);
		printf(" ");
		colorForeground("magenta claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x+5,y+3);
		printf("%c",219);
		gotoxy(x+1,y+4);
		printf("%c%c%c%c",223,223,223,223);

		colorDefault();
		break;

	case 'M':
		colorForeground("blanco");
		printf("%c%c   %c%c",219,220,220,219);
		gotoxy(x+2,y+1);
		printf("%c %c",223,223);
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+6,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x+3,y+1);
		printf("%c",220);
		gotoxy(x,y+2);
		printf("%c     %c",219,219);
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("%c     %c",219,219);
		gotoxy(x,y+4);
		printf("%c     %c",223,223);

		colorDefault();
		break;

	case 'P':
		colorForeground("blanco");
		printf("%c%c%c%c%c",219,223,223,223,220);
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x,y+2);
		printf("%c%c%c%c",219,223,223,223);
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x,y+4);
		printf("%c",223);

		colorDefault();
		break;

	case 'R':
		colorForeground("blanco");
		printf("%c%c%c%c%c",219,223,223,223,220);
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x,y+2);
		printf("%c%c%c%c%c",219,223,223,223,220);
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("%c   %c",219,219);
		gotoxy(x,y+4);
		printf("%c   %c",223,223);

		colorDefault();
		break;

	case 'I':
		colorForeground("blanco");
		printf("%c%c%c",223,219,223);
		colorBackground("cian claro");
		gotoxy(x+1,y+1);
		printf("%c",223);
		gotoxy(x+1,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("magenta claro");
		gotoxy(x+1,y+3);
		printf("%c",219);
		gotoxy(x,y+4);
		printf("%c%c%c",223,223,223);

		colorDefault();
		break;

	case 'A':
		colorForeground("blanco");
		printf("%c%c%c%c%c",220,223,223,223,220);
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x,y+2);
		printf("%c%c%c%c%c",219,223,223,223,219);
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("%c   %c",219,219);
		gotoxy(x,y+4);
		printf("%c   %c",223,223);

		colorDefault();
		break;

	case 'H':
		colorForeground("blanco");
		printf("%c   %c",219,219);
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x+1,y+2);
		printf("%c%c%c",223,223,223);
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("%c   %c",219,219);
		gotoxy(x,y+4);
		printf("%c   %c",223,223);

		colorDefault();
		break;

	case 'V':
		colorForeground("blanco");
		printf("%c   %c",219,219);
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("%c%c %c%c",223,220,220,223);
		gotoxy(x+2,y+4);
		printf("%c",223);

		colorDefault();
		break;

	case 'D':
		colorForeground("blanco");
		printf("%c%c%c%c%c",219,223,223,223,220);
		gotoxy(x,y+1);
		colorBackground("cian claro");
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorForeground("magenta claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x+4,y+3);
		printf("%c",219);
		gotoxy(x,y+4);
		printf("%c%c%c%c",223,223,223,223);

		colorDefault();
		break;

	case 'E':
		colorForeground("blanco");
		printf("%c%c%c%c",219,223,223,223);
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x,y+2);
		printf("%c%c%c",219,223,223);
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x,y+4);
		printf("%c%c%c%c",223,223,223,223);

		colorDefault();
		break;

	case 'S':
		colorForeground("blanco");
		printf("%c%c%c%c",220,223,223,223);
		gotoxy(x,y+1);
		colorBackground("cian claro");
		printf("%c",223);
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x+1,y+2);
		printf("%c%c%c",223,223,220);
		colorForeground("magenta claro");
		gotoxy(x+3,y+3);
		printf("%c",219);
		gotoxy(x,y+4);
		printf("%c%c%c",223,223,223);

		colorDefault();
		break;

	case 'F':
		colorForeground("blanco");
		printf("%c%c%c%c",219,223,223,223);
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x,y+2);
		printf("%c%c%c",219,223,223);
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x,y+4);
		printf("%c",223);

		colorDefault();
		break;

	case 'N':
		colorForeground("blanco");
		printf("%c%c   %c",219,220,219);
		gotoxy(x+2,y+1);
		printf("%c  %c",223,219);
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("%c",223);
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x+3,y+1);
		printf("%c",220);
		gotoxy(x,y+2);
		printf("%c   %c%c",219,223,219);
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("%c    %c",219,219);
		gotoxy(x,y+4);
		printf("%c    %c",223,223);

		colorDefault();
		break;

	case 'U':
		colorForeground("blanco");
		printf("%c   %c",219,219);
		gotoxy(x,y+1);
		colorBackground("cian claro");
		printf("%c",223);
		gotoxy(x+4,y+1);
		printf("%c",223);
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorForeground("magenta claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("%c",219);
		gotoxy(x+4,y+3);
		printf("%c",219);
		gotoxy(x+1,y+4);
		printf("%c%c%c",223,223,223);

		colorDefault();
		break;
	}
}

void pochita(short x, short y){
	//Texto gris claro, fondo negro
	colorForeground("gris claro");
	gotoxy(x+2,y);
	printf("%c",220);
	gotoxy(x+8,y);
	printf("%c%c%c",220,220,220);
	gotoxy(x,y+1);
	printf("%c",220);
	gotoxy(x,y+2);
	printf("%c",219);
	gotoxy(x+1,y+3);
	printf("%c",223);
	gotoxy(x+3,y+4);
	printf("%c",223);

	//Texto gris claro, fondo blanco
	colorBackground("blanco");
	gotoxy(x+3,y);
	printf("%c%c%c%c%c",223,223,223,223,223);
	gotoxy(x+1,y+1);
	printf("%c         %c",223,223);

	gotoxy(x+2,y+3);
	printf("%c     ",220);
	gotoxy(x+4,y+4);
	printf("%c%c%c",220,220,220);
	gotoxy(x+17,y+3);
	printf("%c",223);
	gotoxy(x+17,y+4);
	printf(" ");
	gotoxy(x+12,y+5);
	printf("%c",220);
	gotoxy(x+16,y+5);
	printf("%c",220);

	//Texto gris oscuro, fondo blanco
	colorForeground("gris oscuro");
	gotoxy(x+1,y+2);
	printf("        %c",220);
	gotoxy(x+8,y+3);
	printf("%c",220);
	gotoxy(x+7,y+4);
	printf("%c",220);
	
	//Texto gris oscuro, fondo magenta
	colorBackground("magenta claro");
	gotoxy(x+7,y+6);
	printf("%c%c",223,223);
	gotoxy(x+7,y+7);
	printf("  ");
	
	//Texto gris oscuro, fondo gris claro
	colorBackground("gris claro");
	gotoxy(x+12,y+1);
	printf("%c",220);
	gotoxy(x+8,y+4);
	printf("%c   ",223);
	gotoxy(x+9,y+3);
	printf("%c  ",223);
	gotoxy(x+10,y+2);
	printf("%c%c    %c%c",223,223,223,223);
	gotoxy(x+6,y+5);
	printf("%c   %c ",219,220);
	gotoxy(x+18,y+3);
	printf("  %c%c",223,223);
	gotoxy(x+18,y+4);
	printf("     %c",223);
	gotoxy(x+17,y+5);
	printf("        %c",223);
	gotoxy(x+9,y+6);
	printf("%c                 %c",219,219);
	gotoxy(x+10,y+7);
	printf("%c                 %c",220,219);
	gotoxy(x+11,y+8);
	printf("%c                %c",219,219);
	gotoxy(x+12,y+9);
	printf("%c%c              %c",223,223,219);
	gotoxy(x+10,y+10);
	printf("%c      %c%c %c   %c%c",219,220,220,220,220,220);
	gotoxy(x+19,y+11);
	printf("%c%c%c%c",219,220,220,220);

	//Texto gris oscuro, fondo negro
	colorBackground("negro");
	gotoxy(x+13,y+1);
	printf("%c%c%c",220,220,220);
	gotoxy(x+18,y+2);
	printf("%c%c",220,220);
	gotoxy(x+24,y+4);
	printf("%c",220);
	gotoxy(x+26,y+5);
	printf("%c",220);
	gotoxy(x+9,y+7);
	printf("%c",223);
	gotoxy(x+11,y+9);
	printf("%c",220);
	gotoxy(x+26,y+10);
	printf("%c%c",223,223);
	gotoxy(x+11,y+11);
	printf("%c%c%c%c%c%c",223,223,223,223,223,223);
	gotoxy(x+23,y+11);
	printf("%c",223);

	//Texto rojo, fondo negro
	colorForeground("rojo");
	gotoxy(x+16,y+1);
	printf("%c%c%c%c%c%c%c%c%c%c%c",220,219,219,219,219,219,219,219,219,219,219);
	gotoxy(x+23,y+2);
	printf("%c%c%c%c",220,220,219,223);
	gotoxy(x+23,y+3);
	printf("%c%c",223,223);

	gotoxy(x+32,y+4);
	printf("%c%c%c",220,220,220);
	gotoxy(x+31,y+5);
	printf("%c%c %c%c",223,220,220,223);
	gotoxy(x+28,y+6);
	printf("%c%c%c  %c",219,223,219,219);
	gotoxy(x+30,y+7);
	printf("%c %c%c",219,220,223);
	gotoxy(x+29,y+8);
	printf("%c%c%c%c",219,220,220,223);

	colorBackground("rojo");
	gotoxy(x+13,y+3);
	printf("%c%c%c",219,219,219);
	gotoxy(x+12,y+4);
	printf("%c%c%c%c%c",219,219,219,219,219);

	colorBackground("blanco");
	gotoxy(x+16,y+3);
	printf("%c",220);
	gotoxy(x+13,y+5);
	printf("%c%c%c",223,223,223);
	colorBackground("gris claro");
	gotoxy(x+12,y+3);
	printf("%c",220);
	colorBackground("gris oscuro");
	gotoxy(x+22,y+3);
	printf("%c",223);

	colorDefault();
}