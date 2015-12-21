#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct data
{
	char* key;
	char* name;
	char* num;
};

typedef struct Node{		
	char* family; // Фамилия - ключ
	struct data *adress; // Адрес структуры с данными
	struct Node*next;
} Node_one;

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

void push(Node_one** head, char* family, struct data *adress) {
    Node_one *tmp = malloc(sizeof(Node_one));
    tmp->family = family;
    tmp->adress = adress;
    tmp->next = (*head);
    (*head) = tmp;
}

int main(int argc, char *argv[])
{
	struct data mass[10];
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

	free(ver); 

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

	Node_one* head[10] = {NULL}; int j;

	for (i = 0; i < 10; i++) {
		push(&head[sum[i]],mass[i].key,&mass[i]);
	}

	while(1){
		
		



	}


	return 0;
}