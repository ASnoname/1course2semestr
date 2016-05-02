#include <stdio.h>
#include "D:\proga\library.h"

void main(int argc, char* argv[])
{
	graph_user graph1;
	graph_user graph2;
	graph_user graph3; 
	graph_user graph4; 

	char* text = argv[1];

	graph1 = reader_graph_edges(text); 
	graph2 = reader_graph_matrix(text); 

	graph3 = copy_graph(graph1); 
	graph4 = copy_graph(graph2); 

	add_edge_graph(graph3, 1, 5, 1, 5); 
	
	delete_edge(graph4, 1, 3); 

	load_graph_in_file("D:/projects/1.txt", graph1); 
	load_graph_in_file("D:/projects/2.txt", graph2); 
	load_graph_in_file("D:/projects/3.txt", graph3); 
	load_graph_in_file("D:/projects/4.txt", graph4); 

	graph_user graph6 = make_graph(1,3); 
//	// add_edge_graph(graph6, 1, 2, 1, 5); 
//	// add_edge_graph(graph6, 1, 3, 0, 7); 
//	// add_edge_graph(graph6, 2, 3, -1, 2); 

	// load_graph_in_file("D:/projects/5.txt", graph6); 

	// graph_user graph7 = reader_graph_edges("D:/projects/5.txt"); 

	// load_graph_in_file("D:/projects/6.txt", graph7); 

// 	int i,g;

// 	for (i = 1; i <= func_count_node(graph6); i++)
// 	{
// 		for (g = 1; g <= func_count_node(graph6); g++)
// 		{
// 			if (existence(graph6, i, g) != -3)
// 			{
// 				printf("%d_%d\n", i,g);
// 			}
// 		}
// 	}
// printf("\n");
// 	for (i = 1; i <= func_count_node(graph7); i++)
// 	{
// 		for (g = 1; g <= func_count_node(graph7); g++)
// 		{
// 			if (existence(graph7, i, g) != -3)
// 			{
// 				printf("%d_%d\n", i,g);
// 			}
// 		}

// 	}
}	