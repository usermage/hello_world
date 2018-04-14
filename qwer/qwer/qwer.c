// qwer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

FILE *zlo;

int to_ip = 143;
int to_my_ip = 167;
int to_rr = 787;
int to_protocol = 80;
int to_time=2083;

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

//Отвечает за указатель на текущюю структуру
struct packet *global;

//Попытка создать db дерево
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

//
#define z 4
int max_const = 1000;
int keeek = 0;








///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////ip/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////




/*ip, my_time, rr, protocol, time 
	имеют схожий синтаксис и по сути копируют себя*/






int mass_ip[1000]; //Массив хранит текущие значения вариантов ip
int ssam_ip[1000]; //Хранит количество вариантов массива выше
int old_mass_ip[1000]; //Тоже самое, хранит загружаемую версию
int old_ssam_ip[1000]; //Тоже самое
int max_mass_ip; //Размер массива для ip адресов
int old_max_mass_ip; //Размер массива для подгружаемых данных

//Поиск значения ip в подгруженном массиве
//Бинарный поиск
int pos_ip(int a)
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
			return old_ssam_ip[middle];
	}
	return 0;
}

//Загружает указанный файл и смотрит от туда ip и их количество
// (зранее обработанный пользователь)
void load_ip(){
	int mmmax = 0;
	old_max_mass_ip = 0;
	char sp[100];
	sprintf(sp, "%d_ip.txt", ++keeek);
	FILE *fi = fopen(sp, "r");
	fscanf(fi, "%d", &old_max_mass_ip);
	for (int i = 0; i < old_max_mass_ip; i++){
		fscanf(fi, "%d %d", &old_mass_ip[i], &old_ssam_ip[i]);
		mmmax += old_ssam_ip[i];
	}
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\t%d\n", mmmax);
	fclose(fi);
}

//Возвращает коэфициент баеса
double baes_ip(){
	double result = 0.0;
	for (int i = 0; i < max_mass_ip; i++){
		int a = pos_ip(mass_ip[i]);
		result += a*log(((double)(ssam_ip[i] + z)) / ((to_ip)+z*max_const));
		//printf("! = %lf\n", result);
	}
	printf("! = %lf\n", result);
	return result;
}

//Определяет подходящий ли ip аддресс
int correct_ip(struct packet * mu){
	if (mu->ip == global->ip)
		return 1;
	else return 0;
}

//Сортировка массива после обработки
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

//Выводит в файл текущюю конфигурацию
void print_to_file_ip(){
	FILE *fi = fopen("1_ip.txt", "w");
	fprintf(fi, "%d\n", max_mass_ip);
	for (int i = 0; i < max_mass_ip; i++){
		fprintf(fi, "%d %d\n", mass_ip[i], ssam_ip[i]);
	}
	fclose(fi);
}

//Поместить ip-адресс в нашу базу
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


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////my_ip/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////




int mass_my_ip[1000];
int ssam_my_ip[1000];
int old_mass_my_ip[1000];
int old_ssam_my_ip[1000];
int max_mass_my_ip;
int old_max_mass_my_ip;

int pos_my_ip(int a)
{
	int low, high, middle;
	low = 0;
	high = old_max_mass_my_ip - 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (a < old_mass_my_ip[middle])
			high = middle - 1;
		else if (a > old_mass_my_ip[middle])
			low = middle + 1;
		else
			return old_ssam_my_ip[middle];
	}
	return 0;
}


void load_my_ip(){
	int mmmax = 0;
	old_max_mass_my_ip = 0;
	char sp[100];
	sprintf(sp, "%d_my_ip.txt", keeek);
	FILE *fi = fopen(sp, "r");
	fscanf(fi, "%d", &old_max_mass_my_ip);
	for (int i = 0; i < old_max_mass_my_ip; i++){
		fscanf(fi, "%d %d", &old_mass_my_ip[i], &old_ssam_my_ip[i]);
		mmmax += old_ssam_my_ip[i];
	}
	printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n%d\n\n", mmmax);
	fclose(fi);
}

double baes_my_ip(){
	double result = 0.0;
	for (int i = 0; i < max_mass_my_ip; i++){
		int a = pos_my_ip(mass_my_ip[i]);
		result += a*log(((double)(ssam_my_ip[i] + z)) / ((to_my_ip)+z*max_const));
		//printf("! = %lf\n", result);
	}
	printf("! = %lf\n", result);
	return result;
}

