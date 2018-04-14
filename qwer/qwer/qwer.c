// qwer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

FILE *zlo;

char s[1000];

//Структура одного пакета
struct packet{
	long long int time;
	int ip;
	int my_ip;
	int rr;
	//int section;
	int protocol;
};


struct packet *global;

struct db{
	struct db*l;
	struct db*r;
	struct db*papa;
	int mass;
	int ssam;
};

struct db*start_ip;

struct db* new_db_ip(){
	return (struct db*)malloc(sizeof(struct db));
}

void push_ip2(int a){
	struct db*now = start_ip;
	if (!now){
		now = new_db_ip();
		now->l = now->r = now->papa = 0;
		now->ssam = 1;
		now->mass = a;
		start_ip = now;
		return;
	}
	while (now->mass != a){
		if ((now->mass > a && !now->r) || (now->mass < a && !now->l)){
			struct db*help = now;
			if (help->mass>a)
				help->r = now;
			else help->l = now;
			now = new_db_ip;
			now->mass = a;
			now->ssam = 1;
			now->papa = help;
			now->l = now->r = 0;
			return now;
		}
		if (now->mass > a)
			now = now->r;
		else now = now->l;
	}
	now->ssam++;
	return now;
}



int mass_ip[1000];
int ssam_ip[1000];
int old_mass_ip[1000];
int old_ssam_ip[1000];
int max_mass_ip;
int old_max_mass_ip;


#define z 3
int max_const = 1000;

int binarysearch(int a)
{
	int low, high, middle;
	low = 0;
	high = old_max_mass_ip - 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (a < old_mass_ip[middle])
			high = middle - 1;
		else if (a > old_mass_ip[middle])
			low = middle + 1;
		else
			return middle;
	}
	return -1;
}

//По массиву!!! и тоько
int pos_ip(int a){
	for (int i = 0; i < old_max_mass_ip; i++){
		if (old_mass_ip[i] == a)
			return old_ssam_ip[i];
	}
	return 0;
}


int keeek = 0;

void load_ip(){
	int mmmax = 0;
	old_max_mass_ip = 0;
	char sp[100];
	sprintf(sp, "%d.txt", ++keeek);
	FILE *fi = fopen(sp, "r");
	fscanf(fi, "%d", &old_max_mass_ip);
	for (int i = 0; i < old_max_mass_ip; i++){
		fscanf(fi, "%d %d", &old_mass_ip[i], &old_ssam_ip[i]);
		mmmax += old_ssam_ip[i];
	}
	printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n%d\n\n", mmmax);
	fclose(fi);
}

double baes_ip(){
	double result = 0.0;
	for (int i = 0; i < max_mass_ip; i++){
		int a = pos_ip(mass_ip[i]);
		result += a*log(((double)(ssam_ip[i] + z)) / ((105) + z*max_const));
		printf("! = %lf\n", result);
	}
	printf("! = %lf\n", result);
}

/*double baes_ip2(){
	double result = 0.0;
	struct db*now = start_ip;
	while (1){
		if (now->l){
			now
		}
	}
	for (int i = 0; i < max_mass_ip; i++){
		int a = pos_ip(mass_ip[i]);
		result += a*log(((double)(ssam_ip[i] + z)) / ((105) + z*max_const));
		printf("! = %lf\n", result);
	}
	printf("! = %lf\n", result);
}*/

int correct_ip(struct packet * mu){
	if (mu->ip == global->ip)
		return 1;
	else return 0;
}

void quickSort_ip(int left, int right)
{
	int pivot; // разрешающий элемент
	int l_hold = left; //левая граница
	int r_hold = right; // правая граница
	pivot = mass_ip[left];
	int pivot_help = ssam_ip[left];
	while (left < right) // пока границы не сомкнутся
	{
		while ((mass_ip[right] >= pivot) && (left < right))
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			mass_ip[left] = mass_ip[right]; // перемещаем элемент [right] на место разрешающего
			ssam_ip[left] = ssam_ip[right];
			left++; // сдвигаем левую границу вправо 
		}
		while ((mass_ip[left] <= pivot) && (left < right))
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			mass_ip[right] = mass_ip[left]; // перемещаем элемент [left] на место [right]
			ssam_ip[right] = ssam_ip[left];
			right--; // сдвигаем правую границу вправо 
		}
	}
	mass_ip[left] = pivot; // ставим разрешающий элемент на место
	ssam_ip[left] = pivot_help;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
		quickSort_ip(left, pivot - 1);
	if (right > pivot)
		quickSort_ip(pivot + 1, right);
}

