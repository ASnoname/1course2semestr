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

void part2(FILE* file, int** lamborghini, int weight, int high){

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

			lamborghini[i][j] = c;
		}
	}
}

void correct(int** lamborghini, int weight, int high){

	int i,j;

	for (i = 1; i < high-1; i++){
		for (j = 1; j < weight-1; j++){
			printf("%d", lamborghini[j][i]);
		}
		printf("\n");
	}	
}

void part3(int** lamborghini, int** copylabirint, int** key_coo, int weight, int high){

	int i,j;

	for (i = 0; i < high; i++){
		for (j = 0; j < weight; j++){

			if (lamborghini[j][i] == 32)
				copylabirint[j][i] = 0;
			else
				copylabirint[j][i] = lamborghini[j][i];
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

void part5(int** lamborghini, int** key_coo, int weight, int high){

	int i,j;

	for (i = 0; i < high; i++)
		for (j = 0; j < weight; j++)
			if (lamborghini[j][i] == 32)
				lamborghini[j][i] = 0;

	lamborghini[key_coo[0][0]][key_coo[0][1]] = 0;	
	lamborghini[key_coo[1][0]][key_coo[1][1]] = 0;			
}

void part6_1(int** lamborghini, int** key_coo, int* x, int* y, int* count, int* optimal_way){ // вправо

	lamborghini[*x][*y] = 1; 	
	(*x)++;

	while (lamborghini[*x][*y] != 35){  

		if (lamborghini[*x][*y] == 42)
			*x = 1;

		if (lamborghini[*x][*y] == 1)
			break;

		if ((*count > lamborghini[*x][*y]) && (lamborghini[*x][*y] != 0))
			break;

		lamborghini[*x][*y] = ++(*count);

		if (*optimal_way > 0)
			if(lamborghini[*x][*y] > *optimal_way)
				break;	

		if ((*x == key_coo[1][0]) && (*y == key_coo[1][1])) 
			return;

		++(*x);	
	}
}

void part6_2(int** lamborghini, int** key_coo, int* x, int* y, int* count, int* optimal_way){

	(*y)++;

	while (lamborghini[*x][*y] != 35){  

		if (lamborghini[*x][*y] == 42)
			*y = 1;

		if (lamborghini[*x][*y] == 1)
			break;

		if ((*count > lamborghini[*x][*y]) && (lamborghini[*x][*y] != 0))
			break;

		lamborghini[*x][*y] = ++(*count);

		if (*optimal_way > 0)
			if(lamborghini[*x][*y] > *optimal_way)
				break;	

		if ((*x == key_coo[1][0]) && (*y == key_coo[1][1])) 
			return;

		++(*y);	
	}	// вниз
}

void part6_3(int** lamborghini, int** key_coo, int* x, int* y, int* count, int* optimal_way, int weight){

	--(*x);

	while (lamborghini[*x][*y] != 35){  

		if (lamborghini[*x][*y] == 42)
			*x = weight-2;

		if (lamborghini[*x][*y] == 1)
			break;

		if ((*count > lamborghini[*x][*y]) && (lamborghini[*x][*y] != 0))
			break;

		lamborghini[*x][*y] = ++(*count);

		if (*optimal_way > 0)
			if(lamborghini[*x][*y] > *optimal_way)
				break;	

		if ((*x == key_coo[1][0]) && (*y == key_coo[1][1])) 
			return;

		--(*x);	
	} // влево
}

void part6_4(int** lamborghini, int** key_coo, int* x, int* y, int* count, int* optimal_way, int high){

	(*y)--;

	while (lamborghini[*x][*y] != 35){  

		if (lamborghini[*x][*y] == 42)
			*y = high-2;

		if (lamborghini[*x][*y] == 1)
			break;

		if ((*count > lamborghini[*x][*y]) && (lamborghini[*x][*y] != 0))
			break;

		lamborghini[*x][*y] = ++(*count);

		if (*optimal_way > 0)
			if(lamborghini[*x][*y] > *optimal_way)
				break;	

		if ((*x == key_coo[1][0]) && (*y == key_coo[1][1])) 
			return;

		--(*y);	
	}	 // вверх
}

void part6(int** lamborghini, int** copylabirint, int** key_coo, int weight, int high){

	int i,j;
	int x; int y;
	x = key_coo[0][0];
	y = key_coo[0][1];

	int optimal_way = lamborghini[key_coo[1][0]][key_coo[1][1]];
	int count = 1;

	part6_1(lamborghini,key_coo,&x,&y,&count,&optimal_way);

	if (lamborghini[x][y] == 35) 
		x--;
	else if (x == 1)
		x = weight-2;

	if ((x == key_coo[1][0]) && (y == key_coo[1][1]))
		return;

	part6_2(lamborghini,key_coo,&x,&y,&count,&optimal_way);

	if (lamborghini[x][y] == 35)
		y--;
	else if (y == 1)
		y = high-2;

	if ((x == key_coo[1][0]) && (y == key_coo[1][1]))
		return;

	part6_3(lamborghini,key_coo,&x,&y,&count,&optimal_way,weight);

	if (lamborghini[x][y] == 35)
		x++;
	else if (x == weight-2)
		x = 1;

	if ((x == key_coo[1][0]) && (y == key_coo[1][1]))
		return;	

	part6_4(lamborghini,key_coo,&x,&y,&count,&optimal_way,high);

	if (lamborghini[x][y] == 35)
		y = high-2;
	else if (x == weight-2)
		y++;

	if ((x == key_coo[1][0]) && (y == key_coo[1][1]))
		return;		

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

	int** lamborghini = calloc(weight,sizeof(int*));

	for (i = 0; i < weight; i++)
		lamborghini[i] = calloc(high,sizeof(int));

	part2(file,lamborghini,weight,high);

	int** copylabirint = calloc(weight,sizeof(int*));
	for (i = 0; i < weight; i++)
		copylabirint[i] = calloc(high,sizeof(int));

	part3(lamborghini, copylabirint, key_coo, weight, high);

	part4(copylabirint, key_coo, weight, high);

	part5(lamborghini, key_coo, weight,high);

	part6(lamborghini,copylabirint,key_coo,weight,high);

	

	correct(lamborghini, weight, high);



}