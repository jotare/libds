#include <stdlib.h>

#include "graph/graph.h"
#include "graph/adj_list.h"
#include "graph/undirected_graph_adj_list.h"


int
undirected_graph_adj_list_init(undirected_graph_adj_list_t *
                               undirected_graph_adj_list, int size)
{
    return adj_list_init(undirected_graph_adj_list, size);
}

int
undirected_graph_adj_list_edge_add(undirected_graph_adj_list_t
                                   undirected_graph_adj_list, vertex_t a,
                                   vertex_t b)
{
    int status;

    status = adj_list_edge_add(undirected_graph_adj_list, a, b);
    if (status != 0)
        return status;
    return adj_list_edge_add(undirected_graph_adj_list, b, a);
}

int
undirected_graph_adj_list_edge_remove(undirected_graph_adj_list_t
                                      undirected_graph_adj_list, vertex_t a,
                                      vertex_t b)
{
    int status;

    status = adj_list_edge_remove(undirected_graph_adj_list, a, b);
    if (status != 0)
        return status;
    return adj_list_edge_remove(undirected_graph_adj_list, b, a);

}

bool
undirected_graph_adj_list_adjancent_vertices(undirected_graph_adj_list_t
                                             undirected_graph_adj_list,
                                             vertex_t a, vertex_t b)
{
    return adj_list_adjancent_vertices(undirected_graph_adj_list, a, b);
}

int
undirected_graph_adj_list_neighbors_count(undirected_graph_adj_list_t
                                          undirected_graph_adj_list,
                                          vertex_t vertex)
{
    return adj_list_neighbors_count(undirected_graph_adj_list, vertex);
}

int
undirected_graph_adj_list_neighbors(undirected_graph_adj_list_t
                                    undirected_graph_adj_list,
                                    vertex_t vertex, vertex_t ** neighbors)
{
    return adj_list_neighbors(undirected_graph_adj_list, vertex, neighbors);
}

void
undirected_graph_adj_list_destroy(undirected_graph_adj_list_t *
                                  undirected_graph_adj_list)
{
    adj_list_destroy(undirected_graph_adj_list);
}
