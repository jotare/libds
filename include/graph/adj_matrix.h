/**
 * @file adj_matrix.h
 * @brief Adjacency matrix implementation
 *
 * An adjacency matrix is a graph representation method which uses an
 * matrix representing edges and vertices. Each element of the matrix
 * represent a vertex.
 *
 * This graph representation is more useful where the number of
 * vertices is high compared with the number of edges, as the memory
 * used by the matrix will be better used.
 */
#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include "graph.h"
#include "../constants.h"

typedef void *adj_matrix_t;

status_t adj_matrix_init(adj_matrix_t * adj_matrix, unsigned int size);

status_t adj_matrix_edge_add(adj_matrix_t adj_matrix, edge_t edge,
                             label_t label);
label_t adj_matrix_edge_remove(adj_matrix_t adj_matrix, edge_t edge);

label_t adj_matrix_edge_label(adj_matrix_t adj_matrix, edge_t edge);
status_t adj_matrix_edge_set_label(adj_matrix_t adj_matrix, edge_t edge,
                                   label_t label);

bool adj_matrix_adjancent_vertices(adj_matrix_t adj_matrix, vertex_t from,
                                   vertex_t to);

int adj_matrix_neighbors_count(adj_matrix_t adj_matrix, vertex_t vertex);
int adj_matrix_neighbors(adj_matrix_t adj_matrix, vertex_t vertex,
                         vertex_t ** neighbors);

void adj_matrix_destroy(adj_matrix_t * adj_matrix);

#endif /* ADJ_MATRIX_H */