int correct_my_ip(struct packet * mu){
	if (mu->my_ip == global->my_ip)
		return 1;
	else return 0;
}

void quickSort_my_ip(int left, int right)
{
	int pivot; // разрешающий элемент
	int l_hold = left; //левая граница
	int r_hold = right; // правая граница
	pivot = mass_my_ip[left];
	int pivot_help = ssam_my_ip[left];
	while (left < right) // пока границы не сомкнутся
	{
		while ((mass_my_ip[right] >= pivot) && (left < right))
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			mass_my_ip[left] = mass_my_ip[right]; // перемещаем элемент [right] на место разрешающего
			ssam_my_ip[left] = ssam_my_ip[right];
			left++; // сдвигаем левую границу вправо 
		}
		while ((mass_my_ip[left] <= pivot) && (left < right))
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			mass_my_ip[right] = mass_my_ip[left]; // перемещаем элемент [left] на место [right]
			ssam_my_ip[right] = ssam_my_ip[left];
			right--; // сдвигаем правую границу вправо 
		}
	}
	mass_my_ip[left] = pivot; // ставим разрешающий элемент на место
	ssam_my_ip[left] = pivot_help;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
		quickSort_my_ip(left, pivot - 1);
	if (right > pivot)
		quickSort_my_ip(pivot + 1, right);
}

void print_to_file_my_ip(){
	FILE *fi = fopen("1_my_ip.txt", "w");
	fprintf(fi, "%d\n", max_mass_my_ip);
	for (int i = 0; i < max_mass_my_ip; i++){
		fprintf(fi, "%d %d\n", mass_my_ip[i], ssam_my_ip[i]);
	}
	fclose(fi);
}

void push_my_ip(){
	for (int i = 0; i < max_mass_my_ip; i++)
	if (correct_my_ip(&mass_my_ip[i])){
		ssam_my_ip[i]++;
		return;
	}
	mass_my_ip[max_mass_my_ip] = global->my_ip;
	ssam_my_ip[max_mass_my_ip] = 1;
	max_mass_my_ip++;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////rr/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////











int mass_rr[1000];
int ssam_rr[1000];
int old_mass_rr[1000];
int old_ssam_rr[1000];
int max_mass_rr;
int old_max_mass_rr;

int pos_rr(int a)
{
	int low, high, middle;
	low = 0;
	high = old_max_mass_rr - 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (a < old_mass_rr[middle])
			high = middle - 1;
		else if (a > old_mass_rr[middle])
			low = middle + 1;
		else
			return old_ssam_rr[middle];
	}
	return 0;
}

//По массиву!!! и тоько (cv dsit)
/*int pos_rr(int a){
for (int i = 0; i < old_max_mass_rr; i++){
if (old_mass_rr[i] == a)
return old_ssam_rr[i];
}
return 0;
}*/


void load_rr(){
	int mmmax = 0;
	old_max_mass_rr = 0;
	char sp[100];
	sprintf(sp, "%d_rr.txt", keeek);
	FILE *fi = fopen(sp, "r");
	fscanf(fi, "%d", &old_max_mass_rr);
	for (int i = 0; i < old_max_mass_rr; i++){
		fscanf(fi, "%d %d", &old_mass_rr[i], &old_ssam_rr[i]);
		mmmax += old_ssam_rr[i];
	}
	printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n%d\n\n", mmmax);
	fclose(fi);
}

double baes_rr(){
	double result = 0.0;
	for (int i = 0; i < max_mass_rr; i++){
		int a = pos_rr(mass_rr[i]);
		result += a*log(((double)(ssam_rr[i] + z)) / ((to_rr)+z*max_const));
		//printf("! = %lf\n", result);
	}
	printf("! = %lf\n", result);
	return result;
}


int correct_rr(struct packet * mu){
	if (mu->rr == global->rr)
		return 1;
	else return 0;
}

