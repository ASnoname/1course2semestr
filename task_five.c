#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "D:\proga\library2.h"

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define ACCURACY 4

int proverka(char* stroka){

	if ((stroka[0] < '0') || (stroka[0] > '9') && (stroka[0] != '-'))
		return -1;

	if ((stroka[0] == '0') && (stroka[1] != ','))
		return -1;

	if (((stroka[0] == '-') || (stroka[0] == '+')) && (stroka[1] == ','))
		return -1;

	int i; int k = 0;
	for (i = 1; i < strlen(stroka); i++)
	{
		if ((stroka[i] < '0') || (stroka[i] > '9') && (stroka[i] != ','))
			return -1;	

		if (stroka[i] == ',')
			k++;

		if (k > 1)
			return -1;	
	}

	return 0;
}

void reader(char* tempstroka, long_number* structure){

	int h = 0;
	if (tempstroka[0] == '-'){
		h = 1;
		structure->znak = '-';
	}	
	else structure->znak = '+';

	int i = 1;
	while (tempstroka[i] != ',') i++;
	structure->comma = i-h;

	structure->number = calloc(strlen(tempstroka)-1-h,sizeof(int));

	int j;
	for (j = 0; j < i-h; j++)
		structure->number[j] = tempstroka[j+h] - 48;

	for (j = i-h; j < strlen(tempstroka)-1-h; j++)
		structure->number[j] = tempstroka[j+1+h] - 48;

	structure->length = strlen(tempstroka)-1-h;
}

void first_or_second(long_number* tempone, long_number* temptwo, long_number** first, long_number** second){

	if(tempone->comma > temptwo->comma){

		*first = tempone;
		*second = temptwo;
	}
	else if (tempone->comma < temptwo->comma)
	{
		*first = temptwo;
		*second = tempone;
	}
	else if (tempone->comma == temptwo->comma)
	{
		int prefer;
		if (tempone->length >= temptwo->length) 
			prefer = 1;
		else prefer = 2;

		int i;
		for (i = 0; i < MIN(tempone->length,temptwo->length); i++)
		{
			if (tempone->number[i] > temptwo->number[i]){

				*first = tempone;
				*second = temptwo;
				return;
			}
			else if (tempone->number[i] < temptwo->number[i]){

				*first = temptwo;
				*second = tempone;
				return;
			}
		}

		if (prefer == 2)
		{
			*first = temptwo;
			*second = tempone;
			return;
		}
		else 
		{
			*first = tempone;
			*second = temptwo;
			return;
		}
	}
}

void alignment(long_number* first, long_number* second){

	int diff = first->comma - second->comma;

	if (diff > 0)
	{
		second->number = realloc(second->number,(second->length + diff)*sizeof(int));
		int i;

		for (i = second->length-1; i >= 0; i--)
			second->number[i+diff] = second->number[i];

		second->length += diff;

		for (i = 0; i < diff; i++)
			second->number[i] = 0;
	}
	else if (diff < 0)
	{
		first->number = realloc(first->number,(first->length + diff)*sizeof(int));

		int i;
		for (i = first->length-1; i >= 0; i--)
			first->number[i+diff] = first->number[i];

		first->length += diff;

		for (i = 0; i < diff; i++)
			first->number[i] = 0;
	}

	diff = first->length - second->length;

	if (diff > 0)
	{
		second->number = realloc(second->number,sizeof(int)*(second->length + diff));
		second->length += diff;
		int i;
		for (i = 0; i < diff; i++)
			second->number[i] = 0;
	}
	else if (diff < 0)
	{
		first->length += diff;
		first->number = realloc(first->number,sizeof(int)*(first->length + diff));
		int i;
		for (i = 0; i < diff; i++)
			first->number[i] = 0;
	}
}

void numeral(long_number* first, long_number* second, int pointer, long_number* result, int i){

	int p = first->number[i] + pointer*second->number[i];
	if (p < 10)
		result->number[i+1] += p;
	else{

		result->number[i+1] += p-10; 
		result->number[i]++;
	}
}

void cleaner(long_number* result,int i){

	if (result->number[i] < 0)
	{
		result->number[i] += 10; 
		result->number[i-1] -= 1;
	}
}

int* summa(long_number* first, long_number* second, int pointer, long_number* result){

	alignment(first, second);
	result->number = calloc(first->length+1,sizeof(int));
	result->length = first->length+1;

	int i;
	for (i = first->length-1; i >= 0; i--)
		numeral(first,second,pointer,result,i);

	for (i = result->length-1; i >= 0 ; i--)
		cleaner(result,i);

	result->comma = first->comma + 1;

	return result->number;
}

