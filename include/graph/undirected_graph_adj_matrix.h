/**
 * @file undirected_graph_adj_matrix.h
 * @brief Undirected graph implementation using an adjacency matrix
 */
#ifndef UNDIRECTED_GRAPH_ADJ_MATRIX_H
#define UNDIRECTED_GRAPH_ADJ_MATRIX_H

#include "graph.h"
#include "../constants.h"

typedef void *undirected_graph_adj_matrix_t;


status_t undirected_graph_adj_matrix_init(undirected_graph_adj_matrix_t *
                                          graph, int size);

unsigned int undirected_graph_adj_matrix_size(undirected_graph_adj_matrix_t
                                              graph);

status_t undirected_graph_adj_matrix_edge_add(undirected_graph_adj_matrix_t
                                              graph, edge_t edge,
                                              label_t label);
label_t undirected_graph_adj_matrix_edge_remove(undirected_graph_adj_matrix_t
                                                graph, edge_t edge);

label_t undirected_graph_adj_matrix_edge_label(undirected_graph_adj_matrix_t
                                               graph, edge_t edge);
status_t
undirected_graph_adj_matrix_edge_set_label(undirected_graph_adj_matrix_t
                                           graph, edge_t edge, label_t label);

bool


undirected_graph_adj_matrix_adjancent_vertices(undirected_graph_adj_matrix_t
                                               graph, vertex_t tail,
                                               vertex_t head);

int undirected_graph_adj_matrix_neighbors_count(undirected_graph_adj_matrix_t
                                                graph, vertex_t vertex);
int undirected_graph_adj_matrix_neighbors(undirected_graph_adj_matrix_t graph,
                                          vertex_t vertex,
                                          vertex_t ** neighbors);

void undirected_graph_adj_matrix_destroy(undirected_graph_adj_matrix_t *
                                         graph);


#endif /* UNDIRECTED_GRAPH_ADJ_MATRIX_H */
