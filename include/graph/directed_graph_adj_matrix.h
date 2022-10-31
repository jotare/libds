#ifndef DIRECTED_GRAPH_ADJ_MATRIX_H
#define DIRECTED_GRAPH_ADJ_MATRIX_H

#include "graph/graph.h"

typedef void *directed_graph_adj_matrix_t;


int directed_graph_adj_matrix_init(directed_graph_adj_matrix_t *
                                   graph, int size);

int directed_graph_adj_matrix_edge_add(directed_graph_adj_matrix_t
                                       graph, vertex_t tail, vertex_t head);

int directed_graph_adj_matrix_edge_remove(directed_graph_adj_matrix_t
                                          graph,
                                          vertex_t tail, vertex_t head);

bool directed_graph_adj_matrix_adjancent_vertices(directed_graph_adj_matrix_t
                                                  graph,
                                                  vertex_t tail,
                                                  vertex_t head);

int directed_graph_adj_matrix_neighbors_count(directed_graph_adj_matrix_t
                                              graph, vertex_t vertex);

int directed_graph_adj_matrix_neighbors(directed_graph_adj_matrix_t
                                        graph,
                                        vertex_t vertex,
                                        vertex_t ** neighbors);

void directed_graph_adj_matrix_destroy(directed_graph_adj_matrix_t * graph);


#endif /* DIRECTED_GRAPH_ADJ_MATRIX_H */
