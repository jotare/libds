#ifndef GRAPH_TESTCONF_H
#define GRAPH_TESTCONF_H

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

/**
 * @return Graph suite test case array
 */
CU_TestInfo *get_graph_tests(void);

int init_graph_suite(void);
int cleanup_graph_suite(void);


#endif /* GRAPH_TESTCONF_H */
