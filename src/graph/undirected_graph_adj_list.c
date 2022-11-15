#include <stdlib.h>

#include "graph/graph.h"
#include "graph/adj_list.h"
#include "graph/undirected_graph_adj_list.h"


status_t
undirected_graph_adj_list_init(undirected_graph_adj_list_t * graph, int size)
{
    return adj_list_init(graph, size);
}

unsigned int
undirected_graph_adj_list_size(undirected_graph_adj_list_t graph)
{
    return adj_list_size(graph);
}

status_t
undirected_graph_adj_list_edge_add(undirected_graph_adj_list_t graph,
                                   edge_t edge, label_t label)
{
    int status;

    status = adj_list_edge_add(graph, (edge_t) {edge.from, edge.to}, label);
    if (status != 0)
        return status;
    return adj_list_edge_add(graph, (edge_t) {edge.to, edge.from}, label);
}

label_t
undirected_graph_adj_list_edge_remove(undirected_graph_adj_list_t graph,
                                      edge_t edge)
{
    adj_list_edge_remove(graph, (edge_t) {edge.from, edge.to});
    return adj_list_edge_remove(graph, (edge_t) {edge.to, edge.from});
}

label_t
undirected_graph_adj_list_edge_label(undirected_graph_adj_list_t graph,
                                     edge_t edge)
{
    return adj_list_edge_label(graph, edge);
}

status_t
undirected_graph_adj_list_edge_set_label(undirected_graph_adj_list_t graph,
                                         edge_t edge, label_t label)
{
    return adj_list_edge_set_label(graph, edge, label);
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
