// qwer.cpp: ���������� ����� ����� ��� ����������� ����������.
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

char s[10000];

//��������� ������ ������
struct packet{
	long long int time;
	int ip;
	int my_ip;
	int rr;
	//int section;
	int protocol;
};

//�������� �� ��������� �� ������� ���������
struct packet *global;

//������� ������� db ������
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
	����� ������ ��������� � �� ���� �������� ����*/





int size_mass_ip;//������ ������ �������
int *mass_ip; //������ ������ ������� �������� ��������� ip
int *ssam_ip; //������ ���������� ��������� ������� ����
int *old_mass_ip; //���� �����, ������ ����������� ������
int *old_ssam_ip; //���� �����
int max_mass_ip; //������ ������� ��� ip �������
int old_max_mass_ip; //������ ������� ��� ������������ ������

//����� �������� ip � ������������ �������
//�������� �����
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

//��������� ��������� ���� � ������� �� ���� ip � �� ����������
// (������ ������������ ������������)
void load_ip(){
	int mmmax = 0;
	old_max_mass_ip = 0;
	char sp[100];
	sprintf(sp, "%d_ip.txt", ++keeek);
	FILE *fi = fopen(sp, "r");
	fscanf(fi, "%d", &old_max_mass_ip);
	old_mass_ip = calloc(sizeof(int), old_max_mass_ip);
	old_ssam_ip = calloc(sizeof(int), old_max_mass_ip);
	for (int i = 0; i < old_max_mass_ip; i++){
		fscanf(fi, "%d %d", &old_mass_ip[i], &old_ssam_ip[i]);
		mmmax += old_ssam_ip[i];
	}
	//printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\t%d\n", mmmax);
	fclose(fi);
}

//���������� ���������� �����
double baes_ip(){
	double result = 0.0;
	for (int i = 0; i < max_mass_ip; i++){
		int a = pos_ip(mass_ip[i]);
		result += a*log(((double)(ssam_ip[i] + z)) / ((to_ip)+z*max_const));
		//printf("! = %lf\n", result);
	}
	//printf("! = %lf\n", result);
	return result;
}

//���������� ���������� �� ip �������
int correct_ip(struct packet * mu){
	if (mu->ip == global->ip)
		return 1;
	else return 0;
}

//���������� ������� ����� ���������
void quickSort_ip(int left, int right)
{
	int pivot; // ����������� �������
	int l_hold = left; //����� �������
	int r_hold = right; // ������ �������
	pivot = mass_ip[left];
	int pivot_help = ssam_ip[left];
	while (left < right) // ���� ������� �� ���������
	{
		while ((mass_ip[right] >= pivot) && (left < right))
			right--; // �������� ������ ������� ���� ������� [right] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			mass_ip[left] = mass_ip[right]; // ���������� ������� [right] �� ����� ������������
			ssam_ip[left] = ssam_ip[right];
			left++; // �������� ����� ������� ������ 
		}
		while ((mass_ip[left] <= pivot) && (left < right))
			left++; // �������� ����� ������� ���� ������� [left] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			mass_ip[right] = mass_ip[left]; // ���������� ������� [left] �� ����� [right]
			ssam_ip[right] = ssam_ip[left];
			right--; // �������� ������ ������� ������ 
		}
	}
	mass_ip[left] = pivot; // ������ ����������� ������� �� �����
	ssam_ip[left] = pivot_help;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // ���������� �������� ���������� ��� ����� � ������ ����� �������
		quickSort_ip(left, pivot - 1);
	if (right > pivot)
		quickSort_ip(pivot + 1, right);
}

//������� � ���� ������� ������������
void print_to_file_ip(){
	FILE *fi = fopen("1_ip.txt", "w");
	fprintf(fi, "%d\n", max_mass_ip);
	for (int i = 0; i < max_mass_ip; i++){
		fprintf(fi, "%d %d\n", mass_ip[i], ssam_ip[i]);
	}
	fclose(fi);
}

