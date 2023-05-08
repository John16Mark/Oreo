#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include "disenio.h"

void gotoxy(int x, int y){
	printf("%c[%d;%df",0x1B,y+1,x+1);
}

void clrscr(){
	colorDefault();
	system("clear");
	printf("\033[2J");
}

void esperar(int t){
	usleep(t*1000);
}

void colorForeground(char *color){
	if(strcmp(color,"negro") == 0){
		printf("\033[30m");
	}
	else if(strcmp(color,"rojo") == 0){
		printf("\033[31m");
	}
	else if(strcmp(color,"azul") == 0){
		printf("\033[34m");
	}
	else if(strcmp(color,"magenta") == 0){
		printf("\033[35m");
	}
	else if(strcmp(color,"gris claro") == 0){
		printf("\033[37m");
	}
	else if(strcmp(color,"gris oscuro") == 0){
		printf("\033[90m");
	}
	else if(strcmp(color,"rojo claro") == 0){
		printf("\033[91m");
	}
	else if(strcmp(color,"magenta claro") == 0){
		printf("\033[95m");
	}
	else if(strcmp(color,"verde claro") == 0){
		printf("\033[92m");
	}
	else if(strcmp(color,"cian claro") == 0){
		printf("\033[96m");
	}
	else if(strcmp(color, "blanco") == 0){
		printf("\033[97m");
	}
}

void colorBackground(char *color){
	if(strcmp(color,"negro") == 0){
		printf("\033[40m");
	}
	else if(strcmp(color,"rojo") == 0){
		printf("\033[41m");
	}
	else if(strcmp(color,"azul") == 0){
		printf("\033[44m");
	}
	else if(strcmp(color,"magenta") == 0){
		printf("\033[45m");
	}
	else if(strcmp(color,"gris claro") == 0){
		printf("\033[47m");
	}
	else if(strcmp(color,"gris oscuro") == 0){
		printf("\033[100m");
	}
	else if(strcmp(color,"verde claro") == 0){
		printf("\033[102m");
	}
	else if(strcmp(color,"magenta claro") == 0){
		printf("\033[105m");
	}
	else if(strcmp(color,"cian claro") == 0){
		printf("\033[106m");
	}
	else if(strcmp(color,"blanco") == 0){
		printf("\033[107m");
	}
}

void colorDefault(){
	printf("\033[0m\033[40m");
}