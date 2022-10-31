#include <stdlib.h>

#include "graph/graph.h"
#include "graph/adj_list.h"
#include "graph/undirected_graph_adj_list.h"


int
undirected_graph_adj_list_init(undirected_graph_adj_list_t * graph, int size)
{
    return adj_list_init(graph, size);
}

int
undirected_graph_adj_list_edge_add(undirected_graph_adj_list_t
                                   graph, vertex_t a, vertex_t b)
{
    int status;

    status = adj_list_edge_add(graph, a, b);
    if (status != 0)
        return status;
    return adj_list_edge_add(graph, b, a);
}

int
undirected_graph_adj_list_edge_remove(undirected_graph_adj_list_t
                                      graph, vertex_t a, vertex_t b)
{
    int status;

    status = adj_list_edge_remove(graph, a, b);
    if (status != 0)
        return status;
    return adj_list_edge_remove(graph, b, a);

}

bool
undirected_graph_adj_list_adjancent_vertices(undirected_graph_adj_list_t
                                             graph, vertex_t a, vertex_t b)
{
    return adj_list_adjancent_vertices(graph, a, b);
}

int
undirected_graph_adj_list_neighbors_count(undirected_graph_adj_list_t
                                          graph, vertex_t vertex)
{
    return adj_list_neighbors_count(graph, vertex);
}

int
undirected_graph_adj_list_neighbors(undirected_graph_adj_list_t
                                    graph,
                                    vertex_t vertex, vertex_t ** neighbors)
{
    return adj_list_neighbors(graph, vertex, neighbors);
}

void
undirected_graph_adj_list_destroy(undirected_graph_adj_list_t * graph)
{
    adj_list_destroy(graph);
}
