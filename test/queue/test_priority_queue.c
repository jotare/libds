#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "queue/priority_queue.h"

#include "queue/testconf.h"

int
init_priority_queue_suite(void)
{
    return 0;
}

int
cleanup_priority_queue_suite(void)
{
    return 0;
}

static void
test_priority_queue_init_destroy(priority_queue_type_t type)
{
    priority_queue_t priority_queue = NULL;

    priority_queue_init(&priority_queue, 10, type);
    CU_ASSERT_PTR_NOT_NULL(priority_queue);

    priority_queue_destroy(&priority_queue);
    CU_ASSERT_PTR_NULL(priority_queue);
}

static void
test_heap_priority_queue_init_destroy(void)
{
    test_priority_queue_init_destroy(HEAP_PRIORITY_QUEUE);
}


static void
test_priority_queue_insert_deletemin(priority_queue_type_t type)
{
    priority_queue_t priority_queue;
    priority_queue_element_t e0 = 0, e1 = 10, e2 = 20, e3 = 30, min;

    priority_queue_init(&priority_queue, 10, type);

    priority_queue_insert(priority_queue, e3, e3);
    priority_queue_insert(priority_queue, e1, e1);
    priority_queue_insert(priority_queue, e0, e0);
    priority_queue_insert(priority_queue, e1, e1);
    priority_queue_insert(priority_queue, e2, e2);
    priority_queue_insert(priority_queue, e3, e3);

    priority_queue_deletemin(priority_queue, &min);
    CU_ASSERT_EQUAL(min, e0);
    priority_queue_deletemin(priority_queue, &min);
    CU_ASSERT_EQUAL(min, e1);
    priority_queue_deletemin(priority_queue, &min);
    CU_ASSERT_EQUAL(min, e1);
    priority_queue_deletemin(priority_queue, &min);
    CU_ASSERT_EQUAL(min, e2);

    priority_queue_insert(priority_queue, e1, e1);
    priority_queue_insert(priority_queue, e0, e0);
    priority_queue_insert(priority_queue, e0, e0);
    priority_queue_insert(priority_queue, e2, e2);

    priority_queue_deletemin(priority_queue, &min);
    CU_ASSERT_EQUAL(min, e0);
    priority_queue_deletemin(priority_queue, &min);
    CU_ASSERT_EQUAL(min, e0);
    priority_queue_deletemin(priority_queue, &min);
    CU_ASSERT_EQUAL(min, e1);
    priority_queue_deletemin(priority_queue, &min);
    CU_ASSERT_EQUAL(min, e2);
    priority_queue_deletemin(priority_queue, &min);
    CU_ASSERT_EQUAL(min, e3);
    priority_queue_deletemin(priority_queue, &min);
    CU_ASSERT_EQUAL(min, e3);

    priority_queue_destroy(&priority_queue);
}

static void
test_heap_priority_queue_insert_deletemin(void)
{
    test_priority_queue_insert_deletemin(HEAP_PRIORITY_QUEUE);
}


static CU_TestInfo priority_queue_tests[] = {
    {"heap priority_queue: init, destroy",
     test_heap_priority_queue_init_destroy},
    {"heap priority_queue: insert, deletemin",
     test_heap_priority_queue_insert_deletemin},

    CU_TEST_INFO_NULL
};

CU_TestInfo *
get_priority_queue_tests(void)
{
    return priority_queue_tests;
}
