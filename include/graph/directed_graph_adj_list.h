#ifndef DIRECTED_GRAPH_ADJ_LIST_H
#define DIRECTED_GRAPH_ADJ_LIST_H

#include "graph/graph.h"

typedef void *directed_graph_adj_list_t;


int directed_graph_adj_list_init(directed_graph_adj_list_t *
                                 directed_graph_adj_list, int size);

int directed_graph_adj_list_edge_add(directed_graph_adj_list_t
                                     directed_graph_adj_list, vertex_t tail,
                                     vertex_t head);

int directed_graph_adj_list_edge_remove(directed_graph_adj_list_t
                                        directed_graph_adj_list,
                                        vertex_t tail, vertex_t head);

bool directed_graph_adj_list_adjancent_vertices(directed_graph_adj_list_t
                                                directed_graph_adj_list,
                                                vertex_t tail, vertex_t head);

int directed_graph_adj_list_neighbors_count(directed_graph_adj_list_t
                                            directed_graph_adj_list,
                                            vertex_t vertex);

int directed_graph_adj_list_neighbors(directed_graph_adj_list_t
                                      directed_graph_adj_list,
                                      vertex_t vertex, vertex_t ** neighbors);

void directed_graph_adj_list_destroy(directed_graph_adj_list_t *
                                     directed_graph_adj_list);


#endif /* DIRECTED_GRAPH_ADJ_LIST_H */
