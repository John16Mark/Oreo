#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
gcc e.c -o e.exe
*/

#define PESOBIT(bpos) 1<<bpos
#define CONSULTARBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)

int main(){
	unsigned char a[2];
	a[0] = 65;
	a[1] = 137;
	int i;
	for(i = 0; i < 16; i++){
		printf("%d",CONSULTARBIT(*(a+(i/8)),7-(i%8)));
	}
	
	printf("\n%c %c", *a, *(a+1));
	/*for(i = 0; i < 8; i++){
		printf("%d",CONSULTARBIT(a[1],7-i%8));
	}*/

}