void quickSort_rr(int left, int right)
{
	int pivot; // разрешающий элемент
	int l_hold = left; //левая граница
	int r_hold = right; // правая граница
	pivot = mass_rr[left];
	int pivot_help = ssam_rr[left];
	while (left < right) // пока границы не сомкнутся
	{
		while ((mass_rr[right] >= pivot) && (left < right))
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			mass_rr[left] = mass_rr[right]; // перемещаем элемент [right] на место разрешающего
			ssam_rr[left] = ssam_rr[right];
			left++; // сдвигаем левую границу вправо 
		}
		while ((mass_rr[left] <= pivot) && (left < right))
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			mass_rr[right] = mass_rr[left]; // перемещаем элемент [left] на место [right]
			ssam_rr[right] = ssam_rr[left];
			right--; // сдвигаем правую границу вправо 
		}
	}
	mass_rr[left] = pivot; // ставим разрешающий элемент на место
	ssam_rr[left] = pivot_help;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
		quickSort_rr(left, pivot - 1);
	if (right > pivot)
		quickSort_rr(pivot + 1, right);
}

void print_to_file_rr(){
	FILE *fi = fopen("1_rr.txt", "w");
	fprintf(fi, "%d\n", max_mass_rr);
	for (int i = 0; i < max_mass_rr; i++){
		fprintf(fi, "%d %d\n", mass_rr[i], ssam_rr[i]);
	}
	fclose(fi);
}

void push_rr(){
	for (int i = 0; i < max_mass_rr; i++)
	if (correct_rr(&mass_rr[i])){
		ssam_rr[i]++;
		return;
	}
	mass_rr[max_mass_rr] = global->rr;
	ssam_rr[max_mass_rr] = 1;
	max_mass_rr++;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////protocol//////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////











int mass_protocol[1000];
int ssam_protocol[1000];
int old_mass_protocol[1000];
int old_ssam_protocol[1000];
int max_mass_protocol;
int old_max_mass_protocol;

int pos_protocol(int a)
{
	int low, high, middle;
	low = 0;
	high = old_max_mass_protocol - 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (a < old_mass_protocol[middle])
			high = middle - 1;
		else if (a > old_mass_protocol[middle])
			low = middle + 1;
		else
			return old_ssam_protocol[middle];
	}
	return 0;
}

//По массиву!!! и тоько (cv dsit)
/*int pos_protocol(int a){
for (int i = 0; i < old_max_mass_protocol; i++){
if (old_mass_protocol[i] == a)
return old_ssam_protocol[i];
}
return 0;
}*/


void load_protocol(){
	int mmmax = 0;
	old_max_mass_protocol = 0;
	char sp[100];
	sprintf(sp, "%d_protocol.txt", keeek);
	FILE *fi = fopen(sp, "r");
	fscanf(fi, "%d", &old_max_mass_protocol);
	for (int i = 0; i < old_max_mass_protocol; i++){
		fscanf(fi, "%d %d", &old_mass_protocol[i], &old_ssam_protocol[i]);
		mmmax += old_ssam_protocol[i];
	}
	printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n%d\n\n", mmmax);
	fclose(fi);
}

double baes_protocol(){
	double result = 0.0;
	for (int i = 0; i < max_mass_protocol; i++){
		int a = pos_protocol(mass_protocol[i]);
		result += a*log(((double)(ssam_protocol[i] + z)) / ((to_protocol)+z*max_const));
		//printf("! = %lf\n", result);
	}
	printf("! = %lf\n", result);
	return result;
}


int coprotocolect_protocol(struct packet * mu){
	if (mu->protocol == global->protocol)
		return 1;
	else return 0;
}

void quickSort_protocol(int left, int right)
{
	int pivot; // разрешающий элемент
	int l_hold = left; //левая граница
	int r_hold = right; // правая граница
	pivot = mass_protocol[left];
	int pivot_help = ssam_protocol[left];
	while (left < right) // пока границы не сомкнутся
	{
		while ((mass_protocol[right] >= pivot) && (left < right))
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			mass_protocol[left] = mass_protocol[right]; // перемещаем элемент [right] на место разрешающего
			ssam_protocol[left] = ssam_protocol[right];
			left++; // сдвигаем левую границу вправо 
		}
		while ((mass_protocol[left] <= pivot) && (left < right))
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			mass_protocol[right] = mass_protocol[left]; // перемещаем элемент [left] на место [right]
			ssam_protocol[right] = ssam_protocol[left];
			right--; // сдвигаем правую границу вправо 
		}
	}
	mass_protocol[left] = pivot; // ставим разрешающий элемент на место
	ssam_protocol[left] = pivot_help;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
		quickSort_protocol(left, pivot - 1);
	if (right > pivot)
		quickSort_protocol(pivot + 1, right);
}

