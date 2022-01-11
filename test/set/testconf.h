#ifndef SET_TESTCONF_H
#define SET_TESTCONF_H

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

/**
 * @return Set suite test case array
 */
CU_TestInfo *get_set_tests(void);

int init_set_suite(void);
int cleanup_set_suite(void);


#endif /* SET_TESTCONF_H */
