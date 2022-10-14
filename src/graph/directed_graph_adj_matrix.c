#include <stdlib.h>

#include "graph/graph.h"
#include "graph/adj_matrix.h"
#include "graph/directed_graph_adj_matrix.h"


int
directed_graph_adj_matrix_init(directed_graph_adj_matrix_t *
                               directed_graph_adj_matrix, int size)
{
    return adj_matrix_init(directed_graph_adj_matrix, size);
}

int
directed_graph_adj_matrix_edge_add(directed_graph_adj_matrix_t
                                   directed_graph_adj_matrix, vertex_t tail,
                                   vertex_t head)
{
    return adj_matrix_edge_add(directed_graph_adj_matrix, tail, head);
}

int
directed_graph_adj_matrix_edge_remove(directed_graph_adj_matrix_t
                                      directed_graph_adj_matrix,
                                      vertex_t tail, vertex_t head)
{
    return adj_matrix_edge_remove(directed_graph_adj_matrix, tail, head);
}

bool
directed_graph_adj_matrix_adjancent_vertices(directed_graph_adj_matrix_t
                                             directed_graph_adj_matrix,
                                             vertex_t tail, vertex_t head)
{
    return adj_matrix_adjancent_vertices(directed_graph_adj_matrix, tail,
                                         head);
}

int
directed_graph_adj_matrix_neighbors_count(directed_graph_adj_matrix_t
                                          directed_graph_adj_matrix,
                                          vertex_t vertex)
{
    return adj_matrix_neighbors_count(directed_graph_adj_matrix, vertex);
}

int
directed_graph_adj_matrix_neighbors(directed_graph_adj_matrix_t
                                    directed_graph_adj_matrix,
                                    vertex_t vertex, vertex_t ** neighbors)
{
    return adj_matrix_neighbors(directed_graph_adj_matrix, vertex, neighbors);
}

void
directed_graph_adj_matrix_destroy(directed_graph_adj_matrix_t *
                                  directed_graph_adj_matrix)
{
    adj_matrix_destroy(directed_graph_adj_matrix);
}
