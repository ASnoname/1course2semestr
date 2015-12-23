#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define Happy_New_Year 10

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
	struct data mass[Happy_New_Year];
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

	fclose(fileik); int a[Happy_New_Year*4 +2] = {-1};

	for (i = 0; i < Happy_New_Year*4 +2; i++) {
		a[i] = -1;
	}


	for (i = 0; i < pole; i++)
	{
		if (ver[i] == 9 || ver[i] == '\r' || ver[i] == '\n'){
			for (l = 1; l < Happy_New_Year*4 +1; l++){
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

	int summer[Happy_New_Year] = {0}; int key_len[Happy_New_Year]; int sum[Happy_New_Year];

	for(i = 0; i < Happy_New_Year; i++)
		key_len[i] = strlen(mass[i].key);

	for (i = 0; i < Happy_New_Year; i++)
		for (k = 0; k < key_len[i]; k++)
			summer[i] += mass[i].key[k];

	for(i = 0; i < Happy_New_Year; i++)
		sum[i] = summer[i] % Happy_New_Year;	

//Хеширование конец

	Node_one* head[Happy_New_Year] = {NULL}; int j;

	for (i = 0; i < Happy_New_Year; i++) {
		push(&head[sum[i]],mass[i].key,&mass[i]);
	}

	char* input = malloc(sizeof(char)*15); int len_input = 0; int sum_input = 0; int summer_input = 0; 
	Node_one* temp_head = NULL; struct data* tmp_tmp; int o; int er = 0;

	while(1){

		summer_input = 0; o = 0; i = 0; er = 0;

		do{
			scanf("%c", input+i);
			o++; i++;
		} while (input[i-1] != '\n');
		if(o == 1 && input[0]=='\n'){
			i = 0;
			do{
				scanf("%c", input+i);
				o++; i++;
			} while (input[i-1] != '\n');
		}

		if (o == 2 && input[0] == '\n')
			break;
		else
		{
			input[i-1] = '\0';	
		}

		for (i = 0; i < Happy_New_Year; i++)
		{
			if (!strcmp(input, mass[i].key))
				er++;
		}

		if (er == 0)
			{
				printf("ERROR 3\n");
			}
			else
			{

		len_input = strlen(input);

		for (i = 0; i < len_input; i++)
			summer_input += input[i];
		sum_input = summer_input % Happy_New_Year;
		temp_head = head[sum_input];

		for (i = 0; i < Happy_New_Year; i++)
		{
			if (!strcmp(input, temp_head->family))
			{
				tmp_tmp = temp_head->adress;
				printf("%s\n%s\n%s\n", tmp_tmp->key, tmp_tmp->name, tmp_tmp->num);
				break;
			}
			temp_head = temp_head->next;
		}

		temp_head = NULL;
		}

	}

	free(input);
	free(*head);
	return 0;
}