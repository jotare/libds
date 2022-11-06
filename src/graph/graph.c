#include <stdio.h>
#include <stdlib.h>

#include "graph/directed_graph_adj_list.h"
#include "graph/directed_graph_adj_matrix.h"
#include "graph/undirected_graph_adj_list.h"
#include "graph/undirected_graph_adj_matrix.h"
#include "graph/graph.h"

typedef struct {
    graph_type_t type;
    void *graph;
} graph_header_t;

typedef struct {
    status_t (*init)(graph_t * graph, int size);

    status_t (*edge_add)(graph_t graph, edge_t edge, label_t label);
    label_t (*edge_remove)(graph_t graph, edge_t edge);
    label_t (*edge_label)(graph_t graph, edge_t edge);
    status_t (*edge_set_label)(graph_t graph, edge_t edge, label_t label);

    bool (*adjancent_vertices)(graph_t graph, vertex_t tail, vertex_t head);
    int (*neighbors_count)(graph_t graph, vertex_t vertex);
    int (*neighbors)(graph_t graph, vertex_t vertex, vertex_t ** neighbors);

    void (*destroy)(graph_t * graph);
} igraph_t;

static const igraph_t directed_graph_adj_list = {
    directed_graph_adj_list_init,
    directed_graph_adj_list_edge_add,
    directed_graph_adj_list_edge_remove,
    directed_graph_adj_list_edge_label,
    directed_graph_adj_list_edge_set_label,
    directed_graph_adj_list_adjancent_vertices,
    directed_graph_adj_list_neighbors_count,
    directed_graph_adj_list_neighbors,
    directed_graph_adj_list_destroy,
};

static const igraph_t directed_graph_adj_matrix = {
    directed_graph_adj_matrix_init,
    directed_graph_adj_matrix_edge_add,
    directed_graph_adj_matrix_edge_remove,
    directed_graph_adj_matrix_edge_label,
    directed_graph_adj_matrix_edge_set_label,
    directed_graph_adj_matrix_adjancent_vertices,
    directed_graph_adj_matrix_neighbors_count,
    directed_graph_adj_matrix_neighbors,
    directed_graph_adj_matrix_destroy,
};

static const igraph_t undirected_graph_adj_list = {
    undirected_graph_adj_list_init,
    undirected_graph_adj_list_edge_add,
    undirected_graph_adj_list_edge_remove,
    undirected_graph_adj_list_edge_label,
    undirected_graph_adj_list_edge_set_label,
    undirected_graph_adj_list_adjancent_vertices,
    undirected_graph_adj_list_neighbors_count,
    undirected_graph_adj_list_neighbors,
    undirected_graph_adj_list_destroy,
};

static const igraph_t undirected_graph_adj_matrix = {
    undirected_graph_adj_matrix_init,
    undirected_graph_adj_matrix_edge_add,
    undirected_graph_adj_matrix_edge_remove,
    undirected_graph_adj_matrix_edge_label,
    undirected_graph_adj_matrix_edge_set_label,
    undirected_graph_adj_matrix_adjancent_vertices,
    undirected_graph_adj_matrix_neighbors_count,
    undirected_graph_adj_matrix_neighbors,
    undirected_graph_adj_matrix_destroy,
};

static const igraph_t *
interface(graph_type_t type)
{
    switch (type) {

    case DIRECTED_GRAPH_ADJ_LIST:
        return &directed_graph_adj_list;

    case DIRECTED_GRAPH_ADJ_MATRIX:
        return &directed_graph_adj_matrix;

    case UNDIRECTED_GRAPH_ADJ_LIST:
        return &undirected_graph_adj_list;

    case UNDIRECTED_GRAPH_ADJ_MATRIX:
        return &undirected_graph_adj_matrix;

    default:
        fprintf(stderr, "Invalid graph type");
        abort();
    }
}

status_t
graph_init(graph_t * graph, int n, graph_type_t type)
{
    graph_header_t *header;
    const igraph_t *ds = interface(type);

    header = malloc(sizeof(graph_header_t));
    if (header == NULL)
        return -1;

    header->type = type;
    int status = ds->init(&(header->graph), n);

    if (status < 0)
        *graph = NULL;
    else
        *graph = header;

    return status;
}

void
graph_destroy(graph_t * graph)
{
    graph_header_t *header;
    const igraph_t *ds;

    header = *graph;
    ds = interface(header->type);

    ds->destroy(&(header->graph));
    free(header);
    *graph = NULL;
}

#define call_graph_interface_function(fun, g, ...)      \
    ({                                                  \
        graph_header_t *header = g;                     \
        igraph_t const *ds = interface(header->type);   \
        return ds->fun(header->graph, ## __VA_ARGS__);  \
    })

status_t
graph_edge_add(graph_t graph, edge_t edge, label_t label)
{
    call_graph_interface_function(edge_add, graph, edge, label);
}

label_t
graph_edge_remove(graph_t graph, edge_t edge)
{
    call_graph_interface_function(edge_remove, graph, edge);
}

label_t
graph_edge_label(graph_t graph, edge_t edge)
{
    call_graph_interface_function(edge_label, graph, edge);
}

status_t
graph_edge_set_label(graph_t graph, edge_t edge, label_t label)
{
    call_graph_interface_function(edge_set_label, graph, edge, label);
}

bool
graph_adjancent_vertices(graph_t graph, vertex_t tail, vertex_t head)
{
    call_graph_interface_function(adjancent_vertices, graph, tail, head);
}

int
graph_neighbors_count(graph_t graph, vertex_t vertex)
{
    call_graph_interface_function(neighbors_count, graph, vertex);
}

int
graph_neighbors(graph_t graph, vertex_t vertex, vertex_t ** neighbors)
{
    call_graph_interface_function(neighbors, graph, vertex, neighbors);
}
