#include <stdio.h>
#include <stdlib.h>

int part1(char** lamborghini, int high, int weight, int x, int y, int count){

	if (lamborghini[x-1][y] == '*'){ 
		if (lamborghini[weight-2][y] == ' ')
			lamborghini[weight-2][y] = '0' + count;
		else if (lamborghini[weight-2][y] == 'B')
			return 1;
	}	
	else if (lamborghini[x-1][y] == ' ')
		lamborghini[x-1][y] = '0' + count;	
	else if (lamborghini[x-1][y] == 'B')
		return 1;	

	if (lamborghini[x+1][y] == '*'){
		if (lamborghini[1][y] == ' ')
			lamborghini[1][y] = '0' + count;
		else if (lamborghini[1][y] == 'B')
			return 1;		
	}	
	else if (lamborghini[x+1][y] == ' ')
		lamborghini[x+1][y] = '0' + count;	
	else if (lamborghini[x+1][y] == 'B')
		return 1;	

	if (lamborghini[x][y-1] == '*'){
		if (lamborghini[x][high-2] == ' ')
			lamborghini[x][high-2] = '0' + count;
		else if (lamborghini[x][high-2] == 'B')
			return 1;		
	}	
	else if (lamborghini[x][y-1] == ' ')
		lamborghini[x][high-2] = '0' + count;	
	else if (lamborghini[x][y-1] == 'B')
		return 1;	

	if (lamborghini[x][y+1] == '*'){
		if (lamborghini[x][1] == ' ')
			lamborghini[x][1] = '0' + count;
		else if (lamborghini[x][1] == 'B')
			return 1;		
	}	
	else if (lamborghini[x][y+1] == ' ')
		lamborghini[x][1] = '0' + count;
	else if (lamborghini[x][y+1] == 'B')
		return 1;	

	return 0;
}

int part2(char** lamborghini, int high, int weight, int x, int y){

	int i,j;
	int count = 1;    int p,q;

	int result = part1(lamborghini,high,weight,x,y,count);

	if (result == 0){

		for (j = 1; j < high-1; j++)
		{
			for (i = 1; i < weight-1; i++){

				if (lamborghini[i][j] == '0' + count)
				{
					x = i;
					y = j;  
					count++;
					if (part1(lamborghini,high,weight,x,y,count) == 1)
						return 1;

					i = 1; j = 1;
				}
			}
		}

		return 0;
	}	
	else return 1;
}

void main(int argc, char* argv[])
{
	FILE* file; 
	file = fopen(argv[1], "rb");

    int high = 0;
    int weight = 0;
    char c;
    int key_coo[2][2];
    int temp = 0;

	while(1){
		c = fgetc(file);			

		if(c == 13){

			weight = temp + 1;
			high++;
			c = fgetc(file);
			temp = -1;
		}
		else temp++;

		if (c == 'A'){
			key_coo[0][0] = temp; 
			key_coo[0][1] = high; 	
		}	
		if (c == 'B'){
			key_coo[1][0] = temp; 
			key_coo[1][1] = high; 	
		}

		if (c == EOF) break;
	}

	int i,j;
	char** lamborghini = calloc(weight,sizeof(char*));

	for (i = 0; i < weight; i++)
		lamborghini[i] = calloc(high,sizeof(char));

	fseek(file,0,SEEK_SET);

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

	int x = key_coo[0][0];
	int y = key_coo[0][1];	

	int verification = part2(lamborghini,high,weight,x,y);

	// printf("%d\n", verification);


}