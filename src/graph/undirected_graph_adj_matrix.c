#include <stdlib.h>

#include "graph/graph.h"
#include "graph/adj_matrix.h"
#include "graph/undirected_graph_adj_matrix.h"


int
undirected_graph_adj_matrix_init(undirected_graph_adj_matrix_t *
                                 graph, int size)
{
    return adj_matrix_init(graph, size);
}

int
undirected_graph_adj_matrix_edge_add(undirected_graph_adj_matrix_t
                                     graph, vertex_t a, vertex_t b)
{
    int status;

    status = adj_matrix_edge_add(graph, a, b);
    if (status != 0)
        return status;
    return adj_matrix_edge_add(graph, b, a);
}

int
undirected_graph_adj_matrix_edge_remove(undirected_graph_adj_matrix_t
                                        graph, vertex_t a, vertex_t b)
{
    int status;

    status = adj_matrix_edge_remove(graph, a, b);
    if (status != 0)
        return status;
    return adj_matrix_edge_remove(graph, b, a);

}

bool
undirected_graph_adj_matrix_adjancent_vertices(undirected_graph_adj_matrix_t
                                               graph, vertex_t a, vertex_t b)
{
    return adj_matrix_adjancent_vertices(graph, a, b);
}

int
undirected_graph_adj_matrix_neighbors_count(undirected_graph_adj_matrix_t
                                            graph, vertex_t vertex)
{
    return adj_matrix_neighbors_count(graph, vertex);
}

int
undirected_graph_adj_matrix_neighbors(undirected_graph_adj_matrix_t
                                      graph,
                                      vertex_t vertex, vertex_t ** neighbors)
{
    return adj_matrix_neighbors(graph, vertex, neighbors);
}

void
undirected_graph_adj_matrix_destroy(undirected_graph_adj_matrix_t * graph)
{
    adj_matrix_destroy(graph);
}
