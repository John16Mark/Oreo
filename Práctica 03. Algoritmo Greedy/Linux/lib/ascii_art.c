#include <stdio.h>
#include "disenio.h"
#include "ascii_art.h"

void letra(short x, short y, char l){
	gotoxy(x,y);
	switch(l){
	case 'C':
		colorForeground("magenta claro");
		printf("▄▀▀▀");
		gotoxy(x,y+1);
		colorBackground("azul");
		printf("▀");
		gotoxy(x,y+2);
		printf(" ");
		colorForeground("verde claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x+1,y+4);
		printf("▀▀▀");

		colorDefault();
		break;

	case 'O':
		colorForeground("magenta claro");
		printf("▄▀▀▀▀▄");
		gotoxy(x,y+1);
		colorBackground("azul");
		printf("▀");
		gotoxy(x+5,y+1);
		printf("▀");
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+5,y+2);
		printf(" ");
		colorForeground("verde claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x+5,y+3);
		printf("█");
		gotoxy(x+1,y+4);
		printf("▀▀▀▀");

		colorDefault();
		break;

	case 'M':
		colorForeground("magenta claro");
		printf("█▄   ▄█");
		gotoxy(x+2,y+1);
		printf("▀ ▀");
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+6,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x+3,y+1);
		printf("▄");
		gotoxy(x,y+2);
		printf("█     █");
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("█     █");
		gotoxy(x,y+4);
		printf("▀     ▀");

		colorDefault();
		break;

	case 'P':
		colorForeground("magenta claro");
		printf("█▀▀▀▄");
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x,y+2);
		printf("█▀▀▀");
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x,y+4);
		printf("▀");

		colorDefault();
		break;

	case 'R':
		colorForeground("magenta claro");
		printf("█▀▀▀▄");
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x,y+2);
		printf("█▀▀▀▄");
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("█   █");
		gotoxy(x,y+4);
		printf("▀   ▀");

		colorDefault();
		break;

	case 'I':
		colorForeground("magenta claro");
		printf("▀█▀");
		colorBackground("azul");
		gotoxy(x+1,y+1);
		printf("▀");
		gotoxy(x+1,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("verde claro");
		gotoxy(x+1,y+3);
		printf("█");
		gotoxy(x,y+4);
		printf("▀▀▀");

		colorDefault();
		break;

	case 'A':
		colorForeground("magenta claro");
		printf("▄▀▀▀▄");
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x,y+2);
		printf("█▀▀▀█");
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("█   █");
		gotoxy(x,y+4);
		printf("▀   ▀");

		colorDefault();
		break;

	case 'H':
		colorForeground("magenta claro");
		printf("█   █");
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x+1,y+2);
		printf("▀▀▀");
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("█   █");
		gotoxy(x,y+4);
		printf("▀   ▀");

		colorDefault();
		break;

	case 'V':
		colorForeground("magenta claro");
		printf("█   █");
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("▀▄ ▄▀");
		gotoxy(x+2,y+4);
		printf("▀");

		colorDefault();
		break;

	case 'D':
		colorForeground("magenta claro");
		printf("█▀▀▀▄");
		gotoxy(x,y+1);
		colorBackground("azul");
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorForeground("verde claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x+4,y+3);
		printf("█");
		gotoxy(x,y+4);
		printf("▀▀▀▀");

		colorDefault();
		break;

	case 'E':
		colorForeground("magenta claro");
		printf("█▀▀▀");
		colorBackground("azul");
		gotoxy(x,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x,y+2);
		printf("█▀▀");
		colorForeground("verde claro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x,y+4);
		printf("▀▀▀▀");

		colorDefault();
		break;

	case 'S':
		colorForeground("magenta claro");
		printf("▄▀▀▀");
		gotoxy(x,y+1);
		colorBackground("azul");
		printf("▀");
		colorBackground("negro");
		colorForeground("azul");
		gotoxy(x+1,y+2);
		printf("▀▀▄");
		colorForeground("verde claro");
		gotoxy(x+3,y+3);
		printf("█");
		gotoxy(x,y+4);
		printf("▀▀▀");

		colorDefault();
		break;
	}
}

