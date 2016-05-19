#include "D:\proga\library.h"
#include <stdio.h>

int maxflow(graph_user graphik, int first_node, int second_node){

	graph_user graph = copy_graph(graphik);
	int count_node = func_count_node(graph);
	int metka = 1; 
	int i,k;
	int line[count_node];
	int yes[count_node]; int p = 0;

	while (metka != 0){
	
		for (i = 0; i < count_node; i++)
			line[i] = -1;

		for (i = 0; i < count_node; i++)
			yes[i] = 0;

		yes[first_node-1] = 1; line[0] = first_node; int var_temp = 0;

		i = first_node; int h;
		int lmetka = 0; int counter = 0;

		do{ 
			h = 0;
			for (k = 1; k <= count_node; k++)
			{  
				if ((existence(graph,i,k) == 1) && (yes[k-1] == 0) && (character(graph, "weight", i, k) > 0)){
					yes[k-1] = 1;

					line[++var_temp] = k;		

					i = k;
					h = 1; 
					counter = 0;
					break;
				}
			}

			if (!h){

				if ((var_temp == 0) && (line[1] == -1)){
					metka = 0;
					break;
				}

				if (counter == 1){
					metka = 0;
					break;
				}

				i = line[--var_temp];

				if (i == first_node)
					counter++;
			}	

		} while (i != second_node); 

		if (metka == 0)
			break;

		for (i = 1; i < count_node; i++)
			if (line[i] != -1)
				lmetka++;

		i = 0; int min = 1024;
		while (i < lmetka){

			int l = character(graph, "weight", line[i], line[i+1]);

			if (l < min)
				min = l;

			i++;
		}

		i = 0;
		while (i < lmetka){

			int l = character(graph, "weight", line[i], line[i+1]);

			delete_edge(graph, line[i], line[i+1]);  

			if (l > min)
				add_edge_graph(graph, line[i], line[i+1], 1, l - min);

			if (existence(graph,line[i+1], line[i]) == 1){

				int m = character(graph, "weight", line[i+1], line[i]);

				delete_edge(graph, line[i+1], line[i]);  
				add_edge_graph(graph, line[i+1], line[i], 1, m+min);
			}	
			else
				add_edge_graph(graph, line[i+1], line[i], 1, min);
						
			i++;
		}
	}

	int potok = 0;
	for (i = 1; i < count_node; i++)	
		if (existence(graphik,i,second_node) == 1)
			potok += character(graphik, "weight", i, second_node) - character(graph, "weight", i, second_node);		

	delete_graph(graph);

	return potok;	
}

void main(int argc, char* argv[])
{
	char* file = argv[1]; 

	graph_user graphik = reader_graph_matrix(file);

	int first_node,second_node;
	while(1){

		scanf("%d", &first_node);

		if (first_node == 0)
			break;

		scanf("%d", &second_node);	

		if (second_node == 0)
			break;

		printf("%d\n", maxflow(graphik,first_node,second_node));
	}

	delete_graph(graphik);
}