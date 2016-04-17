#include "D:\proga\library.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// написать в каждой функции проверку на существование адреса

int count_graph = 0;

typedef struct real_graph
{
	graph_user address_graph;
	int weighting;
	int orientation;
	int form;
	int count_edges;
	int count_node;
	int type;
}real_graph;

real_graph* Graph_data;

struct Graph_w_o
{
	int first_node;
	int second_node;
	int weight;
	int orient;
};

struct Graph_n_o
{
	int first_node;
	int second_node;
	int orient;
};

struct Graph_w_n
{
	int first_node;
	int second_node;
	int weight;
};

struct Graph_n_n
{
	int first_node;
	int second_node;
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

graph_user func_reader_edges(FILE* file){

	int weight = 0, orient = 0, count_node = reader_help_one(file,0,0);
	int c, count_edges = 0;

	int place = ftell(file);
	fseek(file,0,SEEK_SET);

	while(1){
		c = fgetc(file);
		if(c == 13){
			count_edges++;
		}
		if (c == EOF) break;
	}

	fseek(file,place,SEEK_SET);

	struct Graph_w_o* Graph = calloc(count_edges,sizeof(struct Graph_w_o));

	int i; int t1,t2,tt; 
	int counter_weight = 0; 
	int counter_orient = 0;

	Graph_data[count_graph].form = 0;
	Graph_data[count_graph].count_edges = count_edges;
	Graph_data[count_graph].count_node = count_node;
	Graph_data[count_graph].type = 111;

	for(i=0; i < count_edges; i++){

		if ((t1 = reader_help_one(file, &orient,&weight)) > (t2 = reader_help_one(file, &orient,&weight)))
		{
			tt = t2;
			t2 = t1;
			t1 = tt;

			if (orient != 0)
				orient *= -1;
		}

		Graph[i].first_node = t1;
		Graph[i].orient = orient;
		Graph[i].second_node = t2;
		Graph[i].weight = weight;

		if (Graph[i].orient != 0)
			counter_orient = 1;
		if (Graph[i].weight != 0)
			counter_weight = 1;		
	}

	fclose(file);

	if ((counter_orient == 0) && (counter_weight == 1))
	{
		struct Graph_w_n* Graph_new = calloc(count_edges,sizeof(struct Graph_w_n));

		for (i = 0; i < count_edges; i++)
		{
			Graph_new[i].first_node = Graph[i].first_node;
			Graph_new[i].second_node = Graph[i].second_node;
			Graph_new[i].weight = Graph[i].weight;
		}

		Graph_data[count_graph].weighting = 1;
		Graph_data[count_graph].orientation = 0;
		Graph_data[count_graph].address_graph = Graph_new;
		Graph_data[count_graph].type = 110;
	}

	if ((counter_orient == 0) && (counter_weight == 0))
	{
		struct Graph_n_n* Graph_new = calloc(count_edges,sizeof(struct Graph_n_n));

		for (i = 0; i < count_edges; i++)
		{
			Graph_new[i].first_node = Graph[i].first_node;
			Graph_new[i].second_node = Graph[i].second_node;
		}

		Graph_data[count_graph].weighting = 0;
		Graph_data[count_graph].orientation = 0;
		Graph_data[count_graph].address_graph = Graph_new;
		Graph_data[count_graph].type = 100;
	}

	if ((counter_orient == 1) && (counter_weight == 0))
	{
		struct Graph_n_o* Graph_new = calloc(count_edges,sizeof(struct Graph_n_o));

		for (i = 0; i < count_edges; i++)
		{
			Graph_new[i].first_node = Graph[i].first_node;
			Graph_new[i].second_node = Graph[i].second_node;
			Graph_new[i].orient = Graph[i].orient;
		}

		Graph_data[count_graph].weighting = 0;
		Graph_data[count_graph].orientation = 1;
		Graph_data[count_graph].address_graph = Graph_new;
		Graph_data[count_graph].type = 101;
	}

	count_graph++;

	//delete_graph(Graph);

	return Graph_new;
}

graph_user func_reader_matrix(FILE* file){
	int weight = 0, orient = 0, count_node = reader_help_one(file,0,0);
	int c, count_edges = 0;

	int place = ftell(file);
	fseek(file,0,SEEK_SET);

	while(1){
		c = fgetc(file);
		if(c == 13){
			count_edges++;
		}
		if (c == EOF) break;
	}

	fseek(file,place,SEEK_SET);

	int i; int t1,t2,tt;

	realloc(Graph_data,count_graph);
	int** Graph = calloc(count_node*count_node, sizeof(int))

	int counter_weight = 0; 
	int counter_orient = 0;

	Graph_data[count_graph].form = 1;
	Graph_data[count_graph].count_edges = count_edges;
	Graph_data[count_graph].count_node = count_node;

	for (i = 0; i < count_edges; i++)
	{
		t1 = reader_help_one(file, &orient,&weight);
		t2 = reader_help_one(file, &orient,&weight);

		if (orient == -1){

			if (&weight == NULL)
				Graph[t2][t1] = 1;
			else{
				Graph[t2][t1] = weight;
				counter_weight = 1;
			}

			counter_orient = 1;	
		}	

		if (orient == 1){

			if (&weight == NULL)
				Graph[t1][t2] = 1;
			else{
				Graph[t1][t2] = weight;
				counter_weight = 1;
			}	
			
			counter_orient = 1;	
		}	

		if (orient == 0)
		{
			if (&weight == NULL)
			{
				Graph[t2][t1] = 1;
				Graph[t1][t2] = 1;
			}
			else {
				Graph[t2][t1] = weight;
				Graph[t1][t2] = weight;

				counter_weight = 1;
			}	
		}
	}

	if ((counter_orient == 1) && (counter_weight == 0)){

		Graph_data[count_graph].weighting = 0;
		Graph_data[count_graph].orientation = 1;
		Graph_data[count_graph].type = 101;
	}

	if ((counter_orient == 0) && (counter_weight == 0)){

		Graph_data[count_graph].weighting = 0;
		Graph_data[count_graph].orientation = 0;
		Graph_data[count_graph].type = 100;
	}

	if ((counter_orient == 0) && (counter_weight == 1)){

		Graph_data[count_graph].weighting = 1;
		Graph_data[count_graph].orientation = 0;
		Graph_data[count_graph].type = 110;
	}

	Graph_data[count_graph].address_graph = Graph;

	count_graph++;

	return Graph;
}

int security(graph_user temp_graf){

	int i;

	for (i = 0; i < count_graph; i++)
	{
		if (Graph_data[i].address_graph == temp_graf)
			return i;
	}

	return -1;
}

int existence(graph_user temp_graf, int first_node, int second_node){

	int i; 
	int key = security(temp_graf);

	if (key == -1){
		printf("ERROR");
		return -5;
	}

	if (Graph_data[key].form == 0)
	{

		if (Graph_data[key].type = 100)
		{
			struct Graph_n_n* Graph = (struct Graph_n_n*)temp_graf;
		}

		if (Graph_data[key].type = 101)
		{
			struct Graph_n_o* Graph = (struct Graph_n_o*)temp_graf;
		}

		if (Graph_data[key].type = 111)
		{
			struct Graph_w_o* Graph = (struct Graph_w_o*)temp_graf;
		}

		if (Graph_data[key].type = 110)
		{
			struct Graph_w_n* Graph = (struct Graph_n_o*)temp_graf;
		}

		for (i = 0; i < Graph_data[key].count_edges; i++)
		{
			if ((Graph[i].orient == 0) && (Graph[i].first_node == first_node) && (Graph[i].second_node == second_node))
				return 0;			
			if ((Graph[i].orient == 0) && (Graph[i].first_node == second_node) && (Graph[i].second_node == first_node))
				return 0;
			if ((Graph[i].orient == 1) && (Graph[i].first_node == first_node) && (Graph[i].second_node == second_node))
				return 1;			
			if ((Graph[i].orient == -1) && (Graph[i].first_node == first_node) && (Graph[i].second_node == second_node))
				return -1;			
		}
		return -3;
	}

	int** Graph;

	if (Graph_data[key].form == 1){
		Graph = Graph_data[key].address_graph;

		if ((Graph[first_node][second_node] > 0) && (Graph[second_node][first_node] > 0))
			return 0;
		else if (Graph[first_node][second_node] > 0)
			return 1;
		else if (Graph[second_node][first_node] > 0)
			return -1;
		else return -3;
	}

}

int func_count_edges(graph_user temp_graf){

	int key = security(temp_graf);

	if (key == -1){
		printf("ERROR");
		return -5;
	}

	return Graph_data[key].count_edges;
}

int func_count_node(graph_user temp_graf){

	int key = security(temp_graf);

	if (key == -1){
		printf("ERROR");
		return -5;
	}

	return Graph_data[key].count_node;
}

// graph_user make_graph(int form, int weighting, int size){
// 	if ( (form == 0) && (weighting == 0) )
// 	{
// 		struct Graph_no_weighting* Graph = calloc(size,sizeof(struct Graph_no_weighting));
// 		return Graph;
// 	}
// 	if ((form == 0) && (weighting == 1))
// 	{
// 		struct Graph_weighting* Graph = calloc(size,sizeof(struct Graph_weighting));
// 		return Graph;
// 	}
// 	if (form == 1)
// 	{
// 		graph_user Graph = calloc(size*size, sizeof(int));
// 		return Graph;
// 	}
// }

// void delete_graph(graph_user temp_graf, int form, int weighting){

// 	int N,i;

// 	if (form == 0)
// 	{

// 		if (weighting == 0)
// 		{
// 			struct Graph_no_weighting* Graph = (struct Graph_no_weighting*)temp_graf;
// 			N = func_count_edges(temp_graf);
// 			for (i = 0; i < N; i++)
// 			{
// 				Graph[i].count_edges = 0;
// 				Graph[i].first_node = 0;
// 				Graph[i].orient = 0;
// 				Graph[i].second_node = 0;
// 				Graph[i].count_node = 0;
// 			}
// 			free(temp_graf);
// 		}

// 		if (weighting == 1)
// 		{
// 			struct Graph_weighting* Graph = (struct Graph_weighting*)temp_graf;
// 			N = func_count_edges(temp_graf);
// 			for (i = 0; i < N; i++)
// 			{
// 				Graph[i].count_edges = 0;
// 				Graph[i].first_node = 0;
// 				Graph[i].orient = 0;
// 				Graph[i].second_node = 0;
// 				Graph[i].count_node = 0;
// 				Graph[i].weight = 0;
// 			}
// 			free(temp_graf);
// 		}

// 	}

// 	// if (form == 1)
// 	// {
		
// 	// }
// }

// int max(int a, int b){
// 	if (a > b)
// 		return a;
// 	else return b;
// }

// graph_user add_edge_graph(graph_user temp_graf, int form, int weighting, int first_node, int second_node, int orient, int weight, int size){
// 	if (form == 0)
// 	{
// 		if (weighting == 0)
// 			struct Graph_no_weighting* Graph = (struct Graph_no_weighting*)temp_graf;
		
// 		if (weighting == 1)
// 			struct Graph_weighting* Graph = (struct Graph_weighting*)temp_graf;	

// 		int count_node = func_count_edges(Graph);
// 		realloc(Graph,count_node+1);

// 		Graph[0].count_edges = count_node+1;
// 		Graph[count_node].first_node = first_node;
// 		Graph[count_node].orient = orient;
// 		Graph[count_node].second_node = second_node;
// 		Graph[0].count_node = count_node+1;

// 		if (weighting == 1)
// 			Graph[count_node].weight = weight;
// 	}

// 	if(form == 1){
// 		int** Graph = (int**)temp_graf;
// 		int N = func_count_node(Graph);

 
// 		if (N < max(first_node,second_node))
// 		{
// 			size++;
// 			realloc(Graph,size*size);
// 		}

// 		if (orient == -1){

// 			if (&weight == NULL)
// 				Graph[second_node][first_node] = 1;
// 			else Graph[second_node][first_node] = weight;
// 		}	

// 		if (orient == 1){

// 			if (&weight == NULL)
// 				Graph[first_node][second_node] = 1;
// 			else Graph[first_node][second_node] = weight;
// 		}	

// 		if (orient == 0)
// 		{
// 			if (&weight == NULL)
// 			{
// 				Graph[second_node][first_node] = 1;
// 				Graph[first_node][second_node] = 1;
// 			}
// 			else {
// 				Graph[second_node][first_node] = weight;
// 				Graph[first_node][second_node] = weight;
// 			}	
// 		}
// 	}
// }

// int func_edit_count_node(graph_user temp_graf, int form, int weighting){
// 	if(form == 0){
// 		if (weighting == 0)
// 		{
// 			struct Graph_no_weighting* Graph = (struct Graph_no_weighting*)temp_graf;
// 		}
// 		if (weighting == 1)
// 		{
// 			struct Graph_weighting* Graph = (struct Graph_weighting*)temp_graf;
// 		}	
// 			int i;
// 			int count_node = func_count_node(Graph);
// 			int count_edges = func_count_edges(Graph);

// 			int control[count_node + 1];

// 			for (i = 0; i < count_node; i++)
// 				control[i] = -1;

// 			for (i = 0; i < count_edges; i++)
// 			{
// 				if ((Graph[i].first_node == i+1) && (control[i] == -1))
// 					control[i] = 1;
// 				if ((Graph[i].second_node == i+1) && (control[i] == -1))
// 					control[i] = 1;
// 			}

// 			for (i = 0; i < count_node; i++)
// 			{
// 				if (control[i] != 1)
// 					return count_node - 1;
// 			}
// 			return count_node;
// 	}

// 	// if (form == 1)
// 	// {
		
// 	// }
// }

// graph_user delete_edge_graph(graph_user temp_graf, int form, int weighting, int first_node, int second_node){
// 	if (form == 0)
// 	{
// 		if (weighting == 0)
// 			struct Graph_no_weighting* Graph = (struct Graph_no_weighting*)temp_graf;
// 		if (weighting == 1)
// 			struct Graph_weighting* Graph = (struct Graph_weighting*)temp_graf;

// 		int count_edges = func_count_edges(Graph);

// 		if(first_node > second_node){
// 			int temp = second_node;
// 			second_node = first_node;
// 			first_node = temp;
// 		}

// 		int i;
// 		for (i = 0; i < count_edges; i++)
// 		{
// 			if ( (Graph[i].first_node == first_node) && (Graph[i].second_node == second_node) )
// 			{
// 				Graph[i].first_node = 0;
// 				Graph[i].second_node = 0;
// 				Graph[i].orient = 0;
// 				Graph[i].count_edges = 0;
// 				Graph[i].count_node = 0;

// 				if (weighting == 1)
// 					Graph[i].weight = 0;
// 				break;
// 			}				
// 		}

// 		if (i == count_edges - 1)
// 			Graph[0].count_edges--;
		

// 		Graph[i].first_node = Graph[count_edges - 1].first_node;
// 		Graph[i].second_node = Graph[count_edges - 1].second_node;
// 		Graph[i].orient = Graph[count_edges - 1].orient;
// 		Graph[i].count_edges = Graph[count_edges - 1].count_edges;
// 		Graph[i].count_node = Graph[count_edges - 1].count_node;

// 		if (weighting == 1)
// 			Graph[i].weight = Graph[count_edges - 1].weight;

// 		Graph[0].count_edges = count_edges - 1;	

// 		Graph[0].count_node = func_edit_count_node(Graph,form,weighting);
// 	}

// 	// if (form == 1)
// 	// {
		
// 	// }
// }	