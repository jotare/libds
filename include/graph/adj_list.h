/**
 * @file adj_list.h
 * @brief Adjacency list implementation
 *
 * An adjacency list is a graph representation method which uses an
 * array of linked lists. Each element of the array represents an
 * edge while the linked list associated with it represents its
 * vertices to other edges.
 *
 * This graph representation is more useful where the number of
 * vertices is low compared with the number of edges.
 */
#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include "graph.h"
#include "../constants.h"

typedef void *adj_list_t;

status_t adj_list_init(adj_list_t * adj_list, int size);

status_t adj_list_edge_add(adj_list_t adj_list, edge_t edge, label_t label);
label_t adj_list_edge_remove(adj_list_t adj_list, edge_t edge);

label_t adj_list_edge_label(adj_list_t adj_list, edge_t edge);
status_t adj_list_edge_set_label(adj_list_t adj_list, edge_t edge,
                                 label_t label);

bool adj_list_adjancent_vertices(adj_list_t adj_list, vertex_t from,
                                 vertex_t to);

int adj_list_neighbors_count(adj_list_t adj_list, vertex_t vertex);
int adj_list_neighbors(adj_list_t adj_list, vertex_t vertex,
                       vertex_t ** neighbors);

void adj_list_destroy(adj_list_t * adj_list);

#endif /* ADJ_LIST_H */
