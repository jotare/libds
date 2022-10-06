#ifndef QUEUE_TESTCONF_H
#define QUEUE_TESTCONF_H

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

/**
 * @return Queue suite test case array
 */
CU_TestInfo *get_queue_tests(void);

int init_queue_suite(void);
int cleanup_queue_suite(void);

CU_TestInfo *get_priority_queue_tests(void);

int init_priority_queue_suite(void);
int cleanup_priority_queue_suite(void);

#endif /* QUEUE_TESTCONF_H */