void menu(short x, short y, char l){
	gotoxy(x,y);
	switch(l){
	case 'C':
		colorForeground("blanco");
		printf("▄▀▀▀");
		gotoxy(x,y+1);
		colorBackground("cian claro");
		printf("▀");
		gotoxy(x,y+2);
		printf(" ");
		colorForeground("magenta claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x+1,y+4);
		printf("▀▀▀");

		colorDefault();
		break;

	case 'O':
		colorForeground("blanco");
		printf("▄▀▀▀▀▄");
		gotoxy(x,y+1);
		colorBackground("cian claro");
		printf("▀");
		gotoxy(x+5,y+1);
		printf("▀");
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+5,y+2);
		printf(" ");
		colorForeground("magenta claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x+5,y+3);
		printf("█");
		gotoxy(x+1,y+4);
		printf("▀▀▀▀");

		colorDefault();
		break;

	case 'M':
		colorForeground("blanco");
		printf("█▄   ▄█");
		gotoxy(x+2,y+1);
		printf("▀ ▀");
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+6,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x+3,y+1);
		printf("▄");
		gotoxy(x,y+2);
		printf("█     █");
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("█     █");
		gotoxy(x,y+4);
		printf("▀     ▀");

		colorDefault();
		break;

	case 'P':
		colorForeground("blanco");
		printf("█▀▀▀▄");
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x,y+2);
		printf("█▀▀▀");
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x,y+4);
		printf("▀");

		colorDefault();
		break;

	case 'R':
		colorForeground("blanco");
		printf("█▀▀▀▄");
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x,y+2);
		printf("█▀▀▀▄");
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("█   █");
		gotoxy(x,y+4);
		printf("▀   ▀");

		colorDefault();
		break;

	case 'I':
		colorForeground("blanco");
		printf("▀█▀");
		colorBackground("cian claro");
		gotoxy(x+1,y+1);
		printf("▀");
		gotoxy(x+1,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("magenta claro");
		gotoxy(x+1,y+3);
		printf("█");
		gotoxy(x,y+4);
		printf("▀▀▀");

		colorDefault();
		break;

	case 'A':
		colorForeground("blanco");
		printf("▄▀▀▀▄");
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x,y+2);
		printf("█▀▀▀█");
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("█   █");
		gotoxy(x,y+4);
		printf("▀   ▀");

		colorDefault();
		break;

	case 'H':
		colorForeground("blanco");
		printf("█   █");
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x+1,y+2);
		printf("▀▀▀");
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("█   █");
		gotoxy(x,y+4);
		printf("▀   ▀");

		colorDefault();
		break;

	case 'V':
		colorForeground("blanco");
		printf("█   █");
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorBackground("negro");
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("▀▄ ▄▀");
		gotoxy(x+2,y+4);
		printf("▀");

		colorDefault();
		break;

	case 'D':
		colorForeground("blanco");
		printf("█▀▀▀▄");
		gotoxy(x,y+1);
		colorBackground("cian claro");
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorForeground("magenta claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x+4,y+3);
		printf("█");
		gotoxy(x,y+4);
		printf("▀▀▀▀");

		colorDefault();
		break;

	case 'E':
		colorForeground("blanco");
		printf("█▀▀▀");
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x,y+2);
		printf("█▀▀");
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x,y+4);
		printf("▀▀▀▀");

		colorDefault();
		break;

	case 'S':
		colorForeground("blanco");
		printf("▄▀▀▀");
		gotoxy(x,y+1);
		colorBackground("cian claro");
		printf("▀");
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x+1,y+2);
		printf("▀▀▄");
		colorForeground("magenta claro");
		gotoxy(x+3,y+3);
		printf("█");
		gotoxy(x,y+4);
		printf("▀▀▀");

		colorDefault();
		break;

	case 'F':
		colorForeground("blanco");
		printf("█▀▀▀");
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x,y+2);
		printf("█▀▀");
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x,y+4);
		printf("▀");

		colorDefault();
		break;

	case 'N':
		colorForeground("blanco");
		printf("█▄   █");
		gotoxy(x+2,y+1);
		printf("▀");
		colorBackground("cian claro");
		gotoxy(x,y+1);
		printf("▀");
		gotoxy(x+5,y+1);
		printf("▀");
		colorBackground("negro");
		colorForeground("cian claro");
		gotoxy(x+3,y+1);
		printf("▄");
		gotoxy(x,y+2);
		printf("█   ▀█");
		colorForeground("magenta claro");
		gotoxy(x,y+3);
		printf("█    █");
		gotoxy(x,y+4);
		printf("▀    ▀");

		colorDefault();
		break;

	case 'U':
		colorForeground("blanco");
		printf("█   █");
		gotoxy(x,y+1);
		colorBackground("cian claro");
		printf("▀");
		gotoxy(x+4,y+1);
		printf("▀");
		gotoxy(x,y+2);
		printf(" ");
		gotoxy(x+4,y+2);
		printf(" ");
		colorForeground("magenta claro");
		colorBackground("negro");
		gotoxy(x,y+3);
		printf("█");
		gotoxy(x+4,y+3);
		printf("█");
		gotoxy(x+1,y+4);
		printf("▀▀▀");

		colorDefault();
		break;
	}
}

