#ifndef LIBRARY_H
#include <stdio.h>

typedef void* graph_user;

graph_user reader_graph_edges(char* text);
graph_user reader_graph_matrix(char* text);
int existence(graph_user temp_graf, int first_node, int second_node);
void delete_graph(graph_user graph);
void delete_edge(graph_user temp_graf, int first_node, int second_node);
int func_count_edges(graph_user temp_graf);
int func_count_node(graph_user temp_graf);
graph_user make_graph(int form, int size);
void add_edge_graph(graph_user temp_graf, int first_node, int second_node, int orient, int weight);
int character(graph_user temp_graf, char* string, int first_node, int second_node);
graph_user copy_graph(graph_user temp_graf);
void load_graph_in_file(char* text, graph_user temp_graf);

#endif