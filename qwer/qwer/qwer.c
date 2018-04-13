// qwer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

FILE *zlo;

char s[1000];

//Структура одного пакета
struct packet{
	long time;
	int ip;
	int rr;
	int section;
	char protocol;
};

//Ищем клбчевое слово <packet>
void start_search(){
	char scmp[] = "<packet>00";
	scmp[8] = 13;
	scmp[9] = 10;
	//printf("%c", 10);
	do{
		//system("pause");
		fgets(s, sizeof(s), zlo);
		//printf("%s", s);
		/*for (int i = 0; i < strlen(s); i++)
			printf("%d)%d %d\n", i, s[i], scmp[i]);*/
	} while (strcmp(s, scmp));
}

//Извлекаем время
void parse_time(){
	char* str = s + 10;
	str[strlen(str) - 12] = '\0';
	printf("%s", str);
}

//Парсим один пакет
void parse(){
	fgets(s, sizeof(s), zlo);
	fgets(s, sizeof(s), zlo);
	printf("%s", s);
	parse_time();
	fgets(s, sizeof(s), zlo);
	fgets(s, sizeof(s), zlo);
	fgets(s, sizeof(s), zlo);
	fgets(s, sizeof(s), zlo);
	fgets(s, sizeof(s), zlo);
}

int main(){
	zlo = fopen("test", "rb");
	start_search();
	parse();
	fclose(zlo);
}

