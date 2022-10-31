#include <stdlib.h>

#include "graph/graph.h"
#include "graph/adj_list.h"
#include "graph/directed_graph_adj_list.h"


int
directed_graph_adj_list_init(directed_graph_adj_list_t * graph, int size)
{
    return adj_list_init(graph, size);
}

int
directed_graph_adj_list_edge_add(directed_graph_adj_list_t
                                 graph, vertex_t tail, vertex_t head)
{
    return adj_list_edge_add(graph, tail, head);
}

int
directed_graph_adj_list_edge_remove(directed_graph_adj_list_t
                                    graph, vertex_t tail, vertex_t head)
{
    return adj_list_edge_remove(graph, tail, head);
}

bool
directed_graph_adj_list_adjancent_vertices(directed_graph_adj_list_t
                                           graph,
                                           vertex_t tail, vertex_t head)
{
    return adj_list_adjancent_vertices(graph, tail, head);
}

int
directed_graph_adj_list_neighbors_count(directed_graph_adj_list_t
                                        graph, vertex_t vertex)
{
    return adj_list_neighbors_count(graph, vertex);
}

int
directed_graph_adj_list_neighbors(directed_graph_adj_list_t
                                  graph, vertex_t vertex,
                                  vertex_t ** neighbors)
{
    return adj_list_neighbors(graph, vertex, neighbors);
}

void
directed_graph_adj_list_destroy(directed_graph_adj_list_t * graph)
{
    adj_list_destroy(graph);
}
