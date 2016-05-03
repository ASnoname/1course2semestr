#include "D:\proga\library.h"
#include <stdio.h>

int maxflow(graph_user graphik, int first_node, int second_node){

	graph_user graph = copy_graph(graphik);

	while (1){

		int nezametno = 0; 
		int count_node = func_count_node(graph);

		int i,k;
		int line[count_node];
		for (i = 0; i < count_node; i++)
			line[i] = -1;

		int yes[count_node];
		for (i = 0; i < count_node; i++)
			yes[i] = 0;

		yes[first_node-1] = 1; line[0] = first_node; int var_temp = 0;

		i = first_node; int h; int back = 0; int g = 0;

		do{ 
			h = 0;
			for (k = 1; k <= count_node; k++)
			{  
				if ((existence(graph,i,k) > -1) && (yes[k-1] == 0) && (character(graph, "weight", i, k) > 0)){
					yes[k-1] = 1;

					if (g == 1)
						var_temp--;

					var_temp++;
					g = 0;
					line[var_temp + back] = k;				
					i = k;
					h = 1;
					break;
				}
			}

			if (!h){
				i = line[var_temp - back - 1];
				back++;
				if (i == first_node)
				{
					var_temp += back-1;
					back = 0;
				}
				g = 1;
			}	
			nezametno++;
			if ((i != second_node) && (nezametno == count_node-1)){
				nezametno = 15999;
				break;				
			}

		} while(i != second_node);
		
		i = 0; int min = 1024;
		while ((line[i] != -1) && (i != count_node-1)){

			int l = character(graph, "weight", line[i], line[i+1]);

			if (l < min)
				min = l;

			i++;
		}

		i = 0;
		while ((line[i] != -1) && (i != count_node-1)){

			int l = character(graph, "weight", line[i], line[i+1]);

			delete_edge(graph, line[i], line[i+1]);  
			add_edge_graph(graph, line[i], line[i+1], existence(graph, line[i],line[i+1]), l - min);
			i++;
		}
	
		if (nezametno == 15999)
			break;
	}

	int i; int potok = 0;
	for (i = 0; i < func_count_node(graph); i++)	
		if (existence(graph,i+1,second_node) >= 0){

			int a = character(graph, "weight", i+1, second_node);

			if (a == 0)
				a = character(graphik, "weight", i+1, second_node);

			potok += a;			
		}


	return potok;	
}

void main(int argc, char* argv[])
{
	char* file = argv[1]; 

	graph_user graph = reader_graph_matrix(file);

	int first_node,second_node;
	// while(1){

	// 	scanf("%d", &first_node);

	// 	if (first_node == 0)
	// 		break;

	// 	scanf("%d", &second_node);	

	// 	int potok = maxflow(graphik,first_node,second_node);

	// 	if (potok == -6)
	// 		continue;
	// 	printf("%d\n", potok);
	// }
	printf("%d", maxflow(graph,1,14));
}