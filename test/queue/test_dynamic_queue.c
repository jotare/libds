#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "queue/dynamic_queue.h"


typedef struct node_t {
    struct node_t *next;
    dynamic_queue_element_t elem;
} node_t;

typedef struct {
    struct node_t *front, *rear;
    uint8_t n;
} _queue_t;


int init_dynamic_queue_suite(void) { return 0; }
int clean_dynamic_queue_suite(void) { return 0; }

void test_dynamic_queue_init_destroy(void) {
    dynamic_queue_t queue = NULL;
    dynamic_queue_init(&queue);
    CU_ASSERT_NOT_EQUAL(queue, NULL);

    dynamic_queue_destroy(&queue);
    CU_ASSERT_EQUAL(queue, NULL);
}

void test_dynamic_queue_enqueue_dequeue_front_length(void) {
    dynamic_queue_t queue;
    dynamic_queue_element_t e0 = 0, e1 = 10, e2 = 20, e3 = 30;

    dynamic_queue_init(&queue);
    
    CU_ASSERT_EQUAL(dynamic_queue_length(queue), 0);
    dynamic_queue_enqueue(queue, e0);
    dynamic_queue_enqueue(queue, e1);
    dynamic_queue_enqueue(queue, e2);
    dynamic_queue_enqueue(queue, e3);
    CU_ASSERT_EQUAL(dynamic_queue_length(queue), 4);

    CU_ASSERT_EQUAL(dynamic_queue_front(queue), e0);
    CU_ASSERT_EQUAL(dynamic_queue_dequeue(queue), e0)
    CU_ASSERT_EQUAL(dynamic_queue_length(queue), 3);
    CU_ASSERT_EQUAL(dynamic_queue_front(queue), e1);

    dynamic_queue_enqueue(queue, e0);
    CU_ASSERT_EQUAL(dynamic_queue_length(queue), 4);


    dynamic_queue_dequeue(queue);
    dynamic_queue_dequeue(queue);
    dynamic_queue_dequeue(queue);
    dynamic_queue_dequeue(queue);

    CU_ASSERT_EQUAL(dynamic_queue_length(queue), 0);

    dynamic_queue_enqueue(queue, e0);
    dynamic_queue_enqueue(queue, e1);
    dynamic_queue_enqueue(queue, e2);

    CU_ASSERT_EQUAL(dynamic_queue_front(queue), e0);
    CU_ASSERT_EQUAL(dynamic_queue_dequeue(queue), e0);
    CU_ASSERT_EQUAL(dynamic_queue_length(queue), 2);

    CU_ASSERT_EQUAL(dynamic_queue_front(queue), e1);
    CU_ASSERT_EQUAL(dynamic_queue_dequeue(queue), e1);
    CU_ASSERT_EQUAL(dynamic_queue_length(queue), 1);

    CU_ASSERT_EQUAL(dynamic_queue_front(queue), e2);
    CU_ASSERT_EQUAL(dynamic_queue_dequeue(queue), e2);
    CU_ASSERT_EQUAL(dynamic_queue_length(queue), 0);

    dynamic_queue_destroy(&queue);
}

void test_dynamic_queue_is_empty_full(void) {
    dynamic_queue_t queue;
    dynamic_queue_element_t e0 = 0, e1 = 10;

    dynamic_queue_init(&queue);

    CU_ASSERT_TRUE(dynamic_queue_is_empty(queue));
    CU_ASSERT_FALSE(dynamic_queue_is_full(queue));

    dynamic_queue_enqueue(queue, e0);

    CU_ASSERT_FALSE(dynamic_queue_is_empty(queue));
    CU_ASSERT_FALSE(dynamic_queue_is_full(queue));

    dynamic_queue_enqueue(queue, e1);

    CU_ASSERT_FALSE(dynamic_queue_is_empty(queue));
    CU_ASSERT_FALSE(dynamic_queue_is_full(queue));

    dynamic_queue_dequeue(queue);
    dynamic_queue_enqueue(queue, e0);

    CU_ASSERT_FALSE(dynamic_queue_is_empty(queue));
    CU_ASSERT_FALSE(dynamic_queue_is_full(queue));

    dynamic_queue_destroy(&queue);
}

void test_dynamic_queue_clear(void) {
    dynamic_queue_t queue;
    dynamic_queue_element_t e0 = 0, e1 = 10;

    dynamic_queue_init(&queue);

    dynamic_queue_enqueue(queue, e0);
    dynamic_queue_enqueue(queue, e1);

    CU_ASSERT_EQUAL(dynamic_queue_length(queue), 2);
    dynamic_queue_clear(queue);
    CU_ASSERT_EQUAL(dynamic_queue_length(queue), 0);

    dynamic_queue_destroy(&queue);
}

int main(void) {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
	return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Dynamic Queue Suite",
			  init_dynamic_queue_suite,
			  clean_dynamic_queue_suite);
    if (NULL == pSuite) {
	CU_cleanup_registry();
	return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if ((NULL == CU_add_test(pSuite, "init-destroy", test_dynamic_queue_init_destroy)) ||
	(NULL == CU_add_test(pSuite, "enqueue-dequeue-front-length", test_dynamic_queue_enqueue_dequeue_front_length)) ||
	(NULL == CU_add_test(pSuite, "is_empty-is_full", test_dynamic_queue_is_empty_full)) ||
	(NULL == CU_add_test(pSuite, "clear", test_dynamic_queue_clear)))
	{
	    CU_cleanup_registry();
	    return CU_get_error();
	}

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
