#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "graph/graph.h"

#include "graph/testconf.h"


int
init_graph_suite(void)
{
    return 0;
}

int
cleanup_graph_suite(void)
{
    return 0;
}


static void
test_graph_init_destroy(graph_type_t type)
{
    graph_t graph = NULL;

    graph_init(&graph, 10, type);
    CU_ASSERT_PTR_NOT_NULL(graph);

    graph_destroy(&graph);
    CU_ASSERT_PTR_NULL(graph);
}


static void
test_directed_graph_adj_matrix_init_destroy(void)
{
    test_graph_init_destroy(DIRECTED_GRAPH_ADJ_MATRIX);
}

static void
test_directed_graph_adj_list_init_destroy(void)
{
    test_graph_init_destroy(DIRECTED_GRAPH_ADJ_LIST);
}

static void
test_undirected_graph_adj_matrix_init_destroy(void)
{
    test_graph_init_destroy(UNDIRECTED_GRAPH_ADJ_MATRIX);
}

static void
test_undirected_graph_adj_list_init_destroy(void)
{
    test_graph_init_destroy(UNDIRECTED_GRAPH_ADJ_LIST);
}


static void
test_directed_graph(graph_type_t type)
{
    graph_t graph;
    vertex_t neighbors[4];
    vertex_t *neighbors_ptr = (vertex_t *) neighbors;

    CU_ASSERT_EQUAL(graph_init(&graph, 4, type), 0);

    /*
     * +---+       +---+
     * | 0 |------>| 1 |
     * +---+     --+---+
     *   |       -/\ |
     *   |     -/    |
     *   |   -/      |
     *  \/  /       \/
     * +-+-+       +-+-+
     * | 2 |<------| 3 |
     * +---+       +---+
     *
     * Edges:
     * - From 0 to: 1, 2
     * - From 1 to: 3
     * - From 2 to: 1
     * - From 3 to: 2
     */
    graph_edge_add(graph, 0, 1);
    graph_edge_add(graph, 0, 2);
    graph_edge_add(graph, 1, 3);
    graph_edge_add(graph, 2, 1);
    graph_edge_add(graph, 3, 2);

    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 0), 2);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 1), 1);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 2), 1);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 3), 1);

    graph_neighbors(graph, 0, &neighbors_ptr);
    CU_ASSERT(neighbors[0] == 1 || neighbors[0] == 2);
    CU_ASSERT(neighbors[1] == 1 || neighbors[1] == 2);
    CU_ASSERT_NOT_EQUAL(neighbors[0], neighbors[1]);

    graph_neighbors(graph, 1, &neighbors_ptr);
    CU_ASSERT_EQUAL(neighbors[0], 3);

    graph_neighbors(graph, 2, &neighbors_ptr);
    CU_ASSERT_EQUAL(neighbors[0], 1);

    graph_neighbors(graph, 3, &neighbors_ptr);
    CU_ASSERT_EQUAL(neighbors[0], 2);

    /*
     * +---+       +---+
     * | 0 |       | 1 |
     * +---+       +---+
     *   |           |
     *   |           |
     *   |           |
     *  \/          \/
     * +-+-+       +-+-+
     * | 2 |<------| 3 |
     * +---+       +---+
     *
     * Edges:
     * - From 0 to: 2
     * - From 1 to: 3
     * - From 2 to: -
     * - From 3 to: 2
     */
    graph_edge_remove(graph, 0, 1);
    graph_edge_remove(graph, 2, 1);

    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 0), 1);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 1), 1);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 2), 0);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 3), 1);

    graph_neighbors(graph, 0, &neighbors_ptr);
    CU_ASSERT_EQUAL(neighbors[0], 2);

    graph_neighbors(graph, 1, &neighbors_ptr);
    CU_ASSERT_EQUAL(neighbors[0], 3);

    graph_neighbors(graph, 3, &neighbors_ptr);
    CU_ASSERT_EQUAL(neighbors[0], 2);

    graph_destroy(&graph);
}

static void
test_directed_graph_adj_list(void)
{
    test_directed_graph(DIRECTED_GRAPH_ADJ_LIST);
}

static void
test_directed_graph_adj_matrix(void)
{
    test_directed_graph(DIRECTED_GRAPH_ADJ_MATRIX);
}


