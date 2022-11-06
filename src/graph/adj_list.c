#include <stdlib.h>

#include "graph/graph.h"
#include "graph/adj_list.h"

typedef struct node_t {
    vertex_t vertex;
    label_t label;
    struct node_t *next;
} node_t;

typedef struct {
    node_t **edges;
    unsigned int size;
} _adj_list_t;


status_t
adj_list_init(adj_list_t * al, int size)
{
    _adj_list_t *adj_list;
    node_t **edges_list;

    adj_list = malloc(sizeof(_adj_list_t));
    if (adj_list == NULL)
        return ALLOC_ERROR;

    edges_list = malloc(sizeof(node_t) * size);
    if (edges_list == NULL) {
        free(adj_list);
        return ALLOC_ERROR;
    }

    adj_list->edges = edges_list;
    adj_list->size = size;

    *al = adj_list;

    return SUCCESS;
}


status_t
adj_list_edge_add(adj_list_t al, edge_t edge, label_t label)
{
    _adj_list_t *adj_list = al;

    node_t *new = malloc(sizeof(node_t));

    if (new == NULL)
        return ALLOC_ERROR;
    new->vertex = edge.to;
    new->label = NULL;

    if (adj_list->edges[edge.from] == NULL)
        new->next = NULL;
    else
        new->next = adj_list->edges[edge.from];

    /* insert it in the front of the linked list of edges */
    adj_list->edges[edge.from] = new;

    return SUCCESS;
}

label_t
adj_list_edge_remove(adj_list_t al, edge_t edge)
{
    _adj_list_t *adj_list = al;

    node_t *previous = NULL;
    node_t *ptr = adj_list->edges[edge.from];

    while (ptr != NULL) {
        if (ptr->vertex == edge.to) {
            label_t label = ptr->label;

            if (previous == NULL) {
                adj_list->edges[edge.from] = ptr->next;
            } else {
                previous->next = ptr->next;
            }

            free(ptr);
            return label;
        }

        previous = ptr;
        ptr = ptr->next;
    }

    return NULL;
}

label_t
adj_list_edge_label(adj_list_t al, edge_t edge)
{
    _adj_list_t *adj_list = al;

    node_t *ptr = adj_list->edges[edge.from];

    while (ptr != NULL) {
        if (ptr->vertex == edge.to) {
            return ptr->label;
        }
        ptr = ptr->next;
    }

    return NULL;
}

status_t
adj_list_edge_set_label(adj_list_t al, edge_t edge, label_t label)
{
    _adj_list_t *adj_list = al;

    node_t *ptr = adj_list->edges[edge.from];

    while (ptr != NULL) {
        if (ptr->vertex == edge.to) {
            ptr->label = label;
            return SUCCESS;
        }
        ptr = ptr->next;
    }

    return NOT_FOUND;
}

bool
adj_list_adjancent_vertices(adj_list_t al, vertex_t from, vertex_t to)
{
    _adj_list_t *adj_list = al;

    node_t *ptr = adj_list->edges[from];

    while (ptr != NULL) {
        if (ptr->vertex == to)
            return true;
        ptr = ptr->next;
    }

    return false;
}

int
adj_list_neighbors_count(adj_list_t al, vertex_t vertex)
{
    _adj_list_t *adj_list = al;
    node_t *ptr = adj_list->edges[vertex];
    int count = 0;

    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }

    return count;
}

int
adj_list_neighbors(adj_list_t al, vertex_t vertex, vertex_t ** neighbors)
{
    _adj_list_t *adj_list = al;
    node_t *ptr = adj_list->edges[vertex];
    int idx = 0;

    while (ptr != NULL) {
        (*neighbors)[idx] = ptr->vertex;
        idx++;
        ptr = ptr->next;
    }

    return idx;
}

void
adj_list_destroy(adj_list_t * al)
{
    _adj_list_t *adj_list = *al;

    for (int i = 0; i < adj_list->size; i++) {
        while (adj_list->edges[i] != NULL) {
            node_t *next = adj_list->edges[i]->next;

            free(adj_list->edges[i]);
            adj_list->edges[i] = next;
        }
    }

    free(adj_list);
}