void print_to_file(){
	FILE *fi = fopen("1.txt", "w");
	fprintf(fi, "%d\n", max_mass_ip);
	for (int i = 0; i < max_mass_ip; i++){
		fprintf(fi, "%d %d\n", mass_ip[i], ssam_ip[i]);
	}
	fclose(fi);
}

void push_ip(){
	for (int i = 0; i < max_mass_ip;i++)
	if (correct_ip(&mass_ip[i])){
		ssam_ip[i]++;
		return;
	}
	mass_ip[max_mass_ip] = global->ip;
	ssam_ip[max_mass_ip] = 1;
	max_mass_ip++;
}



void read_max_count(){
	FILE *fi = fopen("all.txt", "r");
	fscanf(fi, "%d", &max_const);
	fclose(fi);
}

//Начальные символы
void start_search(){
	fgets(s, sizeof(s), zlo);
	//fgets(s, sizeof(s), zlo);
	//fgets(s, sizeof(s), zlo);
	//fgets(s, sizeof(s), zlo);
	//fgets(s, sizeof(s), zlo);
}

//Переводим ip в число
int ip_to_int(char*s){
	//printf("\n^^ %s\n", s);
	int r = 0;
	int now = 0;
	int i = 0;
	do{
		if (s[i] == '.'){
			r = r * 256 + now;
			now = 0;
		}
		else
			now = now * 10 + s[i];
	} while (s[++i] != '\0');
	r += now;
	//printf("%u\n", r);
	return r;
}

//Извлекаем время
void parse_time(char *s){
	//printf("\t%s", s);
	int i = 0;
	int se = 0;
	int ms = 0;
	global->time = 0;
	for (i = 0; i < strlen(s); i++){
		switch (s[i])
		{
		case ':':
			global->time = global->time *60 + se;
			se = 0;
			break;
		case ',':
		{
					global->time = (global->time * 60 + se)*1000000;
			break;
		}
		default:
			if (i>8)
				ms = ms * 10 + s[i] - '0';
			else se = se * 10 + s[i] - '0';
			break;
		}
	}
	global->time += ms;
}

//Следующий параметр
void next_s(int*i, int*i_start){
	*i += 3;
	*i_start = *i;
	while (s[++(*i)] != '"');
	s[*i] = '\0';
}

//Вывод пакета
void print_packet(struct packet* p){
	printf("\ntime:%lld\nip1:%d\nip2:%d\nprotocol:%d\nlength:%d\n", p->time, p->ip, p->my_ip, p->protocol, p->rr);
}

//Парсим один пакет
int parse(){
	s[0] = '\0';
	fgets(s, sizeof(s), zlo);
	//printf("%s", s);
	if (s[0]=='\0') return 0;
	//printf("%s\n", s);
	/*Извлечь время*/
	int i = 0;
	int u = 3;
	int i_start;
	while (u){
		if (s[i++] == '"')
			--u;
	}
	i_start = i;
	while (s[++i] != '"');
	s[i] = '\0';
	parse_time(s+i_start);
	next_s(&i, &i_start);
	//printf("!%s\n", s + i_start);
	global->ip = ip_to_int(s + i_start);
	next_s(&i, &i_start);
	global->my_ip = ip_to_int(s + i_start);
	next_s(&i, &i_start);
	global->protocol = get_bis_type(s + i_start);
	next_s(&i, &i_start);
	global->rr = atoi(s + i_start);
//	print_packet(global);
	push_ip();
	return 1;
}

int main(){
	read_max_count();
	global = (struct packet*)malloc(sizeof(struct packet));
	zlo = fopen("test", "rb");
	start_search();
	while (parse()){
		
	}
	for (int i = 0; i < max_mass_ip; i++)
		printf("%d) %d\n", mass_ip[i], ssam_ip[i]);
	quickSort_ip(0, max_mass_ip-1);
	for (int i = 0; i < max_mass_ip; i++)
		printf("%d) %d\n", mass_ip[i], ssam_ip[i]);
	int super_max = 0;
	for (int i = 0; i < max_mass_ip; i++)
		super_max += ssam_ip[i];
	printf("\n\n#############################\n%d\n\n", super_max);
	for (int i = 0; i < 3; i++){
		load_ip();
		printf("%ld\n", baes_ip());
	}
	//printf("\n%lld\n", global->time);
	//print_to_file_ip();
	//printf("%ld\n", baes());
	//load();
	//printf("%ld\n", baes());
	fclose(zlo);
}