//��������� ip-������ � ���� ����
void push_ip(){
	for (int i = 0; i < max_mass_ip;i++)
	if (correct_ip(&mass_ip[i])){
		ssam_ip[i]++;
		return;
	}
	mass_ip[max_mass_ip] = global->ip;
	ssam_ip[max_mass_ip] = 1;
	max_mass_ip++;
	if (max_mass_ip % 1000 == 0){
		size_mass_ip += 1000;
		mass_ip = realloc(mass_ip, (size_mass_ip*sizeof(int)));
		ssam_ip = realloc(ssam_ip, (size_mass_ip*sizeof(int)));
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////my_ip/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////



int size_mass_my_ip;
int *mass_my_ip;
int *ssam_my_ip;
int *old_mass_my_ip;
int *old_ssam_my_ip;
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
	old_mass_my_ip = calloc(sizeof(int), old_max_mass_my_ip);
	old_ssam_my_ip = calloc(sizeof(int), old_max_mass_my_ip);
	for (int i = 0; i < old_max_mass_my_ip; i++){
		fscanf(fi, "%d %d", &old_mass_my_ip[i], &old_ssam_my_ip[i]);
		mmmax += old_ssam_my_ip[i];
	}
	//printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n%d\n\n", mmmax);
	fclose(fi);
}

double baes_my_ip(){
	double result = 0.0;
	for (int i = 0; i < max_mass_my_ip; i++){
		int a = pos_my_ip(mass_my_ip[i]);
		result += a*log(((double)(ssam_my_ip[i] + z)) / ((to_my_ip)+z*max_const));
		//printf("! = %lf\n", result);
	}
	//printf("! = %lf\n", result);
	return result;
}

int correct_my_ip(struct packet * mu){
	if (mu->my_ip == global->my_ip)
		return 1;
	else return 0;
}

void quickSort_my_ip(int left, int right)
{
	int pivot; // ����������� �������
	int l_hold = left; //����� �������
	int r_hold = right; // ������ �������
	pivot = mass_my_ip[left];
	int pivot_help = ssam_my_ip[left];
	while (left < right) // ���� ������� �� ���������
	{
		while ((mass_my_ip[right] >= pivot) && (left < right))
			right--; // �������� ������ ������� ���� ������� [right] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			mass_my_ip[left] = mass_my_ip[right]; // ���������� ������� [right] �� ����� ������������
			ssam_my_ip[left] = ssam_my_ip[right];
			left++; // �������� ����� ������� ������ 
		}
		while ((mass_my_ip[left] <= pivot) && (left < right))
			left++; // �������� ����� ������� ���� ������� [left] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			mass_my_ip[right] = mass_my_ip[left]; // ���������� ������� [left] �� ����� [right]
			ssam_my_ip[right] = ssam_my_ip[left];
			right--; // �������� ������ ������� ������ 
		}
	}
	mass_my_ip[left] = pivot; // ������ ����������� ������� �� �����
	ssam_my_ip[left] = pivot_help;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // ���������� �������� ���������� ��� ����� � ������ ����� �������
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
	if (max_mass_my_ip % 1000 == 0){
		size_mass_my_ip += 1000;
		mass_my_ip = realloc(mass_my_ip, (size_mass_my_ip*sizeof(int)));
		ssam_my_ip = realloc(ssam_my_ip, (size_mass_my_ip*sizeof(int)));
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////rr/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////










int size_mass_rr;
int *mass_rr;
int *ssam_rr;
int *old_mass_rr;
int *old_ssam_rr;
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


void load_rr(){
	int mmmax = 0;
	old_max_mass_rr = 0;
	char sp[100];
	sprintf(sp, "%d_rr.txt", keeek);
	FILE *fi = fopen(sp, "r");
	fscanf(fi, "%d", &old_max_mass_rr);
	old_mass_rr = calloc(sizeof(int), old_max_mass_rr);
	old_ssam_rr = calloc(sizeof(int), old_max_mass_rr);
	for (int i = 0; i < old_max_mass_rr; i++){
		fscanf(fi, "%d %d", &old_mass_rr[i], &old_ssam_rr[i]);
		mmmax += old_ssam_rr[i];
	}
	//printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n%d\n\n", mmmax);
	fclose(fi);
}

double baes_rr(){
	double result = 0.0;
	for (int i = 0; i < max_mass_rr; i++){
		int a = pos_rr(mass_rr[i]);
		result += a*log(((double)(ssam_rr[i] + z)) / ((to_rr)+z*max_const));
		//printf("! = %lf\n", result);
	}
	//printf("! = %lf\n", result);
	return result;
}


int correct_rr(struct packet * mu){
	if (mu->rr == global->rr)
		return 1;
	else return 0;
}

void quickSort_rr(int left, int right)
{
	int pivot; // ����������� �������
	int l_hold = left; //����� �������
	int r_hold = right; // ������ �������
	pivot = mass_rr[left];
	int pivot_help = ssam_rr[left];
	while (left < right) // ���� ������� �� ���������
	{
		while ((mass_rr[right] >= pivot) && (left < right))
			right--; // �������� ������ ������� ���� ������� [right] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			mass_rr[left] = mass_rr[right]; // ���������� ������� [right] �� ����� ������������
			ssam_rr[left] = ssam_rr[right];
			left++; // �������� ����� ������� ������ 
		}
		while ((mass_rr[left] <= pivot) && (left < right))
			left++; // �������� ����� ������� ���� ������� [left] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			mass_rr[right] = mass_rr[left]; // ���������� ������� [left] �� ����� [right]
			ssam_rr[right] = ssam_rr[left];
			right--; // �������� ������ ������� ������ 
		}
	}
	mass_rr[left] = pivot; // ������ ����������� ������� �� �����
	ssam_rr[left] = pivot_help;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // ���������� �������� ���������� ��� ����� � ������ ����� �������
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
	if (max_mass_rr % 1000 == 0){
		size_mass_rr += 1000;
		mass_rr = realloc(mass_rr, (size_mass_rr*sizeof(int)));
		ssam_rr = realloc(ssam_rr, (size_mass_rr*sizeof(int)));
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////protocol//////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////










int size_mass_protocol;
int *mass_protocol;
int *ssam_protocol;
int *old_mass_protocol;
int *old_ssam_protocol;
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



void load_protocol(){
	int mmmax = 0;
	old_max_mass_protocol = 0;
	char sp[100];
	sprintf(sp, "%d_protocol.txt", keeek);
	FILE *fi = fopen(sp, "r");
	fscanf(fi, "%d", &old_max_mass_protocol);
	old_mass_protocol = calloc(sizeof(int), old_max_mass_protocol);
	old_ssam_protocol = calloc(sizeof(int), old_max_mass_protocol);
	for (int i = 0; i < old_max_mass_protocol; i++){
		fscanf(fi, "%d %d", &old_mass_protocol[i], &old_ssam_protocol[i]);
		mmmax += old_ssam_protocol[i];
	}
	//printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n%d\n\n", mmmax);
	fclose(fi);
}

double baes_protocol(){
	double result = 0.0;
	for (int i = 0; i < max_mass_protocol; i++){
		int a = pos_protocol(mass_protocol[i]);
		result += a*log(((double)(ssam_protocol[i] + z)) / ((to_protocol)+z*max_const));
		//printf("! = %lf\n", result);
	}
	//printf("! = %lf\n", result);
	return result;
}


int coprotocolect_protocol(struct packet * mu){
	if (mu->protocol == global->protocol)
		return 1;
	else return 0;
}

void quickSort_protocol(int left, int right)
{
	int pivot; // ����������� �������
	int l_hold = left; //����� �������
	int r_hold = right; // ������ �������
	pivot = mass_protocol[left];
	int pivot_help = ssam_protocol[left];
	while (left < right) // ���� ������� �� ���������
	{
		while ((mass_protocol[right] >= pivot) && (left < right))
			right--; // �������� ������ ������� ���� ������� [right] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			mass_protocol[left] = mass_protocol[right]; // ���������� ������� [right] �� ����� ������������
			ssam_protocol[left] = ssam_protocol[right];
			left++; // �������� ����� ������� ������ 
		}
		while ((mass_protocol[left] <= pivot) && (left < right))
			left++; // �������� ����� ������� ���� ������� [left] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			mass_protocol[right] = mass_protocol[left]; // ���������� ������� [left] �� ����� [right]
			ssam_protocol[right] = ssam_protocol[left];
			right--; // �������� ������ ������� ������ 
		}
	}
	mass_protocol[left] = pivot; // ������ ����������� ������� �� �����
	ssam_protocol[left] = pivot_help;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // ���������� �������� ���������� ��� ����� � ������ ����� �������
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
	if (max_mass_protocol % 1000 == 0){
		size_mass_protocol += 1000;
		mass_protocol = realloc(mass_protocol, (size_mass_protocol*sizeof(int)));
		ssam_protocol = realloc(ssam_protocol, (size_mass_protocol*sizeof(int)));
	}
}




