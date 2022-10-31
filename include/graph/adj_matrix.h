#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include "graph/graph.h"

typedef void *adj_matrix_t;

int adj_matrix_init(adj_matrix_t * adj_matrix, unsigned int size);

int adj_matrix_edge_add(adj_matrix_t adj_matrix, edge_t edge, label_t label);
label_t adj_matrix_edge_remove(adj_matrix_t adj_matrix, edge_t edge);

label_t adj_matrix_edge_label(adj_matrix_t adj_matrix, edge_t edge);
int adj_matrix_edge_set_label(adj_matrix_t adj_matrix, edge_t edge,
                              label_t label);

bool adj_matrix_adjancent_vertices(adj_matrix_t adj_matrix, vertex_t from,
                                   vertex_t to);

int adj_matrix_neighbors_count(adj_matrix_t adj_matrix, vertex_t vertex);
int adj_matrix_neighbors(adj_matrix_t adj_matrix, vertex_t vertex,
                         vertex_t ** neighbors);

void adj_matrix_destroy(adj_matrix_t * adj_matrix);

#endif /* ADJ_MATRIX_H */
