#include <stdio.h>      		 
#include <stdlib.h>

int Zhizn(char** new_mass,int i,int j,int stroka,int stolbik){
	int neighbors = 0; int x1,x2,y1,y2; int x = i, y = j;
	
	if (i-1 < 0)
		x1 = stroka-3;
	else x1 = i-1;
	if (i+1 > stroka-3)
		x2 = 0;
	else x2 = i+1;
	if (j-1 < 0)
		y1 = stolbik-1;
	else y1 = j-1;
	if (j+1 > stolbik-1)
		y2 = 0;
	else y2 = j+1;

	if (new_mass[x1][y1] == '+')
		neighbors++;
	if (new_mass[x][y1] == '+')
		neighbors++;
	if (new_mass[x][y2] == '+')
		neighbors++;
	if (new_mass[x1][y] == '+')
		neighbors++;
	if (new_mass[x2][y] == '+')
		neighbors++;
	if (new_mass[x1][y2] == '+')
		neighbors++;
	if (new_mass[x2][y1] == '+')
		neighbors++;
	if (new_mass[x2][y2] == '+')
		neighbors++;

	return neighbors;
}

int main(int argc,char* argv[]){

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

	char* main_line = NULL;
	char** new_mass = NULL;
	
	int stroka,stolbik,pole;

	fscanf(fileik,"%s\n");
	stroka = ftell(fileik);

	fseek(fileik,0,SEEK_END);
	pole = ftell(fileik);
	if(pole == 0){
		printf("ERROR 3");
		return 0;
	}
	if(pole % stroka == 0)
		stolbik = pole / stroka;
	else{
		printf("ERROR 4");
		return 0;
	}	
	main_line = malloc(sizeof(char)*pole);
	new_mass = malloc(sizeof(char)*stroka);
	int i,k;
	for(i = 0; i < stolbik; i++)
		new_mass[i] = &main_line[i*stroka];

	fseek(fileik,0,SEEK_SET);
	fread(main_line,1,pole,fileik);
	fclose(fileik);
	int sum = 0;
	for(i = 0; i < pole; i++)
		if(main_line[i] == '\n')
			sum++;
	if(sum != stolbik){
		printf("ERROR 5");
		return 0;
	}	
	char sym;
	int neighbors,j; 
	char *name = malloc(sizeof(char)*32); 

	while(1){

		while(1){
			fflush(stdin);

			printf("EXIT == G\n");
			printf("FILE == F\n");
			printf("NEXT == D\n");

			sym = getchar();

			if(sym == 'G')
				break;

			if(sym == 'F'){
				printf("Name file\n");
				scanf("%s", name);

				FILE* new_file;
				new_file = fopen(name, "wb");

				if (new_file == NULL) 
					perror("ERROR 6");

				for(i = 0; i < stolbik; i++){
					for(j = 0; j < stroka; j++)
						fwrite(&new_mass[i][j],1,sizeof(char),new_file);	
				}
				fclose(new_file);
			}

			if (sym == 'D')
				break;
		}	

		if (sym == 'G')
			break;

		for(i = 0; i < stolbik; i++){
			for(j = 0; j < stroka-2; j++){
				neighbors = Zhizn(new_mass,i,j,stroka,stolbik);
				if(neighbors == 3)
					new_mass[i][j] = '+';
				if(neighbors > 3 || neighbors < 2)
					new_mass[i][j] = '-';
			}
		}

		for(i = 0; i < stolbik; i++){
			for(j = 0; j < stroka; j++)
				printf("%c",new_mass[i][j]);			
		}
	} 
	free(*new_mass);
	free(main_line);
	free(name);

	return 0;
}