///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////time////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////










long long int size_mass_time;
long long int *mass_time;
long long int *ssam_time;
long long int *old_mass_time;
long long int *old_ssam_time;
long long int max_mass_time;
long long int old_max_mass_time;

long long int pos_time(long long int a)
{
	long long int low, high, middle;
	low = 1;
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
	fscanf(fi, "%ld", &old_max_mass_time);
	old_mass_time = calloc(sizeof(long long int), old_max_mass_time);
	old_ssam_time = calloc(sizeof(long long int), old_max_mass_time);
	for (int i = 0; i < old_max_mass_time; i++){
		fscanf(fi, "%ld %ld", &old_mass_time[i], &old_ssam_time[i]);
		mmmax += old_ssam_time[i];
	}
	//printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n%d\n\n", mmmax);
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
	//printf("! = %lf\n", result);
	return result;
}


long long int cotimeect_time(struct packet * mu){
	if (mu->time == global->time)
		return 1;
	else return 0;
}

void quickSort_time(int left, int right)
{
	long long int pivot; // ����������� �������
	int l_hold = left; //����� �������
	int r_hold = right; // ������ �������
	pivot = mass_time[left];
	long long int pivot_help = ssam_time[left];
	while (left < right) // ���� ������� �� ���������
	{
		while ((mass_time[right] >= pivot) && (left < right))
			right--; // �������� ������ ������� ���� ������� [right] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			mass_time[left] = mass_time[right]; // ���������� ������� [right] �� ����� ������������
			ssam_time[left] = ssam_time[right];
			left++; // �������� ����� ������� ������ 
		}
		while ((mass_time[left] <= pivot) && (left < right))
			left++; // �������� ����� ������� ���� ������� [left] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			mass_time[right] = mass_time[left]; // ���������� ������� [left] �� ����� [right]
			ssam_time[right] = ssam_time[left];
			right--; // �������� ������ ������� ������ 
		}
	}
	mass_time[left] = pivot; // ������ ����������� ������� �� �����
	ssam_time[left] = pivot_help;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // ���������� �������� ���������� ��� ����� � ������ ����� �������
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
	/*if (max_mass_time>=1000){
		printf("\n\n");
		for (int i = 0; i < 1000; i++)
			printf("%d)%lld  ", i, mass_time[i]);
		printf("!!!\n");

		for (int i = 0; i < 1000; i++)
			printf("%d)%lld  ", i, ssam_time[i]);
		system("pause");
	}*/
	if (max_mass_time % 1000 == 0){
		size_mass_time += 1000;
		mass_time = realloc(mass_time, (size_mass_time*sizeof(long long int)));
		ssam_time = realloc(ssam_time, (size_mass_time*sizeof(long long int)));
	}
}











