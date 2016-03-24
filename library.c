#include "D:\proga\library.h"
#include <stdio.h>
#include <math.h>

int reader_help_two(FILE* file, int c){

	if (c == 61)
		return 2;
	if (c == 60)
		return -1;
	if (c == 62)
		return 1;

}

int reader_help_one(FILE* file, int* count, int* weight){

	int i = 0; int number = 0; int c;

	while(((c = fgetc(file)) > 47) && (c < 60)){
		number += (c-48)*pow(10,i);
		i++;
	}

	if ((c == 60) || (c == 61) || (c == 62)){
		*count = reader_help_two(file,c);
	}	
	if (c == 32)
		*weight = reader_help_one(file,0,0);
	
	return number;
}


void* reader(FILE* file){

	int weight = 0,count = 0, N = reader_help_one(file,0,0);
	
	int table[N][N];
	int first_node;
	int second_node;

	while(1){

		fgetc(file);
		first_node = reader_help_one(file, &count,0);
		if (first_node == 0) break;
		second_node = reader_help_one(file,0,&weight);

		if (first_node > second_node){
			table[second_node-1][first_node-1] = count;
			table[first_node-1][second_node-1] = weight;
		}	
		else{
			table[first_node-1][second_node-1] = count;	
			table[second_node-1][first_node-1] = weight;
		}	

	}

}