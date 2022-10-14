#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include "graph/graph.h"

typedef void *adj_list_t;

int adj_list_init(adj_list_t * adj_list, int size);

int adj_list_edge_add(adj_list_t adj_list, vertex_t from, vertex_t to);
int adj_list_edge_remove(adj_list_t adj_list, vertex_t from, vertex_t to);

bool adj_list_adjancent_vertices(adj_list_t adj_list, vertex_t from,
                                 vertex_t to);

int adj_list_neighbors_count(adj_list_t adj_list, vertex_t vertex);
int adj_list_neighbors(adj_list_t adj_list, vertex_t vertex,
                       vertex_t ** neighbors);

void adj_list_destroy(adj_list_t * adj_list);

#endif /* ADJ_LIST_H */
