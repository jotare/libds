#ifndef MAP_TESTCONF_H
#define MAP_TESTCONF_H

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

/**
 * @return Map suite test case array
 */
CU_TestInfo *get_map_tests(void);

int init_map_suite(void);
int cleanup_map_suite(void);


#endif /* MAP_TESTCONF_H */
