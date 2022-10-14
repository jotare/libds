#include <stdlib.h>

#include "graph/graph.h"
#include "graph/adj_matrix.h"
#include "graph/undirected_graph_adj_matrix.h"


int
undirected_graph_adj_matrix_init(undirected_graph_adj_matrix_t *
                                 undirected_graph_adj_matrix, int size)
{
    return adj_matrix_init(undirected_graph_adj_matrix, size);
}

int
undirected_graph_adj_matrix_edge_add(undirected_graph_adj_matrix_t
                                     undirected_graph_adj_matrix, vertex_t a,
                                     vertex_t b)
{
    int status;

    status = adj_matrix_edge_add(undirected_graph_adj_matrix, a, b);
    if (status != 0)
        return status;
    return adj_matrix_edge_add(undirected_graph_adj_matrix, b, a);
}

int
undirected_graph_adj_matrix_edge_remove(undirected_graph_adj_matrix_t
                                        undirected_graph_adj_matrix,
                                        vertex_t a, vertex_t b)
{
    int status;

    status = adj_matrix_edge_remove(undirected_graph_adj_matrix, a, b);
    if (status != 0)
        return status;
    return adj_matrix_edge_remove(undirected_graph_adj_matrix, b, a);

}

bool
undirected_graph_adj_matrix_adjancent_vertices(undirected_graph_adj_matrix_t
                                               undirected_graph_adj_matrix,
                                               vertex_t a, vertex_t b)
{
    return adj_matrix_adjancent_vertices(undirected_graph_adj_matrix, a, b);
}

int
undirected_graph_adj_matrix_neighbors_count(undirected_graph_adj_matrix_t
                                            undirected_graph_adj_matrix,
                                            vertex_t vertex)
{
    return adj_matrix_neighbors_count(undirected_graph_adj_matrix, vertex);
}

int
undirected_graph_adj_matrix_neighbors(undirected_graph_adj_matrix_t
                                      undirected_graph_adj_matrix,
                                      vertex_t vertex, vertex_t ** neighbors)
{
    return adj_matrix_neighbors(undirected_graph_adj_matrix, vertex,
                                neighbors);
}

void
undirected_graph_adj_matrix_destroy(undirected_graph_adj_matrix_t *
                                    undirected_graph_adj_matrix)
{
    adj_matrix_destroy(undirected_graph_adj_matrix);
}
