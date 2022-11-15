/**
 * @file directed_graph_adj_matrix.h
 * @brief Directed graph implementation using an adjacency matrix
 */
#ifndef DIRECTED_GRAPH_ADJ_MATRIX_H
#define DIRECTED_GRAPH_ADJ_MATRIX_H

#include "graph.h"
#include "../constants.h"

typedef void *directed_graph_adj_matrix_t;


status_t directed_graph_adj_matrix_init(directed_graph_adj_matrix_t *
                                        graph, int size);

unsigned int directed_graph_adj_matrix_size(directed_graph_adj_matrix_t
                                            graph);

status_t directed_graph_adj_matrix_edge_add(directed_graph_adj_matrix_t graph,
                                            edge_t edge, label_t label);

label_t directed_graph_adj_matrix_edge_remove(directed_graph_adj_matrix_t
                                              graph, edge_t edge);

label_t directed_graph_adj_matrix_edge_label(directed_graph_adj_matrix_t
                                             graph, edge_t edge);

status_t directed_graph_adj_matrix_edge_set_label(directed_graph_adj_matrix_t
                                                  graph, edge_t edge,
                                                  label_t label);

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