//////////////////////////////////////////////////////////////////////////////////////

//������ �������������� ��������
void read_max_count(){
	FILE *fi = fopen("all.txt", "r");
	fscanf(fi, "%d", &max_const);
	fclose(fi);
}

//��������� ������� (�������)
void start_search(){
	fgets(s, sizeof(s), zlo);
	//fgets(s, sizeof(s), zlo);
	//fgets(s, sizeof(s), zlo);
	//fgets(s, sizeof(s), zlo);
	//fgets(s, sizeof(s), zlo);
}

//��������� ip � �����
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

//��������� �����
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

//��������� ��������
void next_s(int*i, int*i_start){
	*i += 3;
	*i_start = *i;
	while (s[++(*i)] != '"');
	s[*i] = '\0';
}

//����� ������
void print_packet(struct packet* p){
	printf("\ntime:%lld\nip1:%d\nip2:%d\nprotocol:%d\nlength:%d\n", p->time, p->ip, p->my_ip, p->protocol, p->rr);
}

//������ ���� �����
int parse(){
	s[0] = '\0';
	fgets(s, sizeof(s), zlo);
	//printf("%s", s);
	if (s[0]=='\0') return 0;
	//printf("%s\n", s);
	/*������� �����*/
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

//�������������� ���������� ��� �������������
void init(){
	size_mass_ip = 1000;
	mass_ip = calloc(sizeof(int), 1000);
	ssam_ip = calloc(sizeof(int), 1000);
	size_mass_my_ip = 1000;
	mass_my_ip = calloc(sizeof(int), 1000);
	ssam_my_ip = calloc(sizeof(int), 1000);
	size_mass_rr = 1000;
	mass_rr = calloc(sizeof(int), 1000);
	ssam_rr = calloc(sizeof(int), 1000);
	size_mass_protocol = 1000;
	mass_protocol = calloc(sizeof(int), 1000);
	ssam_protocol = calloc(sizeof(int), 1000);
	size_mass_time = 1000;
	mass_time = calloc(sizeof(long long int), 1000);
	ssam_time = calloc(sizeof(long long int), 1000);
}

//������� ������ ����� ������������� ��� ������ ��������� ������������
void deinit_after_file(){
	free(old_mass_ip);
	free(old_ssam_ip);
	free(old_mass_my_ip);
	free(old_ssam_my_ip);
	free(old_mass_rr);
	free(old_ssam_rr);
	free(old_mass_protocol);
	free(old_ssam_protocol);
	free(old_mass_time);
	free(old_ssam_time);
}

//������� ������ ����� ���������� �������������
void deinit(){
	size_mass_ip = 0;
	max_mass_ip = 0;
	free(mass_ip);
	free(ssam_ip);
	size_mass_my_ip = 0;
	max_mass_my_ip = 0;
	free(mass_my_ip);
	free(ssam_my_ip);
	size_mass_rr = 0;
	max_mass_rr = 0;
	free(mass_rr);
	free(ssam_rr);
	size_mass_protocol = 0;
	max_mass_protocol = 0;
	free(mass_protocol);
	free(ssam_protocol);
	size_mass_time = 0;
	max_mass_time = 0;
	free(mass_time);
	free(ssam_time);
}

//���������� �������� �������������
#define USER 6
//��������� ��� �������������
#define PARAMETRS 5

int main(){
	init();
	read_max_count();
	global = (struct packet*)malloc(sizeof(struct packet));
	zlo = fopen("test", "rb");
	start_search();
	while (parse()){
		//if (max_mass_time == 1000) break;
	}//��� �������� ��� ��������
	for (int i = max_mass_time; i > 0; i--)
		mass_time[i] -= mass_time[i - 1];
	mass_time[0] = 0;
	/*for (int i = 0; i < max_mass_time; i++)
		printf("%lld) %lld\n", mass_time[i], ssam_time[i]);
	system("pause");*/

	//���������� ���������� ������

	quickSort_ip(0, max_mass_ip-1);
	quickSort_my_ip(0, max_mass_my_ip - 1);
	quickSort_rr(0, max_mass_rr - 1);
	quickSort_protocol(0, max_mass_protocol - 1);
	quickSort_time(0, max_mass_time - 1);
	/*for (int i = 0; i < max_mass_time; i++)
		printf("%lld) %lld\n", mass_time[i], ssam_time[i]);
	system("pause");*/

	//��������
	int super_max = 0;
	for (int i = 0; i < max_mass_ip; i++)
		super_max += ssam_ip[i];
	printf("Value::\t%d\n", super_max);
	printf("ip: %d\n", max_mass_ip);
	printf("my_ip: %d\n", max_mass_my_ip);
	printf("rr: %d\n", max_mass_rr);
	printf("protocol: %d\n", max_mass_protocol);
	printf("time: %lld\n", max_mass_time);

	//��������
	
	double soda[PARAMETRS][USER];
	//��������� ������ �������� [��������][����]
	for (int i = 0; i < USER; i++){
		load_ip();
		soda[0][i] = baes_ip();
		//printf("ip:%lf\n", soda[0][i]);
		load_my_ip();
		soda[1][i] = baes_my_ip();
		//printf("my_ip:%lf\n", soda[1][i]);
		load_rr();
		soda[2][i] = baes_rr();
		//printf("rr:%lf\n", soda[2][i]);
		load_protocol();
		soda[3][i] = baes_protocol();
		//printf("pro:%lf\n", soda[3][i]);
		load_time();
		soda[4][i] = baes_time();
		//printf("time:%lf\n", soda[4][i]);

		deinit_after_file();

	}

	//������� ������
	deinit();

	//printf("\n%lld\n", global->time);
	printf("\nNaive bayes result:\n");
	for (int i = 0; i < USER; i++){
		printf("User %d: ", i + 1);
		for (int u = 0; u < PARAMETRS; u++)
			printf("%lf\t", soda[u][i]);
		printf("\n");
	}
	//������� ����� ��� ������� ��������� (��� �������� ������������� ��������)
	double proc[PARAMETRS];
	for (int i = 0; i < USER; i++)
		proc[i] = 0;
	for (int i = 0; i < USER; i++){
		for (int u = 0; u < PARAMETRS; u++)
			proc[u] += soda[u][i];
	}
	printf("\nSumm:\n");
	for (int i = 0; i < PARAMETRS; i++)
		printf("%lf\t", proc[i]);
	printf("\n\n");

	printf("Chance of belonging:\n");
	for (int i = 0; i < USER; i++){
		printf("User %d: ", i+1);
		for (int u = 0; u < PARAMETRS; u++)
		if (proc[u] != 0.0)
			printf("%lf\t", fabs(soda[u][i]/proc[u]*100));
		printf("\n");
	}

	//��� ������������ �������� ���������
	const double lol[] = { 0.73, 0.59, 0.31, 0.23, 0.69 };

	//������� �������� ��� ������� �����
	double maxim[USER];
	for (int i = 0; i < USER; i++){
		maxim[i] = 0;
		for (int u = 0; u < PARAMETRS; u++)
		if (proc[u] != 0.0)
			maxim[i] += soda[u][i] / proc[u] * lol[u];
	}

	printf("\nResult value:\n");
	for (int i = 0; i < USER; i++)
		printf("User %d = %lf\n", i+1, maxim[i]);
	//� ����� ���������� - �������
	int rm = 0;
	double rmr = maxim[0];
	for (int i = 1; i < USER; i++)
	if (maxim[i]>rmr){
		rmr = maxim[i];
		rm = i;
	}

	printf("\n");
	if (rmr < 1 / USER * PARAMETRS)
		printf("Warning!\n");
	printf("It`s user %d\n", rm + 1);
	//�������� ������ � �������� �����
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
	//printf("%d\n", sizeof(struct packet));
}

