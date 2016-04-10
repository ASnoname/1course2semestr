#ifndef LIBRARY_H
#include <stdio.h>

typedef void* graph_user;

graph_user reader(FILE* file);
int existence(graph_user temp_graf, int a, int b);
void* delete_graph(graph_user graph);
int count_edges(graph_user temp_graf);
int count_node(graph_user temp_graf);

#endif