char* int_to_string(long_number* result, int pointer){

	char* strochka = calloc(result->length+1+pointer,sizeof(char));
	int i = 0, j = 0;
	if(result->znak == '-'){
		strochka[i] = '-';
		i++;
	}

	if(result->number[0] == 0)
		j++;

	while(j != result->comma){
		strochka[i] = result->number[j] + 48;
		i++;
		j++;
	}

	strochka[i] = ',';
	i++;

	while(j != result->length){
		strochka[i] = result->number[j] + 48;
		i++;
		j++;
	}	

	return strochka;
}	

char* fintushami(long_number* first, long_number* second, char operation){

	long_number* result = calloc(1,sizeof(long_number));
	int pointer = 0;

	if ((first->znak == '-') && (operation == '+') && (second->znak == '-')){
		result->number = summa(first,second,1,result);
		result->znak = '-';
	}	
	else if ((first->znak == '-') && (operation == '-') && (second->znak == '+')){
		result->number = summa(first,second,1,result);
		result->znak = '-';
	}
	else if ((first->znak == '-') && (operation == '+') && (second->znak == '+')){
		pointer = 1;
		result->number = summa(first,second,-1,result);
		result->znak = '-';
	}
	else if ((first->znak == '-') && (operation == '-') && (second->znak == '-')){
		pointer = 1;
		result->number = summa(first,second,-1,result);
		result->znak = '-';
	}
	else if ((first->znak == '+') && (operation == '+') && (second->znak == '-')){
		pointer = 1;
		result->number = summa(first,second,-1,result);	
		result->znak = '+';
	}
	else if ((first->znak == '+') && (operation == '-') && (second->znak == '+')){
		pointer = 1;
		result->number = summa(first,second,-1,result);
		result->znak = '+';
	}
	else if ((first->znak == '+') && (operation == '+') && (second->znak == '+')){
		result->number = summa(first,second,1, result);
		result->znak = '+';
	}
	else if ((first->znak == '+') && (operation == '-') && (second->znak == '-')){
		result->number = summa(first,second,1,result);	
		result->znak = '+';
	}	

	return int_to_string(result,pointer);						
}

void numeral_multi(long_number* first,long_number* second, long_number* result, int i, int h){

	int j; int p;
	for (j = first->length-1; j >= 0; j--)
	{
		p = first->number[j] * second->number[i];

		result->number[j-h+1] += p;
	}
}

void cleaner_multi(long_number* result, int i){

	if (result->number[i] > 10)
	{
		result->number[i-1] += result->number[i] / 10;
		result->number[i] %= 10;
	}
}

char* multiplication(long_number* first,long_number* second){

	int i = 0; 
	int j = 0; int h = 0;

	long_number* result = calloc(1,sizeof(long_number));
	result->number = calloc(first->length+1,sizeof(int));
	result->length = first->length+1;
	result->comma = (first->length + second->length) - (first->comma + second->comma);

	if (first->znak == second->znak)
		result->znak = '+';
	if (first->znak != second->znak)
		result->znak = '-';
	
	for (i = second->length-1; i >= 0; i-- ,h++)
		numeral_multi(first,second, result, i,h);

	for (i = result->length-1; i > 0; i--) 
		cleaner_multi(result,i);

	return int_to_string(result, (result->znak == '-'));
}

char* division(long_number* first,long_number* second){

	int i = 0; 
	int j = 0; int h = 0;

	long_number* result = calloc(1,sizeof(long_number));

	if (first->znak == second->znak)
		result->znak = '+';
	if (first->znak != second->znak)
		result->znak = '-';
	
	result->number = calloc(ACCURACY+(first->znak == '-')+1,sizeof(int));
	result->length = ACCURACY + (first->znak == '-')+1;
	result->comma = MAX(first->length - first->comma, second->length - second->comma);

	

	return "hh";
}

char* lib(char* firstlongnumber, char* secondlongnumber, char operation){

	// int t1 = proverka(firstlongnumber); 
	// if (t1 == -1) 
	// 	return "error";
	// int t2 = proverka(secondlongnumber); 
	// if (t2 == -1) 
	// 	return "error";

	long_number* first = calloc(1,sizeof(long_number));
	long_number* second = calloc(1,sizeof(long_number));

	long_number* tempone = calloc(1,sizeof(long_number));
	long_number* temptwo = calloc(1,sizeof(long_number));

	reader(firstlongnumber,tempone);
	reader(secondlongnumber,temptwo);

	first_or_second(tempone, temptwo, &first, &second);

	if ((operation == '+') || (operation == '-'))
		return fintushami(first,second,operation);

	if (operation == '*')
		return multiplication(first,second);

	if (operation == '/')
		return division(first,second);
}