#ifndef UNDIRECTED_GRAPH_ADJ_LIST_H
#define UNDIRECTED_GRAPH_ADJ_LIST_H

#include "graph.h"

typedef void *undirected_graph_adj_list_t;


int undirected_graph_adj_list_init(undirected_graph_adj_list_t *
                                   graph, int size);

int undirected_graph_adj_list_edge_add(undirected_graph_adj_list_t graph,
                                       edge_t edge, label_t label);
label_t undirected_graph_adj_list_edge_remove(undirected_graph_adj_list_t
                                              graph, edge_t edge);

label_t undirected_graph_adj_list_edge_label(undirected_graph_adj_list_t
                                             graph, edge_t edge);
int undirected_graph_adj_list_edge_set_label(undirected_graph_adj_list_t
                                             graph, edge_t edge,
                                             label_t label);

bool undirected_graph_adj_list_adjancent_vertices(undirected_graph_adj_list_t
                                                  graph,
                                                  vertex_t tail,
                                                  vertex_t head);

int undirected_graph_adj_list_neighbors_count(undirected_graph_adj_list_t
                                              graph, vertex_t vertex);
int undirected_graph_adj_list_neighbors(undirected_graph_adj_list_t graph,
                                        vertex_t vertex,
                                        vertex_t ** neighbors);

void undirected_graph_adj_list_destroy(undirected_graph_adj_list_t * graph);


#endif /* UNDIRECTED_GRAPH_ADJ_LIST_H */
