#include "stdafx.h"
#include "string.h"
char mass_bis_s[1000][10];
int bis_max = 0;

//�������� ����� ���������
int get_bis_type(char *s){
	for (int i = 0; i < bis_max;i++)
	if (!strcmp(s, mass_bis_s[i]))
		return i;
	strcpy(mass_bis_s[bis_max], s);
	return bis_max++;
}