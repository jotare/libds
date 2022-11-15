/**
 * @file graph.h
 * @brief Labeled graph abstract module
 *
 * The Graph module abstract a labeled graph data structure. It allows
 * the user to choose between directed and undirected graph
 * implementations in runtime.
 *
 * A graph is made of vertices and edges. Each vertex and edge can
 * have a label (value), a pointer to some user-defined data.
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#include "../constants.h"

typedef void *graph_t;
typedef int vertex_t;
struct edge_t {
    vertex_t from, to;
};

typedef struct {
    vertex_t from, to;
} edge_t;

typedef void *label_t;

typedef enum {
    DIRECTED_GRAPH_ADJ_MATRIX,
    DIRECTED_GRAPH_ADJ_LIST,
    UNDIRECTED_GRAPH_ADJ_MATRIX,
    UNDIRECTED_GRAPH_ADJ_LIST
} graph_type_t;


/** Create a new graph of `size` vertices and type `type` */
status_t graph_init(graph_t * graph, int size, graph_type_t type);

/** @return Graph size (number of vertices) */
unsigned int graph_size(graph_t graph);

/**
 * Connect two vertices by an edge with label `edge` and get its id in
 * `edge`.
 */
status_t graph_edge_add(graph_t graph, edge_t edge, label_t label);

/**
 * Remove edge from vertices tail and head, if exists.
 * @return removed edge label or NULL
 */
label_t graph_edge_remove(graph_t graph, edge_t edge);

/** Get edge `edge` label. */
label_t graph_edge_label(graph_t graph, edge_t edge);

/** Set edge `edge` label for `label`. */
status_t graph_edge_set_label(graph_t graph, edge_t edge, label_t label);


/**
 * Test whether there is an edge between tail and head vertices.
 */
bool graph_adjancent_vertices(graph_t graph, vertex_t tail, vertex_t head);

/**
 * @return the number of neighbors vertices of `vertex`
 */
int graph_neighbors_count(graph_t graph, vertex_t vertex);

/**
 * List al vertices v such that there is an edge from `vertex` to
 * v. User must ensure there's enough space in `neighbors` list.
 * @return number of neighbors returned
 */
int graph_neighbors(graph_t graph, vertex_t vertex, vertex_t ** neighbors);

/**
 * Destroy the graph `graph`. It must be called when the graph won't
 * be used anymore.
 */
void graph_destroy(graph_t * graph);

#endif /* GRAPH_H */
