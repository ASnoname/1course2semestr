#include "D:\proga\library.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

struct real 
{
	graph_user address_graph;
	int form;
	int count_edges;
	int count_node;
};

struct real* Graph_data;
int count_graph = 0;

struct Graph
{
	int first_node;
	int second_node;
	int weight;
	int orient;
};

void create_new_graph(int form, int count_node, int count_edges, void* address){

	Graph_data = realloc(Graph_data,count_graph+1);

	Graph_data[count_graph].form = form;
	Graph_data[count_graph].count_node = count_node;
	Graph_data[count_graph].count_edges = count_edges;
	Graph_data[count_graph].address_graph = address; 

	count_graph++;
}

int reader_help_two(int c){

	if (c == 61)
		return 0;
	if (c == 60)
		return -1;
	if (c == 62)
		return 1;
}

int reader_help_one(FILE* file, int* orient, int* weight){

	int i = 0; int number = 0; int c;

	while(((c = fgetc(file)) >= '0') && (c <= '9')){
		if (i > 0)
			number *= pow(10,i);
		number += (c-48);
		i++;
	}

	if (c == 13)
		c = fgetc(file);

	if ((c == '<') || (c == '=') || (c == '>')){
		*orient = reader_help_two(c);
	}	

	if (c == ' ')
		*weight = reader_help_one(file,0,0);

	return number;
}

graph_user reader_graph_edges(FILE* file){

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

	struct Graph* Graph = calloc(count_edges,sizeof(struct Graph));
	create_new_graph(0, count_node, count_edges, Graph);

	int i; int t1,t2,tt; 

	for(i = 0; i < count_edges; i++){

		t1 = reader_help_one(file, &orient,0);
		t2 = reader_help_one(file, 0,&weight);

		if (weight == 0)
			weight += 1;

		Graph[i].first_node = t1;
		Graph[i].orient = orient;  
		Graph[i].second_node = t2;
		Graph[i].weight = weight;
	}

	fclose(file);

	return Graph;
}

graph_user reader_graph_matrix(FILE* file){
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

	int i; 

	int** Graph = (int**)calloc(count_node,sizeof(int*));

	for (i = 0; i < count_node; i++)
		Graph[i] = (int*)calloc(count_node,sizeof(int));

	create_new_graph(1, count_node, count_edges, Graph);

	for (i = 0; i < count_edges; i++)
	{
		int t1 = reader_help_one(file, &orient,&weight) - 1;
		int t2 = reader_help_one(file, &orient,&weight) - 1;

		if (orient == -1){

			if (weight == 0)
				Graph[t2][t1] = 1;
			else
				Graph[t2][t1] = weight;
		}	

		else if (orient == 1){

			if (weight == 0)
				Graph[t1][t2] = 1;
			else
				Graph[t1][t2] = weight;
		}	

		else if (orient == 0)
		{
			if (weight == 0)
			{
				Graph[t2][t1] = 1;
				Graph[t1][t2] = 1;
			}
			else {
				Graph[t2][t1] = weight;
				Graph[t1][t2] = weight;
			}	
		}
	}

	fclose(file);

	return Graph;
}

int security(graph_user temp_graf){

	int i;

	for(i = 0; i < count_graph; i++){
		if (Graph_data[i].address_graph == temp_graf){
			return i;
		}	
	}	

	return -1;
}

