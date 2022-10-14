#include <stdlib.h>

#include "graph/graph.h"
#include "graph/adj_matrix.h"


typedef bool adj_matrix_element_t;
typedef struct {
    adj_matrix_element_t *matrix;
    unsigned int size;
} _adj_matrix_t;


static inline bool
edge_exists(_adj_matrix_t * adj_matrix, vertex_t from, vertex_t to)
{
    return adj_matrix->matrix[from * adj_matrix->size + to];
}

static inline void
edge_set(_adj_matrix_t * adj_matrix, vertex_t from, vertex_t to)
{
    adj_matrix->matrix[from * adj_matrix->size + to] = true;
}

static inline void
edge_unset(_adj_matrix_t * adj_matrix, vertex_t from, vertex_t to)
{
    adj_matrix->matrix[from * adj_matrix->size + to] = false;
}


int
adj_matrix_init(adj_matrix_t * am, unsigned int size)
{
    _adj_matrix_t *adj_matrix;
    adj_matrix_element_t *matrix;

    adj_matrix = malloc(sizeof(_adj_matrix_t));
    if (adj_matrix == NULL)
        return -1;

    matrix = malloc(sizeof(adj_matrix_element_t) * size * size);
    if (matrix == NULL) {
        free(adj_matrix);
        return -1;
    }

    adj_matrix->matrix = matrix;
    adj_matrix->size = size;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            edge_unset(adj_matrix, i, j);

    *am = adj_matrix;

    return 0;
}

int
adj_matrix_edge_add(adj_matrix_t am, vertex_t from, vertex_t to)
{
    _adj_matrix_t *adj_matrix = am;

    edge_set(adj_matrix, from, to);

    return 0;
}

int
adj_matrix_edge_remove(adj_matrix_t am, vertex_t from, vertex_t to)
{
    _adj_matrix_t *adj_matrix = am;

    edge_unset(adj_matrix, from, to);

    return 0;
}

bool
adj_matrix_adjancent_vertices(adj_matrix_t am, vertex_t from, vertex_t to)
{
    _adj_matrix_t *adj_matrix = am;

    return edge_exists(adj_matrix, from, to);
}

int
adj_matrix_neighbors_count(adj_matrix_t am, vertex_t vertex)
{
    _adj_matrix_t *adj_matrix = am;
    int count = 0;

    for (int v = 0; v < adj_matrix->size; v++) {
        if (edge_exists(adj_matrix, vertex, v))
            count++;
    }

    return count;
}

int
adj_matrix_neighbors(adj_matrix_t am, vertex_t vertex, vertex_t ** neighbors)
{
    _adj_matrix_t *adj_matrix = am;
    int idx = 0;

    for (int v = 0; v < adj_matrix->size; v++) {
        if (edge_exists(adj_matrix, vertex, v)) {
            (*neighbors)[idx] = v;
            idx++;
        }
    }

    return 0;
}

void
adj_matrix_destroy(adj_matrix_t * am)
{
    _adj_matrix_t *adj_matrix = *am;

    free(adj_matrix->matrix);
    free(adj_matrix);
}
