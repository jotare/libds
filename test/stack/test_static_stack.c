#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "stack/static_stack.h"

int init_static_stack_suite(void) { return 0; }
int clean_static_stack_suite(void) { return 0; }

void test_static_stack_init_destroy(void) {
    static_stack_t stack = NULL;
    static_stack_init(&stack, 10);
    CU_ASSERT_NOT_EQUAL(stack, NULL);

    static_stack_destroy(&stack);
    CU_ASSERT_EQUAL(stack, NULL);
}

void test_static_stack_push_pop_top(void) {
    static_stack_t stack;
    static_stack_element_t e0 = 0, e1 = 10, e2 = 20, e3 = 30;

    static_stack_init(&stack, 5);
    
    CU_ASSERT_EQUAL(static_stack_length(stack), 0);
    static_stack_push(stack, e0);
    CU_ASSERT_EQUAL(static_stack_top(stack), e0);
    static_stack_push(stack, e1);
    CU_ASSERT_EQUAL(static_stack_top(stack), e1);
    static_stack_push(stack, e2);
    CU_ASSERT_EQUAL(static_stack_top(stack), e2);
    static_stack_push(stack, e3);
    CU_ASSERT_EQUAL(static_stack_top(stack), e3);
    CU_ASSERT_EQUAL(static_stack_length(stack), 4);

    static_stack_pop(stack);
    CU_ASSERT_EQUAL(static_stack_top(stack), e2);
    CU_ASSERT_EQUAL(static_stack_length(stack), 3);

    static_stack_push(stack, e3);
    CU_ASSERT_EQUAL(static_stack_top(stack), e3);
    CU_ASSERT_EQUAL(static_stack_length(stack), 4);

    CU_ASSERT_EQUAL(static_stack_pop(stack), e3);
    CU_ASSERT_EQUAL(static_stack_pop(stack), e2);
    CU_ASSERT_EQUAL(static_stack_pop(stack), e1);
    CU_ASSERT_EQUAL(static_stack_pop(stack), e0);
    CU_ASSERT_EQUAL(static_stack_length(stack), 0);

    static_stack_destroy(&stack);
}

void test_static_stack_is_empty_full(void) {
    static_stack_t stack;
    static_stack_element_t e0 = 0, e1 = 10;

    static_stack_init(&stack, 2);

    CU_ASSERT_TRUE(static_stack_is_empty(stack));
    CU_ASSERT_FALSE(static_stack_is_full(stack));

    static_stack_push(stack, e0);

    CU_ASSERT_FALSE(static_stack_is_empty(stack));
    CU_ASSERT_FALSE(static_stack_is_full(stack));

    static_stack_push(stack, e1);

    CU_ASSERT_FALSE(static_stack_is_empty(stack));
    CU_ASSERT_TRUE(static_stack_is_full(stack));

    static_stack_destroy(&stack);
}

void test_static_stack_clear(void) {
    static_stack_t stack;
    static_stack_element_t e0 = 0, e1 = 10;

    static_stack_init(&stack, 2);

    static_stack_push(stack, e0);
    static_stack_push(stack, e1);

    CU_ASSERT_EQUAL(static_stack_length(stack), 2);
    static_stack_clear(stack);
    CU_ASSERT_EQUAL(static_stack_length(stack), 0);

    static_stack_destroy(&stack);
}

int main(void) {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
	return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Static Stack Suite",
			  init_static_stack_suite,
			  clean_static_stack_suite);
    if (NULL == pSuite) {
	CU_cleanup_registry();
	return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if ((NULL == CU_add_test(pSuite, "init-destroy", test_static_stack_init_destroy)) ||
	(NULL == CU_add_test(pSuite, "push-pop-top-length", test_static_stack_push_pop_top)) ||
	(NULL == CU_add_test(pSuite, "is_empty-is_full", test_static_stack_is_empty_full)) ||
	(NULL == CU_add_test(pSuite, "clear", test_static_stack_clear)))
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
