#include <stdlib.h>

#include "graph/graph.h"
#include "graph/adj_matrix.h"
#include "graph/directed_graph_adj_matrix.h"


int
directed_graph_adj_matrix_init(directed_graph_adj_matrix_t * graph, int size)
{
    return adj_matrix_init(graph, size);
}

int
directed_graph_adj_matrix_edge_add(directed_graph_adj_matrix_t
                                   graph, vertex_t tail, vertex_t head)
{
    return adj_matrix_edge_add(graph, tail, head);
}

int
directed_graph_adj_matrix_edge_remove(directed_graph_adj_matrix_t
                                      graph, vertex_t tail, vertex_t head)
{
    return adj_matrix_edge_remove(graph, tail, head);
}

bool
directed_graph_adj_matrix_adjancent_vertices(directed_graph_adj_matrix_t
                                             graph,
                                             vertex_t tail, vertex_t head)
{
    return adj_matrix_adjancent_vertices(graph, tail, head);
}

int
directed_graph_adj_matrix_neighbors_count(directed_graph_adj_matrix_t
                                          graph, vertex_t vertex)
{
    return adj_matrix_neighbors_count(graph, vertex);
}

int
directed_graph_adj_matrix_neighbors(directed_graph_adj_matrix_t
                                    graph,
                                    vertex_t vertex, vertex_t ** neighbors)
{
    return adj_matrix_neighbors(graph, vertex, neighbors);
}

void
directed_graph_adj_matrix_destroy(directed_graph_adj_matrix_t * graph)
{
    adj_matrix_destroy(graph);
}
