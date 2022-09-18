#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "queue/queue.h"

#include "queue/testconf.h"

int init_queue_suite(void) { return 0; }
int cleanup_queue_suite(void) { return 0; }

static void test_queue_init_destroy(queue_type_t type) {
    queue_t queue = NULL;
    queue_init(&queue, 10, type);
    CU_ASSERT_PTR_NOT_NULL(queue);

    queue_destroy(&queue);
    CU_ASSERT_PTR_NULL(queue);
}

static void test_static_queue_init_destroy(void) {
    test_queue_init_destroy(STATIC_QUEUE);
}

static void test_dynamic_queue_init_destroy(void) {
    test_queue_init_destroy(DYNAMIC_QUEUE);
}


static void test_queue_enqueue_dequeue_front_length(queue_type_t type) {
    queue_t queue;
    queue_element_t e0 = 0, e1 = 10, e2 = 20, e3 = 30;

    queue_init(&queue, 4, type);

    CU_ASSERT_EQUAL(queue_length(queue), 0);
    queue_enqueue(queue, e0);
    queue_enqueue(queue, e1);
    queue_enqueue(queue, e2);
    queue_enqueue(queue, e3);
    CU_ASSERT_EQUAL(queue_length(queue), 4);

    CU_ASSERT_EQUAL(queue_front(queue), e0);
    CU_ASSERT_EQUAL(queue_dequeue(queue), e0)
    CU_ASSERT_EQUAL(queue_length(queue), 3);
    CU_ASSERT_EQUAL(queue_front(queue), e1);

    queue_enqueue(queue, e0);
    CU_ASSERT_EQUAL(queue_length(queue), 4);

    queue_dequeue(queue);
    queue_dequeue(queue);
    queue_dequeue(queue);
    queue_dequeue(queue);

    CU_ASSERT_EQUAL(queue_length(queue), 0);

    queue_enqueue(queue, e0);
    queue_enqueue(queue, e1);
    queue_enqueue(queue, e2);

    CU_ASSERT_EQUAL(queue_front(queue), e0);
    CU_ASSERT_EQUAL(queue_dequeue(queue), e0);
    CU_ASSERT_EQUAL(queue_length(queue), 2);

    CU_ASSERT_EQUAL(queue_front(queue), e1);
    CU_ASSERT_EQUAL(queue_dequeue(queue), e1);
    CU_ASSERT_EQUAL(queue_length(queue), 1);

    CU_ASSERT_EQUAL(queue_front(queue), e2);
    CU_ASSERT_EQUAL(queue_dequeue(queue), e2);
    CU_ASSERT_EQUAL(queue_length(queue), 0);

    queue_destroy(&queue);
}

static void test_static_queue_enqueue_dequeue_front_length(void) {
    test_queue_enqueue_dequeue_front_length(STATIC_QUEUE);
}

static void test_dynamic_queue_enqueue_dequeue_front_length(void) {
    test_queue_enqueue_dequeue_front_length(DYNAMIC_QUEUE);
}


static void test_queue_is_empty_is_full(queue_type_t type) {
    queue_t queue;
    queue_element_t e0 = 0, e1 = 10;

    queue_init(&queue, 2, type);

    CU_ASSERT_TRUE(queue_is_empty(queue));
    CU_ASSERT_FALSE(queue_is_full(queue));

    queue_enqueue(queue, e0);

    CU_ASSERT_FALSE(queue_is_empty(queue));
    CU_ASSERT_FALSE(queue_is_full(queue));

    queue_enqueue(queue, e1);

    CU_ASSERT_FALSE(queue_is_empty(queue));
    if (type == STATIC_QUEUE) {
        CU_ASSERT_TRUE(queue_is_full(queue));
    } else {
        CU_ASSERT_FALSE(queue_is_full(queue));
    }

    queue_dequeue(queue);
    queue_enqueue(queue, e0);

    CU_ASSERT_FALSE(queue_is_empty(queue));
    if (type == STATIC_QUEUE) {
        CU_ASSERT_TRUE(queue_is_full(queue));        
    } else {
        CU_ASSERT_FALSE(queue_is_full(queue));
    }

    queue_destroy(&queue);
}

static void test_static_queue_is_empty_is_full(void) {
    test_queue_is_empty_is_full(STATIC_QUEUE);
}

static void test_dynamic_queue_is_empty_is_full(void) {
    test_queue_is_empty_is_full(DYNAMIC_QUEUE);
}


static void test_queue_clear(queue_type_t type) {
    queue_t queue;
    queue_element_t e0 = 0, e1 = 10;

    queue_init(&queue, 2, type);

    queue_enqueue(queue, e0);
    queue_enqueue(queue, e1);

    CU_ASSERT_EQUAL(queue_length(queue), 2);
    queue_clear(queue);
    CU_ASSERT_EQUAL(queue_length(queue), 0);

    queue_destroy(&queue);
}

static void test_static_queue_clear(void) {
    test_queue_clear(STATIC_QUEUE);
}

static void test_dynamic_queue_clear(void) {
    test_queue_clear(DYNAMIC_QUEUE);
}


static CU_TestInfo queue_tests[] = {
    {"static queue: init, destroy", test_static_queue_init_destroy},
    {"static queue: enqueue, dequeue, front, length", test_static_queue_enqueue_dequeue_front_length},
    {"static queue: is_empty, is_full", test_static_queue_is_empty_is_full},
    {"static queue: clear", test_static_queue_clear},

    {"dynamic queue: init, destroy", test_dynamic_queue_init_destroy},
    {"dynamic queue: enqueue, dequeue, front, length", test_dynamic_queue_enqueue_dequeue_front_length},
    {"dynamic queue: is_empty, is_full", test_dynamic_queue_is_empty_is_full},
    {"dynamic queue: clear", test_dynamic_queue_clear},

    CU_TEST_INFO_NULL
};

CU_TestInfo *get_queue_tests(void) {
    return queue_tests;
}
