#ifndef LIST_TESTCONF_H
#define LIST_TESTCONF_H

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

/**
 * @return List suite test case array
 */
CU_TestInfo *get_list_tests(void);

int init_list_suite(void);
int cleanup_list_suite(void);


#endif /* LIST_TESTCONF_H */
