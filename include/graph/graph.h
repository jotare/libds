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

typedef void *graph_t;
typedef int vertex_t;
typedef int edge_t;
typedef void *label_t;

typedef enum {
    DIRECTED_GRAPH_ADJ_MATRIX,
    DIRECTED_GRAPH_ADJ_LIST,
    UNDIRECTED_GRAPH_ADJ_MATRIX,
    UNDIRECTED_GRAPH_ADJ_LIST
} graph_type_t;


/** Create a new graph of `size` vertices and type `type` */
int graph_init(graph_t * graph, int size, graph_type_t type);

/**
 * Connect two vertices by an edge with label `edge` and get its id in
 * `edge`.
 */
int graph_edge_add(graph_t graph, vertex_t tail, vertex_t head);

/** Remove edge from vertices tail and head, if exists. */
int graph_edge_remove(graph_t graph, vertex_t tail, vertex_t head);

/**
 * Test whether there is an edge between tail and head vertices.
 */
bool graph_adjancent_vertices(graph_t graph, vertex_t tail, vertex_t head);

/**
 * Return the number of neighbors vertices of `vertex`
 */
int graph_neighbors_count(graph_t graph, vertex_t vertex);

/**
 * List al vertices v such that there is an edge from `vertex` to
 * v. User must ensure there's enough space in `neighbors` list.
 */
int graph_neighbors(graph_t graph, vertex_t vertex, vertex_t ** neighbors);

/**
 * Destroy the graph `graph`. It must be called when the graph won't
 * be used anymore.
 */
void graph_destroy(graph_t * graph);

#endif /* GRAPH_H */
