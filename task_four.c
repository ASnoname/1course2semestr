#include <stdio.h>
#include <stdlib.h>

void part1(FILE* file, int** key_coo, int* weight, int* high){

    int temp = 0; 
    char c;

	while(1){
		c = fgetc(file);			

		if(c == 13){

			*weight = temp + 1;
			(*high)++;
			c = fgetc(file);
			temp = -1;
		}
		else temp++;

		if (c == 'A'){
			key_coo[0][0] = temp; 
			key_coo[0][1] = *high; 	
		}	
		if (c == 'B'){
			key_coo[1][0] = temp; 
			key_coo[1][1] = *high; 	
		}

		if (c == EOF) break;
	}
}

void part2(FILE* file, int** labirint, int weight, int high){

	fseek(file,0,SEEK_SET);
	int i,j;
	char c;

	for (j = 0; j < high; j++)
	{
		for (i = 0; i < weight; i++){

			c = fgetc(file);

			if (c == 13){
				c = fgetc(file);
				c = fgetc(file);
			}	

			labirint[i][j] = c;
		}
	}
}

void correct(int** labirint, int weight, int high){

	int i,j;

	for (i = 1; i < high-1; i++){
		for (j = 1; j < weight-1; j++){
			printf("%c", labirint[j][i]);
		}
		printf("\n");
	}	
}

void part3(int** labirint, int** copylabirint, int** key_coo, int weight, int high){

	int i,j;

	for (i = 0; i < high; i++){
		for (j = 0; j < weight; j++){

			if (labirint[j][i] == 32)
				copylabirint[j][i] = 0;
			else
				copylabirint[j][i] = labirint[j][i];
		}
	}
	
	copylabirint[key_coo[0][0]][key_coo[0][1]] = 0;	
	copylabirint[key_coo[1][0]][key_coo[1][1]] = 0;	
}

void part4(int** copylabirint, int** key_coo, int weight, int high){

	int i,j;

	for (i = 1; i < high-1; i++)
	{
		for (j = 1; j < weight-1; j++)
		{
			if (copylabirint[j][i] != 35){
				if ((copylabirint[j+1][i] == 42) && (copylabirint[1][i] != 35)) 
						copylabirint[j][i] += 1;

				else if ((copylabirint[j+1][i] != 35) && (copylabirint[j+1][i] != 42))
					copylabirint[j][i] += 1;

				if ((copylabirint[j-1][i] == 42) && (copylabirint[weight-2][i] != 35))
						copylabirint[j][i] += 1;

				else if ((copylabirint[j-1][i] != 35) && (copylabirint[j-1][i] != 42))
					copylabirint[j][i] += 1;

				if ((copylabirint[j][i+1] == 42) && (copylabirint[j][1] != 35))
						copylabirint[j][i] += 1;

				else if ((copylabirint[j][i+1] != 35) && (copylabirint[j][i+1] != 42))
					copylabirint[j][i] += 1;	

				if ((copylabirint[j][i-1] == 42) && (copylabirint[j][high-2] != 35))
						copylabirint[j][i] += 1;

				else if ((copylabirint[j][i-1] != 35) && (copylabirint[j][i-1] != 42))
					copylabirint[j][i] += 1;					
			}
		}
	}
}

void part5(int** labirint, int** key_coo, int weight, int high){

	int i,j;

	for (i = 0; i < high; i++)
		for (j = 0; j < weight; j++)
			if (labirint[j][i] == 32)
				labirint[j][i] = 50000;

	labirint[key_coo[0][0]][key_coo[0][1]] = 50000;	
	labirint[key_coo[1][0]][key_coo[1][1]] = 50000;			
}

void part6_1(int** labirint, int** key_coo, int* x, int* y, int* count, int weight){ 
 
	while ((labirint[*x+1][*y] != '#') && (labirint[*x+1][*y] > *count+1)){  

		(*x)++;

		if (labirint[*x][*y] == '*'){
			*x = 1;

			if ((labirint[*x][*y] > *count+1) && (labirint[*x][*y] != '#'))
				labirint[*x][*y] = ++(*count);	
			else{
				*x = weight-2;
				break;
			}	
		}
		else labirint[*x][*y] = ++(*count);
	}
}

void part6_2(int** labirint, int** key_coo, int* x, int* y, int* count, int high){

	while ((labirint[*x][*y+1] != '#') && (labirint[*x][*y+1] > *count+1)){  

		(*y)++;

		if (labirint[*x][*y] == '*'){
			*y = 1;

			if ((labirint[*x][*y] > *count+1) && (labirint[*x][*y] != '#'))
				labirint[*x][*y] = ++(*count);	
			else{
				*y = high-2;
				break;
			}	
		}
		else labirint[*x][*y] = ++(*count);		
	}	
}

