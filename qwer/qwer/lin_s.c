#include "stdafx.h"
#include "string.h"
char mass_bis_s[1000][10];
int bis_max = 0;

//Получаем номер протокола
/*int get_bis_type(char *s){
	for (int i = 0; i < bis_max;i++)
	if (!strcmp(s, mass_bis_s[i]))
		return i;
	strcpy(mass_bis_s[bis_max], s);
	return bis_max++;
}*/

int get_bis_type(char *s){
	int r = 0;
	for (int i = 0; i < strlen(s); i++)
		r = (r << 1) ^ s[i] + i;
	//printf("@ %d\n", r);
	return r;
}