#include <stdio.h>
#include <math.h>

char* memcpyplus(char* ver,int x,int y){
	int h,j;
	char* mass = NULL;
	mass = (char*)malloc(sizeof(char)*(x-y));

	for (h = y + 1, j = 0; h < x; h++, j++){
		mass[j] = ver[h];
	}	
	mass[j] = '\0';
	return mass;
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

	free(ver);
	return 0;
}