void print_to_file_protocol(){
	FILE *fi = fopen("1_protocol.txt", "w");
	fprintf(fi, "%d\n", max_mass_protocol);
	for (int i = 0; i < max_mass_protocol; i++){
		fprintf(fi, "%d %d\n", mass_protocol[i], ssam_protocol[i]);
	}
	fclose(fi);
}

void push_protocol(){
	for (int i = 0; i < max_mass_protocol; i++)
	if (coprotocolect_protocol(&mass_protocol[i])){
		ssam_protocol[i]++;
		return;
	}
	mass_protocol[max_mass_protocol] = global->protocol;
	ssam_protocol[max_mass_protocol] = 1;
	max_mass_protocol++;
}




///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////time////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////











long long int mass_time[1000];
long long int ssam_time[1000];
long long int old_mass_time[1000];
long long int old_ssam_time[1000];
long long int max_mass_time;
long long int old_max_mass_time;

long long int pos_time(long long int a)
{
	long long int low, high, middle;
	low = 0;
	high = old_max_mass_time - 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (a < old_mass_time[middle])
			high = middle - 1;
		else if (a > old_mass_time[middle])
			low = middle + 1;
		else
			return old_ssam_time[middle];
	}
	return 0;
}

void load_time(){
	long long int mmmax = 0;
	old_max_mass_time = 0;
	char sp[100];
	sprintf(sp, "%d_time.txt", keeek);
	FILE *fi = fopen(sp, "r");
	fscanf(fi, "%d", &old_max_mass_time);
	for (int i = 0; i < old_max_mass_time; i++){
		fscanf(fi, "%d %d", &old_mass_time[i], &old_ssam_time[i]);
		mmmax += old_ssam_time[i];
	}
	printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n%d\n\n", mmmax);
	fclose(fi);
}

double baes_time(){
	double result = 0.0;
	for (int i = 0; i < max_mass_time; i++){
		if (i&&(mass_time[i] - mass_time[i - 1])<10)
			continue;
		long long int a = pos_time(mass_time[i]);
		result += a*log(((double)(ssam_time[i] + z)) / ((to_time)+z*max_const));
		//printf("! = %lf\n", result);
		/*if (i == 840)
		{
			printf("()\n");
		}*/
	}
	printf("! = %lf\n", result);
	return result;
}


long long int cotimeect_time(struct packet * mu){
	if (mu->time == global->time)
		return 1;
	else return 0;
}

void quickSort_time(int left, int right)
{
	long long int pivot; // разрешающий элемент
	int l_hold = left; //левая граница
	int r_hold = right; // правая граница
	pivot = mass_time[left];
	long long int pivot_help = ssam_time[left];
	while (left < right) // пока границы не сомкнутся
	{
		while ((mass_time[right] >= pivot) && (left < right))
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			mass_time[left] = mass_time[right]; // перемещаем элемент [right] на место разрешающего
			ssam_time[left] = ssam_time[right];
			left++; // сдвигаем левую границу вправо 
		}
		while ((mass_time[left] <= pivot) && (left < right))
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			mass_time[right] = mass_time[left]; // перемещаем элемент [left] на место [right]
			ssam_time[right] = ssam_time[left];
			right--; // сдвигаем правую границу вправо 
		}
	}
	mass_time[left] = pivot; // ставим разрешающий элемент на место
	ssam_time[left] = pivot_help;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
		quickSort_time(left, pivot - 1);
	if (right > pivot)
		quickSort_time(pivot + 1, right);
}

void print_to_file_time(){
	FILE *fi = fopen("1_time.txt", "w");
	fprintf(fi, "%lld\n", max_mass_time);
	for (int i = 0; i < max_mass_time; i++){
		fprintf(fi, "%lld %lld\n", mass_time[i], ssam_time[i]);
	}
	fclose(fi);
}

void push_time(){
	for (int i = 0; i < max_mass_time; i++)
	if (cotimeect_time(&mass_time[i])){
		ssam_time[i]++;
		return;
	}
	mass_time[max_mass_time] = global->time;
	ssam_time[max_mass_time] = 1;
	max_mass_time++;
}











//////////////////////////////////////////////////////////////////////////////////////