void part6_3(int** labirint, int** key_coo, int* x, int* y, int* count, int weight){

	while ((labirint[*x-1][*y] != '#') && (labirint[*x-1][*y] > *count+1)){  

		--(*x);

		if (labirint[*x][*y] == '*'){
			*x = weight-2;

			if ((labirint[*x][*y] > *count+1) && (labirint[*x][*y] != '#'))
				labirint[*x][*y] = ++(*count);	
			else{
				*x = 1;
				break;
			}	
		}	

		else labirint[*x][*y] = ++(*count);
	} 	
}

void part6_4(int** labirint, int** key_coo, int* x, int* y, int* count, int high){

	while ((labirint[*x][*y-1] != '#') && (labirint[*x][*y-1] > *count+1)){  

		(*y)--;

		if (labirint[*x][*y] == '*'){
			*y = high-2;

			if ((labirint[*x][*y] > *count+1) && (labirint[*x][*y] != '#'))
				labirint[*x][*y] = ++(*count);	
			else{
				*y = 1;
				break;
			}	
		}				

		else labirint[*x][*y] = ++(*count);
	}	
}

int part6_1_1(int** labirint, int** key_coo, int weight, int* count, int* x, int* y){

	int tx = *x;
	int ty = *y;

	part6_1(labirint,key_coo,x,y,count,weight);

	if ((tx == *x) && (ty == *y))
		return 1;
	else return 0;
}

int part6_2_1(int** labirint, int** key_coo, int high, int* count, int* x, int* y){

	int tx = *x;
	int ty = *y;

	part6_2(labirint,key_coo,x,y,count,high);
	
	if ((tx == *x) && (ty == *y))
		return 1;	
	else return 0;
}

int part6_3_1(int** labirint, int** key_coo, int weight, int* count, int* x, int* y){

	int tx = *x;
	int ty = *y;

	part6_3(labirint,key_coo,x,y,count,weight);

	if ((tx == *x) && (ty == *y))
		return 1;	
	else return 0;			
}

int part6_4_1(int** labirint, int** key_coo, int high, int weight, int* count, int* x, int* y){

	int tx = *x;
	int ty = *y;

	part6_4(labirint,key_coo,x,y,count,high);

	if ((tx == *x) && (ty == *y))
		return 1;	
	else return 0;	
}

void part6(int** labirint, int** copylabirint, int** key_coo, int weight, int high, int* count, int* x, int* y, int** standart_koo){

	int metka = 0; int pometka = 0;

	while (1)
	{
		pometka = 0;

		metka = part6_1_1(labirint, key_coo, weight, count, x, y);  
		if (metka == 1)
			pometka++;

		metka = part6_2_1(labirint, key_coo, high, count, x, y);
		if (metka == 1)
			pometka++;		

		metka = part6_3_1(labirint, key_coo, weight, count, x, y);;
		if (metka == 1)
			pometka++;			

		metka = part6_4_1(labirint, key_coo, high, weight, count, x, y);
		if (metka == 1)
			pometka++;	

		if (pometka == 4)
			break;	
	}
}

void part7(int** labirint, int** copylabirint, int* x, int* y, int weight, int high, int* count, int** standart_koo){

	int i; 

	for (i = 0; i < 4; i++)
	{
		if (labirint[*x + standart_koo[0][i]][*y + standart_koo[1][i]] == '*'){

			if ((i == 0) && (labirint[1][*y] == (*count)-1)){
				(*count)--;
				*x = 1;
				break;
			}
								
			if ((i == 1) && (labirint[*x][1] == (*count)-1)){
				(*count)--;
				*y = 1;
				break;
			}

			if ((i == 2) && (labirint[weight-2][*y] == (*count)-1)){
				(*count)--;
				*x = weight-2;
				break;
			}

			if ((i == 3) && (labirint[*x][high-2] == (*count)-1)){
				(*count)--;
				*y = high-2;
				break;
			}								
		}			
		else if (labirint[*x + standart_koo[0][i]][*y + standart_koo[1][i]] == (*count)-1){ 
				(*count)--;
				*x += standart_koo[0][i];
				*y += standart_koo[1][i]; 
				break;
		}
	}
}

