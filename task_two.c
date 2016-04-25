#include <stdio.h>
#include "D:\proga\library.h"

int Dijkstra(graph_user graph, int first, int second){

	int count_node = func_count_node(graph);

	first -= 1; second -= 1;

	int line[count_node][2];
	int i;
	for (i = 0; i < count_node; i++)
		line[i][0] = 1024;
	for (i = 0; i < count_node; i++)
		line[i][1] = 0;

	line[first][0] = 0;
	line[first][1] = 1;

	if ((first+1 > count_node) || (second+1 > count_node))
	{
		printf("Ошибочка :)");
		return;
	}

	int mini;
	int min;
	int k,j;

	for (j = 0; j < count_node; j++)
	{
		min = 1024;

		for (i = 0; i < count_node; i++)
		{
			if (first == i)
				continue;

			if (existence(graph,first+1,i+1) > -1)
			{
				if (line[i][0] > character(graph, "weight", first+1, i+1) + line[first][0])
					line[i][0] = character(graph, "weight", first+1, i+1) + line[first][0];
			}
		}

		line[first][1] = 1;

		for (k = 0; k < count_node; k++){

			if ((line[k][1] == 0) && (line[k][0] < min)){
				min = line[k][0];
				mini = k;
			}
			
		}			

		first = mini;
	}

	return line[second][0];
}

void main(int argc, char const *argv[])
{
	FILE* fileik; 
	fileik = fopen(argv[1], "rb");

	graph_user graph;

	if( NULL == fileik ) { 
		printf( "Cannot open file\n" ); 
		return;
	} 
	graph = reader_graph_edges(fileik);

	int first,second;
	while(1){
		scanf("%d", &first);

		if (first == 0)
			break;

		scanf("%d", &second);		
		int potok = Dijkstra(graph,first,second);
		printf("%d\n", potok);
	}
}