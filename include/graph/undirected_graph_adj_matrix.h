#ifndef UNDIRECTED_GRAPH_ADJ_MATRIX_H
#define UNDIRECTED_GRAPH_ADJ_MATRIX_H

#include "graph/graph.h"

typedef void *undirected_graph_adj_matrix_t;


int undirected_graph_adj_matrix_init(undirected_graph_adj_matrix_t *
                                     undirected_graph_adj_matrix, int size);

int undirected_graph_adj_matrix_edge_add(undirected_graph_adj_matrix_t
                                         undirected_graph_adj_matrix,
                                         vertex_t tail, vertex_t head);

int undirected_graph_adj_matrix_edge_remove(undirected_graph_adj_matrix_t
                                            undirected_graph_adj_matrix,
                                            vertex_t tail, vertex_t head);

bool


undirected_graph_adj_matrix_adjancent_vertices(undirected_graph_adj_matrix_t
                                               undirected_graph_adj_matrix,
                                               vertex_t tail, vertex_t head);

int undirected_graph_adj_matrix_neighbors_count(undirected_graph_adj_matrix_t
                                                undirected_graph_adj_matrix,
                                                vertex_t vertex);

int undirected_graph_adj_matrix_neighbors(undirected_graph_adj_matrix_t
                                          undirected_graph_adj_matrix,
                                          vertex_t vertex,
                                          vertex_t ** neighbors);

void undirected_graph_adj_matrix_destroy(undirected_graph_adj_matrix_t *
                                         undirected_graph_adj_matrix);


#endif /* UNDIRECTED_GRAPH_ADJ_MATRIX_H */
