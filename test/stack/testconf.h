#ifndef STACK_TESTCONF_H
#define STACK_TESTCONF_H

#include <CUnit/TestDB.h>

/**
 * @return Stack suite test case array
 */
CU_TestInfo *get_stack_tests(void);

int init_stack_suite(void);
int cleanup_stack_suite(void);


#endif /* STACK_TESTCONF_H */