//Чтение суммированного значения
void read_max_count(){
	FILE *fi = fopen("all.txt", "r");
	fscanf(fi, "%d", &max_const);
	fclose(fi);
}

//Начальные символы (убирает)
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
	int flag_point = 0;
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
		case '.':
		{
					global->time = (global->time * 60 + se) * 1000000;
					flag_point = 1;
					break;
		}
		default:
			if (i>8 || flag_point)
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
	push_my_ip();
	push_rr();
	push_protocol();
	push_time();
	return 1;
}

int main(){
	read_max_count();
	global = (struct packet*)malloc(sizeof(struct packet));
	zlo = fopen("test", "rb");
	start_search();
	while (parse()){
		
	}//Доп операция над временем
	for (int i = max_mass_time; i > 0; i--)
		mass_time[i] -= mass_time[i - 1];
	mass_time[0] = 0;
	/*for (int i = 0; i < max_mass_time; i++)
		printf("%lld) %lld\n", mass_time[i], ssam_time[i]);
	system("pause");*/

	//Сортировка полученных данных

	quickSort_ip(0, max_mass_ip-1);
	quickSort_my_ip(0, max_mass_my_ip - 1);
	quickSort_rr(0, max_mass_rr - 1);
	quickSort_protocol(0, max_mass_protocol - 1);
	quickSort_time(0, max_mass_time - 1);
	/*for (int i = 0; i < max_mass_time; i++)
		printf("%lld) %lld\n", mass_time[i], ssam_time[i]);
	system("pause");*/

	//Значения
	int super_max = 0;
	for (int i = 0; i < max_mass_ip; i++)
		super_max += ssam_ip[i];
	printf("#############################\t%d\n", super_max);
	printf("ip: %d\n", max_mass_ip);
	printf("my_ip: %d\n", max_mass_my_ip);
	printf("rr: %d\n", max_mass_rr);
	printf("protocol: %d\n", max_mass_protocol);
	printf("time: %lld\n", max_mass_time);

	//Проверка
	
	double soda[5][6];

	for (int i = 0; i < 6; i++){
		load_ip();
		soda[0][i] = baes_ip();
		printf("ip:%lf\n", soda[0][i]);
		load_my_ip();
		soda[1][i] = baes_my_ip();
		printf("my_ip:%lf\n", soda[1][i]);
		load_rr();
		soda[2][i] = baes_rr();
		printf("rr:%lf\n", soda[2][i]);
		load_protocol();
		soda[3][i] = baes_protocol();
		printf("pro:%lf\n", soda[3][i]);
		load_time();
		soda[4][i] = baes_time();
		printf("time:%lf\n", soda[4][i]);
	}
	//printf("\n%lld\n", global->time);

	for (int i = 0; i < 6; i++){
		for (int u = 0; u < 5; u++)
			printf("%lf\t", soda[u][i]);
		printf("\n");
	}

	double proc[5];
	for (int i = 0; i < 6; i++)
		proc[i] = 0;
	for (int i = 0; i < 6; i++){
		for (int u = 0; u < 5; u++)
			proc[u] += soda[u][i];
	}
	printf("\n\n");
	for (int i = 0; i < 5; i++)
		printf("%lf\n", proc[i]);

	for (int i = 0; i < 6; i++){
		for (int u = 0; u < 5; u++)
			printf("%lf\t", fabs(soda[u][i]/proc[u]*100));
		printf("\n");
	}

	double maxim[6];
	for (int i = 0; i < 6; i++){
		maxim[i] = 0;
		for (int u = 0; u < 5; u++)
			maxim[i] += soda[u][i] / proc[u];
	}

	for (int i = 0; i < 6; i++)
		printf("%lf\n", maxim[i]);

	int rm = 0;
	double rmr = maxim[0];
	for (int i = 1; i < 6; i++)
	if (maxim[i]>rmr){
		rmr = maxim[i];
		rm = i;
	}
	printf("User %d\n", rm + 1);

	//Загрузка данных в тестовые файлы
	/*
	print_to_file_ip();
	print_to_file_my_ip();
	print_to_file_rr();
	print_to_file_protocol();
	print_to_file_time();*/

	//printf("%ld\n", baes());
	//load();
	//printf("%ld\n", baes());
	fclose(zlo);
	printf("%d\n", sizeof(struct packet));
}