static void
test_undirected_graph(graph_type_t type)
{
    graph_t graph;
    vertex_t neighbors[4];
    vertex_t *neighbors_ptr = (vertex_t *) neighbors;

    graph_init(&graph, 4, type);

    /*
     * +---+       +---+
     * | 0 |-------| 1 |
     * +---+       +---+
     *   |       -/  |
     *   |     -/    |
     *   |   -/      |
     *   |  /        |
     * +-+-+       +-+-+
     * | 2 |-------| 3 |
     * +---+       +---+
     * 
     * Edges:
     * - From 0 to: 1, 2
     * - From 1 to: 0, 2, 3
     * - From 2 to: 0, 1, 3
     * - From 3 to: 1, 2
     */

    graph_edge_add(graph, 0, 1);
    graph_edge_add(graph, 0, 2);
    graph_edge_add(graph, 1, 3);
    graph_edge_add(graph, 2, 1);
    graph_edge_add(graph, 3, 2);

    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 0), 2);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 1), 3);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 2), 3);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 3), 2);

    graph_neighbors(graph, 0, &neighbors_ptr);
    CU_ASSERT(neighbors[0] == 1 || neighbors[0] == 2);
    CU_ASSERT(neighbors[1] == 1 || neighbors[1] == 2);
    CU_ASSERT_NOT_EQUAL(neighbors[0], neighbors[1]);

    graph_neighbors(graph, 1, &neighbors_ptr);
    CU_ASSERT(neighbors[0] == 0 || neighbors[0] == 2 || neighbors[0] == 3);
    CU_ASSERT(neighbors[1] == 0 || neighbors[1] == 2 || neighbors[1] == 3);
    CU_ASSERT(neighbors[2] == 0 || neighbors[2] == 2 || neighbors[2] == 3);
    CU_ASSERT(neighbors[0] != neighbors[1] && neighbors[1] != neighbors[2])
        graph_neighbors(graph, 2, &neighbors_ptr);
    CU_ASSERT(neighbors[0] == 0 || neighbors[0] == 1 || neighbors[0] == 3);
    CU_ASSERT(neighbors[1] == 0 || neighbors[1] == 1 || neighbors[1] == 3);
    CU_ASSERT(neighbors[2] == 0 || neighbors[2] == 1 || neighbors[2] == 3);
    CU_ASSERT(neighbors[0] != neighbors[1] && neighbors[1] != neighbors[2])
        graph_neighbors(graph, 3, &neighbors_ptr);
    CU_ASSERT(neighbors[0] == 1 || neighbors[0] == 2);
    CU_ASSERT(neighbors[1] == 1 || neighbors[1] == 2);
    CU_ASSERT_NOT_EQUAL(neighbors[0], neighbors[1]);

    /*
     * +---+       +---+
     * | 0 |       | 1 |
     * +---+       +---+
     *   |           |
     *   |           |
     *   |           |
     *   |           |
     * +-+-+       +-+-+
     * | 2 |-------| 3 |
     * +---+       +---+
     * 
     * Edges:
     * - From 0 to: 2
     * - From 1 to: 3
     * - From 2 to: 0, 3
     * - From 3 to: 1, 2
     */
    graph_edge_remove(graph, 0, 1);
    graph_edge_remove(graph, 2, 1);

    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 0), 1);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 1), 1);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 2), 2);
    CU_ASSERT_EQUAL(graph_neighbors_count(graph, 3), 2);

    graph_neighbors(graph, 0, &neighbors_ptr);
    CU_ASSERT_EQUAL(neighbors[0], 2);

    graph_neighbors(graph, 1, &neighbors_ptr);
    CU_ASSERT_EQUAL(neighbors[0], 3);

    graph_neighbors(graph, 2, &neighbors_ptr);
    CU_ASSERT(neighbors[0] == 0 || neighbors[0] == 3);
    CU_ASSERT(neighbors[1] == 0 || neighbors[1] == 3);
    CU_ASSERT_NOT_EQUAL(neighbors[0], neighbors[1]);

    graph_neighbors(graph, 3, &neighbors_ptr);
    CU_ASSERT(neighbors[0] == 1 || neighbors[0] == 2);
    CU_ASSERT(neighbors[1] == 1 || neighbors[1] == 2);
    CU_ASSERT_NOT_EQUAL(neighbors[0], neighbors[1]);

    graph_destroy(&graph);
}

static void
test_undirected_graph_adj_list(void)
{
    test_undirected_graph(UNDIRECTED_GRAPH_ADJ_LIST);
}

static void
test_undirected_graph_adj_matrix(void)
{
    test_undirected_graph(UNDIRECTED_GRAPH_ADJ_MATRIX);
}


static CU_TestInfo graph_tests[] = {
    {"directed graph, adj lists: init, destroy",
     test_directed_graph_adj_list_init_destroy},
    {"directed graph, adj matrix: init, destroy",
     test_directed_graph_adj_matrix_init_destroy},
    {"undirected graph, adj lists: init, destroy",
     test_undirected_graph_adj_list_init_destroy},
    {"undirected graph, adj matrix: init, destroy",
     test_undirected_graph_adj_matrix_init_destroy},

    {"directed graph, adj lists: test", test_directed_graph_adj_list},
    {"directed graph, adj matrix: test", test_directed_graph_adj_matrix},
    {"undirected graph, adj lists: test", test_undirected_graph_adj_list},
    {"undirected graph, adj matrix: test", test_undirected_graph_adj_matrix},

    CU_TEST_INFO_NULL
};

CU_TestInfo *
get_graph_tests(void)
{
    return graph_tests;
}
