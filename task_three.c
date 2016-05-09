#include "D:\proga\library.h"
#include <stdio.h>

int breaking(graph_user graph, int first_node, int second_node){

	int i;
	for (i = 0; i < func_count_node(graph); i++){
		if (existence(graph,i+1,second_node) == 1){

			if (i+1 == first_node)
				return 1;

			return breaking(graph,first_node,i+1);	
		}
	}
	return 0;
}

int maxflow(graph_user graphik, int first_node, int second_node){

	graph_user graph = copy_graph(graphik);
	int count_node = func_count_node(graph);
	int metka = 1; 
	int i,k;
	int line[count_node+1];
	line[count_node] = second_node;
	int yes[count_node];

	while (metka != 0){

		for (i = 0; i < count_node; i++)
			line[i] = -1;

		for (i = 0; i < count_node; i++)
			yes[i] = 0;

		yes[first_node-1] = 1; line[0] = first_node; int var_temp = 0;

		i = first_node; int h; int back = 0; int g = 0;
		int lmetka = 0;

		do{ 
			h = 0;
			for (k = 1; k <= count_node; k++)
			{  
				if ((existence(graph,i,k) == 1) && (yes[k-1] == 0) && (character(graph, "weight", i, k) > 0)){
					yes[k-1] = 1;

					if (g == 0)
						var_temp++;

					if(g == 1)
						line[++var_temp] = k;
					else line[var_temp + back] = k;		

					i = k;
					h = 1; 
					g = 0;

					break;
				}
			}

			if (!h){
				if (var_temp == 0){
					metka = 0;
					break;
				}

				i = line[var_temp - back - 1];

				back++;
				if (i == first_node)
				{
					var_temp = 0;
					back = 0;

					if (breaking(graph,first_node,second_node) == 0){

						metka = 0;
						break;
					}
				}

				g = 1;
			}	

		} while (i != second_node); 

		for (i = 0; i < count_node; i++)
			printf("%d\n", line[i]);
		
		for (i = 0; i < count_node; i++)
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

		if (metka == 0)
			break;
	}

	int potok = 0;
	for (i = 0; i < count_node; i++)	
		if (existence(graph,second_node,i+1) == 1)
			potok += character(graph, "weight", second_node, i+1);	

	delete_graph(graph);

	return potok;	
}

void main(int argc, char* argv[])
{
	char* file = argv[1]; 

	graph_user graph = reader_graph_matrix(file);

	int first_node,second_node;
	while(1){

		scanf("%d", &first_node);

		if (first_node == 0)
			break;

		scanf("%d", &second_node);	

		if (second_node == 0)
			break;

		printf("%d\n", maxflow(graph,first_node,second_node));
	}
}