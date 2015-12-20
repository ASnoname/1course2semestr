#include <stdio.h>
#include <math.h>
#include <stdlib.h>

char* memcpyplus(char* ver,int x,int y){
	int h,j;
	char* mass = NULL;
	mass = malloc(sizeof(char)*(x-y));

	for (h = y + 1, j = 0; h < x; h++, j++){
		mass[j] = ver[h];
	}	
	mass[j] = '\0';
	return mass;
}

void push(Node_one** head, char family, int adress) {
    Node_one *tmp = malloc(sizeof(Node_one));
    tmp->family = family;
    tmp->adress = adress;
    tmp->next = (*head);
    (*head) = tmp;
}

int main(int argc, char *argv[])
{
	
	char* light; 

	if(argc != 2){
		printf("ERROR 1");
		return 0;
	}
	else 
		sscanf(argv[1], "%s", &light);

	FILE* fileik;
	fileik = fopen(argv[1], "rb");

	if(fileik == NULL){
		printf("ERROR 2");
		return 0;
	}

	int k,l,i;

	struct data
	{
		char* key;
		char* name;
		char* num;
	} mass[10];

	for(i = 0; feof(fileik) == 0; i++)
		fgetc(fileik);

	int pole = i; fseek(fileik,0,SEEK_SET);

	char* ver = malloc(sizeof(char)*pole);

	for ( i = 0; i < pole; i++)
		ver[i] = fgetc(fileik);

	fclose(fileik); int a[42] = {-1};

	for (i = 0; i < 42; i++) {
		a[i] = -1;
	}


	for (i = 0; i < pole; i++)
	{
		if (ver[i] == 9 || ver[i] == '\r' || ver[i] == '\n'){
			for (l = 1; l < 41; l++){
				if (a[l] == -1){
					a[l] = i;	
					break;
				}	
			}			
		}
	}

	k = 0;
	for (i = 1; a[i] != -1; i++)
	{
		mass[k].key = memcpyplus(ver,a[i],a[i-1]);
		i++;
		mass[k].name = memcpyplus(ver,a[i],a[i-1]);
		i++;
		mass[k].num = memcpyplus(ver,a[i],a[i-1]);
		i++;
		k++;
	}

//Хеширование начало

	int summer[10] = {0}; int key_len[10]; int sum[10];

	for(i = 0; i < 10; i++)
		key_len[i] = strlen(mass[i].key);

	for (i = 0; i < 10; i++)
		for (k = 0; k < key_len[i]; k++)
			summer[i] += mass[i].key[k];

	for(i = 0; i < 10; i++)
		sum[i] = summer[i] % 10;	

//Хеширование конец	

	typedef struct Node Node_one;

	struct Node{
		char family; // Фамилия - ключ
		int adress; // Адрес структуры с данными
		Node_one *next;
	};

	int size_spisok[10] = {0}; 

	for (i = 0; i < 10; i++)
	{
		switch (sum[i]){
			case 0 : size_spisok[0] += 1;
			case 1 : size_spisok[1] += 1;
			case 2 : size_spisok[2] += 1;
			case 3 : size_spisok[3] += 1;
			case 4 : size_spisok[4] += 1;
			case 5 : size_spisok[5] += 1;
			case 6 : size_spisok[6] += 1;
			case 7 : size_spisok[7] += 1;
			case 8 : size_spisok[8] += 1;
			case 9 : size_spisok[9] += 1;
		}
	}

	Node_one* head[10] = {NULL}; int j;

	for (i = 0; i < 10; i++)
	{
		for (k = 0, j = 0; k < size_spisok[i] && j < 10; k++, j++)
		{
			if(sum[j] == k){
				push(*head[i],mass[j].key,&mass[j]); 
			}
		}
	}



	free(ver); char fam[15] = {0}; int pass; 

/*	while(1){
		sum = 0;
		gets(fam); 

		for (i = 0; i < 15; i++)
			sum += fam[i];

		pass = sum % 10;
		



	}
*/

	return 0;
}