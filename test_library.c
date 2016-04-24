#include <stdio.h>
#include "D:\proga\library.h"

void main(int argc, char* argv[])
{
	FILE* fileik; 
	fileik = fopen(argv[1], "rb");

	graph_user graph,graf;

	if( NULL == fileik ) { 
		printf( "Cannot open file\n" ); 
	} 

	graph_user graphik1 = make_graph(0,15); // 1
	graph_user graphik2 = make_graph(1,18); // 1

	add_edge_graph(graphik1, 1, 2, 0, 5); // 2
	add_edge_graph(graphik2, 1, 2, 1, 2); // 2

	delete_edge(graphik1, 1, 2); // 3
	delete_edge(graphik2, 1, 2); // 3

	int k1 = existence(graphik1, 1, 2); // 4
	int k2 = existence(graphik2, 2, 1);	// 4
		printf("%d\n", k1);
		printf("%d\n", k2);

	int l1 = character(graphik1, "weight", 1, 2); // 5
	int l2 = character(graphik2, "weight", 1, 2); // 5
		printf("%d\n", l1);
		printf("%d\n", l2);

	graph_user copy_graphik1 =  copy_graph(graphik1); // 6
	graph_user copy_graphik2 =  copy_graph(graphik2); // 6

	delete_graph(graphik1); // 7
	delete_graph(graphik2); // 7

	graph = reader_graph_edges(fileik); // 8
	graf = reader_graph_matrix(fileik); // 8

	load_graph_in_file("D:/projects/1.txt", graph); // 9
	load_graph_in_file("D:/projects/2.txt", graf); // 9
}	