void free_graph(graph_user temp_graf){

	int i; 
	int key = security(temp_graf);

	if (key == -1){
		printf("ERROR");
	}

	if (key == count_graph-1)
	{		
		Graph_data[key].form = 0;
		Graph_data[key].count_node = 0;
		Graph_data[key].count_edges = 0;
		Graph_data[key].address_graph = NULL;
		if (count_graph != 1)
			Graph_data = realloc(Graph_data,count_graph-1);
	}

	else if (key != count_graph-1)
	{
		
		Graph_data[key].form = Graph_data[count_graph-1].form;
		Graph_data[key].count_node = Graph_data[count_graph-1].count_node;
		Graph_data[key].count_edges = Graph_data[count_graph-1].count_edges;
		Graph_data[key].address_graph = Graph_data[count_graph-1].address_graph;

		Graph_data = realloc(Graph_data,count_graph-1);
	}
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
		struct Graph* Graph = (struct Graph*)temp_graf;
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

	if (Graph_data[key].form == 1){

		int** Graph;
		Graph = Graph_data[key].address_graph;

		if ((Graph[first_node-1][second_node-1] == Graph[second_node-1][first_node-1]) && (Graph[second_node-1][first_node-1] != 0))
			return 0;
		else if (Graph[first_node-1][second_node-1] > 0)
			return 1;
		else if (Graph[second_node-1][first_node-1] > 0)
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

graph_user make_graph(int form, int size){
	if (form == 0) 
	{
		struct Graph* Graph = calloc(size,sizeof(struct Graph));

		create_new_graph(form, size, 0, Graph);

		return Graph;
	}

	if (form == 1)
	{
		graph_user Graph = calloc(size*size, sizeof(int));

		create_new_graph(form, size, 0, Graph);

		return Graph;
	}
}

void delete_graph(graph_user temp_graf){

	free_graph(temp_graf);
	free(temp_graf);
}

void add_edge_graph(graph_user temp_graf, int first_node, int second_node, int orient, int weight){

	int key = security(temp_graf);

	if (key == -1){
		printf("ERROR");
	}	

	if (Graph_data[key].form == 0)
	{
		struct Graph* Graph = Graph_data[key].address_graph;
		int count_node = ++Graph_data[key].count_node;

		Graph = realloc(Graph,count_node);

		Graph_data[key].address_graph = Graph;
		Graph_data[key].count_edges += 1;

		if (MAX(first_node,second_node) > Graph_data[key].count_node)
			Graph_data[key].count_node += 1;

		Graph[count_node].first_node = first_node;
		Graph[count_node].orient = orient;
		Graph[count_node].second_node = second_node;
		Graph[count_node].weight = weight;
	}

	if(Graph_data[key].form == 1){

		Graph_data[key].count_edges += 1;

		int** Graph = Graph_data[key].address_graph;
		int count_node = Graph_data[key].count_node;

		if (MAX(first_node,second_node) > Graph_data[key].count_node)
		{
			Graph_data[key].count_node += 1;		
			count_node += 1;	
			Graph = realloc(Graph_data[key].address_graph, count_node*count_node);
			Graph_data[key].address_graph = Graph;

		}

		if (orient == -1){

			if (weight == 0)
				Graph[second_node-1][first_node-1] = 1;
			else Graph[second_node-1][first_node-1] = weight;
		}	

		if (orient == 1){

			if (weight == 0)
				Graph[first_node-1][second_node-1] = 1;
			else Graph[first_node-1][second_node-1] = weight;
		}	

		if (orient == 0)
		{
			if (weight == 0)
			{
				Graph[second_node-1][first_node-1] = 1;
				Graph[first_node-1][second_node-1] = 1;
			}
			else {
				Graph[second_node-1][first_node-1] = weight;
				Graph[first_node-1][second_node-1] = weight;
			}	
		}
	}
}

void delete_edge(graph_user temp_graf, int first_node, int second_node){

	int key = security(temp_graf);

	if (key == -1){
		printf("ERROR");
	}

	if (Graph_data[key].form == 0){

		struct Graph* Graph = Graph_data[key].address_graph;
		int count_node = Graph_data[key].count_node;
		int count_edges = Graph_data[key].count_edges;

		int i;
		for (i = 0; i < count_edges; i++)
			if ((first_node == Graph[i].first_node) && (second_node == Graph[i].second_node))
				break;

		if (i == count_edges)
			printf("ERROR");

		if (i == count_edges-1)
		{
			Graph = realloc(Graph,count_edges-1);
		}

		else if (i != count_edges-1){
			Graph[i].first_node = Graph[count_edges-1].first_node;
			Graph[i].second_node = Graph[count_edges-1].second_node;
			Graph[i].orient = Graph[count_edges-1].orient;
			Graph[i].weight = Graph[count_edges-1].weight;

			Graph = realloc(Graph,count_edges-1);
		}

		Graph_data[key].count_edges -= 1;

		int test_one = 0;
		int test_two = 0;

		for (i = 0; i < count_edges -1; i++)
		{
			if ((Graph[i].first_node != first_node) && (Graph[i].second_node != first_node))
				test_one++;

			if((Graph[i].first_node != second_node) && (Graph[i].second_node != second_node))	
				test_two++;
		}

		if (test_one != count_edges-1)
			Graph_data[key].count_node -= 1;

		if (test_two != count_edges-1)
			Graph_data[key].count_node -= 1;
	}

	if (Graph_data[key].form == 1){

		int** Graph = Graph_data[key].address_graph;
		int count_node = Graph_data[key].count_node;
		int count_edges = --Graph_data[key].count_edges;

		int i;
		int test_one = 0;
		int test_two = 0;

		if ((Graph[first_node-1][second_node-1] != 0) && (Graph[second_node-1][first_node-1] != 0))
		{
			Graph[first_node-1][second_node-1] = 0;
			Graph[second_node-1][first_node-1] = 0;	
		}

		if ((Graph[first_node-1][second_node-1] != 0) && (Graph[second_node-1][first_node-1] == 0))
			Graph[first_node-1][second_node-1] = 0;

		if ((Graph[second_node-1][first_node-1] != 0) && (Graph[first_node-1][second_node-1] == 0))
			Graph[second_node-1][first_node-1] = 0;


		for (i = 0; i < count_node; i++)
			if (Graph[first_node-1][i] == 0)
				test_one++;	

		for (i = 0; i < count_node; i++)
			if (Graph[i][second_node-1] == 0)
				test_two++;			

		if ((test_one == count_node) && (first_node == count_node)){

			Graph = realloc(Graph,(count_node-1)*(count_node-1));
			Graph_data[key].count_node -= 1;	
			Graph_data[key].address_graph = Graph;	
		}

		if ((test_two == count_node) && (second_node == count_node)){

			Graph = realloc(Graph,(count_node-1)*(count_node-1));
			Graph_data[key].count_node -= 1;	
			Graph_data[key].address_graph = Graph;	
		}
	}
}

int character(graph_user temp_graf, char string[], int first_node, int second_node){

	int key = security(temp_graf);

	if (key == -1){
		printf("ERROR");
		return -5;
	}

	if (Graph_data[key].form == 0)
	{
		struct Graph* Graph = Graph_data[key].address_graph;

		int i;

		for (i = 0; i < Graph_data[key].count_edges; i++)
		{
			if ((first_node == Graph[i].first_node) && (second_node == Graph[i].second_node) && (Graph[i].orient != 0))
			{
				if (strcmp(string,"weight") == 0)
				{
					return Graph[i].weight;
				}

				else  if (strcmp(string,"orient") == 0)
				{
					return Graph[i].orient;
				}

				else return -4;
			}

			if ((first_node == Graph[i].first_node || first_node == Graph[i].second_node) && (second_node == Graph[i].second_node || second_node == Graph[i].first_node) && (Graph[i].orient == 0)){
				if (strcmp(string,"weight") == 0)
				{
					return Graph[i].weight;
				}

				else  if (strcmp(string,"orient") == 0)
				{
					return Graph[i].orient;
				}

				else return -4;
			}
		}
	}

	if (Graph_data[key].form == 1)
	{
		
		int** Graph = Graph_data[key].address_graph;

		if (strcmp(string,"weight") == 0)
		{
			return Graph[first_node-1][second_node-1];
		}

		else if (strcmp(string,"orient") == 0)
		{
			if ((Graph[first_node-1][second_node-1] == 0) && (Graph[second_node-1][first_node-1] != 0))
			{
				return -1;
			}

			if ((Graph[second_node-1][first_node-1] == 0) && (Graph[first_node-1][second_node-1] != 0))
			{
				return 1;
			}

			if ((Graph[second_node-1][first_node-1] != 0) && (Graph[first_node-1][second_node-1] != 0))
			{
				return 0;
			}
		}

		else return -4;
	}
}

graph_user copy_graph(graph_user temp_graf){

	int key = security(temp_graf);

	if (key == -1){
		printf("ERROR");
	}

	if (Graph_data[key].form == 0)
	{
		struct Graph* Graph = calloc(Graph_data[key].count_edges, sizeof(struct Graph));
		create_new_graph(Graph_data[key].form, Graph_data[key].count_node, Graph_data[key].count_edges, Graph);

		struct Graph* Graph_old = Graph_data[key].address_graph;

		int i;
		for (i = 0; i < Graph_data[key].count_edges; i++)
		{
			Graph[i].first_node = Graph_old[i].first_node;
			Graph[i].second_node = Graph_old[i].second_node;
			Graph[i].orient = Graph_old[i].orient;
			Graph[i].weight = Graph_old[i].weight; 
		}

		return Graph;
	}

	if (Graph_data[key].form == 1){

		int** Graph = (int**)calloc(Graph_data[key].count_node,sizeof(int*));

		int i,j;
		for (i = 0; i < Graph_data[key].count_node; i++)
			Graph[i] = (int*)calloc(Graph_data[key].count_node,sizeof(int));


		create_new_graph(Graph_data[key].form, Graph_data[key].count_node, Graph_data[key].count_edges, Graph);

		int** Graph_old = Graph_data[key].address_graph;

		for (i = 0; i < Graph_data[key].count_node; i++)
		{
			for (j = 0; j < Graph_data[key].count_node; j++){
				Graph[i][j] = Graph_old[i][j];
			}
		}

		return Graph;
	}
}

char help_one_load_graph_in_file(int orient){

	if (orient == -1)
		return '<';
	if (orient == 0)
		return '=';
	if (orient == 1)
		return '>';
}

void load_graph_in_file(char* file, graph_user temp_graf){

	int key = security(temp_graf);

	if (key == -1){
		printf("ERROR");
		return;
	}

	FILE* output = fopen(file,"w");

	if (Graph_data[key].form == 0)
	{

		struct Graph* Graph = Graph_data[key].address_graph;
		fprintf(output, "%d\n", Graph_data[key].count_node);
		int i;
		for (i = 0; i < Graph_data[key].count_edges; i++)
			fprintf(output, "%d%c%d %d\n", Graph[i].first_node, help_one_load_graph_in_file(Graph[i].orient), Graph[i].second_node, Graph[i].weight);
	}

	if (Graph_data[key].form == 1)
	{
		
		int** Graph = copy_graph(Graph_data[key].address_graph);

		key = security(Graph);
		fprintf(output, "%d\n", Graph_data[key].count_node);

		int i,j;
		for (i = 0; i < Graph_data[key].count_node; i++)
		{
			for (j = 0; j < Graph_data[key].count_node; j++){

				if (i == j)
					continue;
				if ((Graph[i][j] == -7) && (Graph[j][i] == -7))
					continue;

				if ((Graph[i][j] == Graph[j][i]) && (Graph[i][j] != 0))
				{
					fprintf(output, "%d%c%d %d\n", i+1, '=', j+1, Graph[i][j]);
					Graph[i][j] = -7;
					Graph[j][i] = -7;
				}

				if ((Graph[i][j] > 0) && (Graph[j][i] == 0))
				{
					fprintf(output, "%d%c%d %d\n", i+1, '>', j+1, Graph[i][j]);
					Graph[i][j] = -7;
					Graph[j][i] = -7;					
				}
			}
		}
		delete_graph(Graph);
	}
}