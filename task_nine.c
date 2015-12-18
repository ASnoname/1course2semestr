#include <stdio.h>
#include <math.h>

void memcpyplus(char* mass,char* ver,int x,int y){
	int h,j;
	for (h = y + 1, j = 0; h < x - y; h++, j++)
		mass[j] = ver[h];
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

	for (i = 0; i < pole; i++)
	{
		if (ver[i] == 9 || '\r' || '\n'){
			for (l = 1; l < 41; l++)
				if (a[l] == -1)
					a[l] = i;		
		}
	}

	k = 0;
	for (i = 1; a[i] != -1; i++)
	{
		memcpyplus(mass[k].key,ver,a[i],a[i-1]);
		i++; 		
		memcpyplus(mass[k].name,ver,a[i],a[i-1]);
		i++;
		memcpyplus(mass[k].num,ver,a[i],a[i-1]);
		k++;
	}

	printf("%s\n", mass[2].key);

	free(ver);
	return 0;
}