void part8(int** labirint, int** copylabirint, int* x, int* y, int weight, int high, int* count, int** standart_koo, int** key_coo){

	int i; int tx = *x; int ty = *y;
	*count = labirint[*x][*y];  

	for (i = 0; i < 4; i++)
	{
		if ((labirint[*x + standart_koo[0][i]][*y + standart_koo[1][i]] != '#') && (labirint[*x + standart_koo[0][i]][*y + standart_koo[1][i]] > *count+1)){

			if (labirint[*x + standart_koo[0][i]][*y + standart_koo[1][i]] == '*')
			{
				if ((i == 0) && (labirint[1][*y] != '#') && (labirint[1][*y] > *count+1))
					*x = 1;	

				if ((i == 1) && (labirint[*x][1] != '#') && (labirint[*x][1] > *count+1))
					*y = 1; 

				if ((i == 2) && (labirint[weight-2][*y] != '#') && (labirint[weight-2][*y] > *count+1))
					*x = weight-2;

				if ((i == 3) && (labirint[*x][high-2] != '#') && (labirint[*x][high-2] > *count+1))
					*y = high-2;												
			}
			else {
				*x += standart_koo[0][i];
				*y += standart_koo[1][i];	
			}

			if ((tx == *x) && (ty == *y))
				continue;

			labirint[*x][*y] = ++(*count);

			part6(labirint, copylabirint, key_coo, weight, high, count, x, y, standart_koo);
			break;
		}
	}
}

void part9(int** labirint, int** copylabirint, int* x, int* y, int weight, int high, int* count, int** standart_koo, int** key_coo){

	*x = key_coo[1][0]; *y = key_coo[1][1];

	*count = labirint[*x][*y];
	int tx = *x; 
	int ty = *y;

	part7(labirint, copylabirint, x, y, weight, high, count, standart_koo);

	labirint[tx][ty] = 'B';

	while (labirint[*x][*y] != 1){
		tx = *x;
		ty = *y;

		part7(labirint, copylabirint, x, y, weight, high, count, standart_koo);
		labirint[tx][ty] = '*';
	}

	labirint[*x][*y] = 'A';

	int i,j;
	for (i = 0; i < weight; i++)
		for (j = 0; j < high; j++)
			if ((labirint[i][j] != '*') && (labirint[i][j] != '#') && (labirint[i][j] != 'A') && (labirint[i][j] != 'B'))
				labirint[i][j] = ' ';

	correct(labirint, weight, high);		
}

void part10(int** del_labirint, int weight, int high){

	int i,j;

	for (i = 0; i < weight; i++)
		for (j = 0; j < high; j++)
			free(del_labirint[j]);
}

void main(int argc, char* argv[])
{
	FILE* file; 
	file = fopen(argv[1], "rb");

	int i,j;

    int** key_coo = calloc(2,sizeof(int*));
	for (i = 0; i < 2; i++)
		key_coo[i] = calloc(2,sizeof(int));

    int high = 0;
    int weight = 0;

    part1(file, key_coo, &weight, &high);

	int** labirint = calloc(weight,sizeof(int*));

	for (i = 0; i < weight; i++)
		labirint[i] = calloc(high,sizeof(int));

	int count = 1;	

	part2(file,labirint,weight,high);

	int** copylabirint = calloc(weight,sizeof(int*));
	for (i = 0; i < weight; i++)
		copylabirint[i] = calloc(high,sizeof(int));

	part3(labirint, copylabirint, key_coo, weight, high);

	part4(copylabirint, key_coo, weight, high);

	part5(labirint, key_coo, weight,high);

	int** standart_koo = calloc(2,sizeof(int*));
		for (i = 0; i < 2; i++)
			standart_koo[i] = calloc(4,sizeof(int));

	standart_koo[0][0] = 1;           
	standart_koo[0][1] = 0;
	standart_koo[0][2] = -1;
	standart_koo[0][3] = 0;

	standart_koo[1][0] = 0; 
	standart_koo[1][1] = 1;
	standart_koo[1][2] = 0;
	standart_koo[1][3] = -1;

	labirint[key_coo[0][0]][key_coo[0][1]] = 1;
	int x = key_coo[0][0]; 
	int y = key_coo[0][1];

	part6(labirint, copylabirint, key_coo, weight, high, &count, &x, &y, standart_koo);

	do{	
		part7(labirint, copylabirint, &x, &y, weight, high, &count, standart_koo);

		while ((copylabirint[x][y] <= 2) && (labirint[x][y] != 1))
			part7(labirint, copylabirint, &x, &y, weight, high, &count, standart_koo);

		part8(labirint, copylabirint, &x, &y, weight, high, &count, standart_koo, key_coo);

	} while (labirint[x][y] != 1);

	if (labirint[key_coo[1][0]][key_coo[1][1]] == 50000)
		printf("No way");
	else
		part9(labirint, copylabirint, &x, &y, weight, high, &count, standart_koo, key_coo);

	part10(labirint,weight,high);
	part10(copylabirint,weight,high);
}