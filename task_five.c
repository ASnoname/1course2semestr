#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <D:\proga\library2.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))

int proverka(char* stroka){

	if ((stroka[0] < '0') && (stroka[0] > '9') && (stroka[0] != '-'))
		return -1;

	if ((stroka[0] == '0') && (stroka[1] != ','))
		return -1;

	int i; int k = 0;
	for (i = 1; i < strlen(stroka); i++)
	{
		if ((stroka[i] < '0') && (stroka[i] > '9') && (stroka[i] != ','))
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

int lib(char* firstlongnumber, char* secondlongnumber, char operation){

	int t1 = proverka(firstlongnumber); if (t1 == -1) return -1;
	int t2 = proverka(secondlongnumber); if (t2 == -1) return -1;

	long_number* first = calloc(1,sizeof(long_number));
	long_number* second = calloc(1,sizeof(long_number));

	long_number* tempone = calloc(1,sizeof(long_number));
	long_number* temptwo = calloc(1,sizeof(long_number));

	reader(firstlongnumber,tempone);
	reader(secondlongnumber,temptwo);

	first_or_second(tempone, temptwo, &first, &second);

	


}