void pochita(short x, short y){
	//Texto gris claro, fondo negro
	colorForeground("gris claro");
	gotoxy(x+2,y);
	printf("▄");
	gotoxy(x+8,y);
	printf("▄▄▄");
	gotoxy(x,y+1);
	printf("▄");
	gotoxy(x,y+2);
	printf("█");
	gotoxy(x+1,y+3);
	printf("▀");
	gotoxy(x+3,y+4);
	printf("▀");

	//Texto gris claro, fondo blanco
	colorBackground("blanco");
	gotoxy(x+3,y);
	printf("▀▀▀▀▀");
	gotoxy(x+1,y+1);
	printf("▀         ▀");

	gotoxy(x+2,y+3);
	printf("▄     ");
	gotoxy(x+4,y+4);
	printf("▄▄▄");
	gotoxy(x+17,y+3);
	printf("▀");
	gotoxy(x+17,y+4);
	printf(" ");
	gotoxy(x+12,y+5);
	printf("▄");
	gotoxy(x+16,y+5);
	printf("▄");

	//Texto gris oscuro, fondo blanco
	colorForeground("gris oscuro");
	gotoxy(x+1,y+2);
	printf("        ▄");
	gotoxy(x+8,y+3);
	printf("▄");
	gotoxy(x+7,y+4);
	printf("▄");
	
	//Texto gris oscuro, fondo magenta
	colorBackground("magenta claro");
	gotoxy(x+7,y+6);
	printf("▀▀");
	gotoxy(x+7,y+7);
	printf("  ");
	
	//Texto gris oscuro, fondo gris claro
	colorBackground("gris claro");
	gotoxy(x+12,y+1);
	printf("▄");
	gotoxy(x+8,y+4);
	printf("▀   ");
	gotoxy(x+9,y+3);
	printf("▀  ");
	gotoxy(x+10,y+2);
	printf("▀▀    ▀▀");
	gotoxy(x+6,y+5);
	printf("█   ▄ ");
	gotoxy(x+18,y+3);
	printf("  ▀▀");
	gotoxy(x+18,y+4);
	printf("     ▀");
	gotoxy(x+17,y+5);
	printf("        ▀");
	gotoxy(x+9,y+6);
	printf("█                 █");
	gotoxy(x+10,y+7);
	printf("▄                 █");
	gotoxy(x+11,y+8);
	printf("█                █");
	gotoxy(x+12,y+9);
	printf("▀▀              █");
	gotoxy(x+10,y+10);
	printf("█      ▄▄ ▄   ▄▄");
	gotoxy(x+19,y+11);
	printf("█▄▄▄");

	//Texto gris oscuro, fondo negro
	colorBackground("negro");
	gotoxy(x+13,y+1);
	printf("▄▄▄");
	gotoxy(x+18,y+2);
	printf("▄▄");
	gotoxy(x+24,y+4);
	printf("▄");
	gotoxy(x+26,y+5);
	printf("▄");
	gotoxy(x+9,y+7);
	printf("▀");
	gotoxy(x+11,y+9);
	printf("▄");
	gotoxy(x+26,y+10);
	printf("▀▀");
	gotoxy(x+11,y+11);
	printf("▀▀▀▀▀▀");
	gotoxy(x+23,y+11);
	printf("▀");

	//Texto rojo, fondo negro
	colorForeground("rojo");
	gotoxy(x+16,y+1);
	printf("▄██████████");
	gotoxy(x+23,y+2);
	printf("▄▄█▀");
	gotoxy(x+23,y+3);
	printf("▀▀");

	gotoxy(x+32,y+4);
	printf("▄▄▄");
	gotoxy(x+31,y+5);
	printf("▀▄ ▄▀");
	gotoxy(x+28,y+6);
	printf("█▀█  █");
	gotoxy(x+30,y+7);
	printf("█ ▄▀");
	gotoxy(x+29,y+8);
	printf("█▄▄▀");

	colorBackground("rojo");
	gotoxy(x+13,y+3);
	printf("███");
	gotoxy(x+12,y+4);
	printf("█████");

	colorBackground("blanco");
	gotoxy(x+16,y+3);
	printf("▄");
	gotoxy(x+13,y+5);
	printf("▀▀▀");
	colorBackground("gris claro");
	gotoxy(x+12,y+3);
	printf("▄");
	colorBackground("gris oscuro");
	gotoxy(x+22,y+3);
	printf("▀");

	colorDefault();
}