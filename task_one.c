#include <stdio.h>
#include "D:\proga\library.h"

void dfs(graph_user graph){
	int N = func_count_node(graph);
	
	int i,k;

	int line[N+1];
	for (i = 2; i < N+1; i++)
		line[i] = -1;

	int yes[N];
	for (i = 1; i < N; i++)
		yes[i] = 0;

	yes[0] = 1; line[1] = 1; int var_temp = 1;
				line[0] = 0;

	i = 1; int h; int back = 0; int g = 0;

	do{ 
		h = 0;
		for (k = 2; k <= N; k++)
		{  
			if ((existence(graph,i,k) != -3)  &&  (yes[k-1] == 0)){
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
			if (i == 1)
			{
				var_temp = var_temp + back;
				back = 0;
			}
			g = 1;
		}	
	} while(i != 0);

	for (i = 1; i < N+1; i++)
		printf("%d\n", line[i]);
}

void bfs(graph_user graph){
	int N = func_count_node(graph);

	int i,j;
	int line[N];
	
	int a; int b;

	for (i = 0; i < N; i++)
		line[i] = 0;

	line[0] = 1; int k = 0; int l = 0; i = 0; 

	for (i = 0; i < N; i++)
	{
		for (b = line[i] + 1; b <= N; b++)
		{
			if (existence(graph,line[i],b) != -3)
			{
				for (j = 0; j < N; j++)
				{
					if (b != line[j])
						k++;
				}
				if (k == j)
				{
					while(line[l] != 0)
						l++;
					line[l] = b;
				}
				k = 0; 
			}
		}
	}
	i = 0;

	while(i < N){
		printf("%d\n", line[i]);
		i++;
	}
}

void main (int argc, char* argv[]){

	FILE* fileik; 
	fileik = fopen(argv[1], "rb");

	graph_user graph;

	if( NULL == fileik ) { 
		printf( "Cannot open file\n" ); 
		return;
	} 
	graph = reader_graph_edges(fileik);

	bfs(graph);
	dfs(graph);
}