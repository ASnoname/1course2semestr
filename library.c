#include "D:\proga\library.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Graph
{
	int count;
	int first_node;
	int second_node;
	int VES;
	int znak;
	int N;
};

int reader_help_two(int c){

	if (c == 61)
		return 0;
	if (c == 60)
		return -1;
	if (c == 62)
		return 1;
}

int reader_help_one(FILE* file, int* count, int* weight){

	int i = 0; int number = 0; int c;

	while(((c = fgetc(file)) >= '0') && (c <= '9')){
		number += (c-48)*pow(10,i);
		i++;
	}

	if (c == 13)
		c = fgetc(file);

	if ((c == '<') || (c == '=') || (c == '>')){
		*count = reader_help_two(c);
	}	

	if (c == ' ')
		*weight = reader_help_one(file,0,0);

	return number;
}

graph_user reader(FILE* file){

	int weight = 0,count = 0, N = reader_help_one(file,0,0);
	int c, enter = 0;

	int place = ftell(file);
	fseek(file,0,SEEK_SET);

	while(1){
		c = fgetc(file);
		if(c == 13){
			enter++;
		}
		if (c == EOF) break;
	}

	fseek(file,place,SEEK_SET);

	struct Graph* table = calloc(enter,sizeof(struct Graph));

	int i; int t1,t2,tt; int temp = enter;

	for(i=0; i < enter; i++){

		if ((t1 = reader_help_one(file, &count,&weight)) >  (t2 = reader_help_one(file, &count,&weight)))
		{
			tt = t2;
			t2 = t1;
			t1 = tt;

			if (count != 2)
				count *= -1;
		}

		table[i].first_node = t1;
		table[i].znak = count;
		table[i].second_node = t2;
		table[i].VES = weight;
		table[i].count = temp;
		table[i].N = N;
	}

	fclose(file);

	return table;
}

int existence(graph_user temp_graf, int a, int b){

int i; 
struct Graph* table=(struct Graph*)temp_graf;

	for (i = 0; i < table[0].count; i++)
	{
		if ((table[i].znak == 0) && (table[i].first_node == a) && (table[i].second_node == b))
			return 0;			
		if ((table[i].znak == 0) && (table[i].first_node == b) && (table[i].second_node == a))
			return 0;
		if ((table[i].znak == 1) && (table[i].first_node == a) && (table[i].second_node == b))
			return 1;			
		if ((table[i].znak == -1) && (table[i].first_node == a) && (table[i].second_node == b))
			return -1;			
	}
	return -3;
}

int count_edges(graph_user temp_graf){
	struct Graph* table = (struct Graph*)temp_graf;
	return table[0].count;
}

int count_node(graph_user temp_graf){
	struct Graph* table = (struct Graph*)temp_graf;
	return table[0].N;
}