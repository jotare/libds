#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "stack/dynamic_stack.h"

int init_dynamic_stack_suite(void) { return 0; }
int clean_dynamic_stack_suite(void) { return 0; }

void test_dynamic_stack_init_destroy(void) {
    dynamic_stack_t stack = NULL;
    dynamic_stack_init(&stack);
    CU_ASSERT_NOT_EQUAL(stack, NULL);

    dynamic_stack_destroy(&stack);
    CU_ASSERT_EQUAL(stack, NULL);
}

void test_dynamic_stack_push_pop_top(void) {
    dynamic_stack_t stack;
    dynamic_stack_element_t e0 = 0, e1 = 10, e2 = 20, e3 = 30;

    dynamic_stack_init(&stack);
    
    CU_ASSERT_EQUAL(dynamic_stack_length(stack), 0);
    dynamic_stack_push(stack, e0);
    CU_ASSERT_EQUAL(dynamic_stack_top(stack), e0);
    dynamic_stack_push(stack, e1);
    CU_ASSERT_EQUAL(dynamic_stack_top(stack), e1);
    dynamic_stack_push(stack, e2);
    CU_ASSERT_EQUAL(dynamic_stack_top(stack), e2);
    dynamic_stack_push(stack, e3);
    CU_ASSERT_EQUAL(dynamic_stack_top(stack), e3);
    CU_ASSERT_EQUAL(dynamic_stack_length(stack), 4);

    dynamic_stack_pop(stack);
    CU_ASSERT_EQUAL(dynamic_stack_top(stack), e2);
    CU_ASSERT_EQUAL(dynamic_stack_length(stack), 3);

    dynamic_stack_push(stack, e3);
    CU_ASSERT_EQUAL(dynamic_stack_top(stack), e3);
    CU_ASSERT_EQUAL(dynamic_stack_length(stack), 4);

    CU_ASSERT_EQUAL(dynamic_stack_pop(stack), e3);
    CU_ASSERT_EQUAL(dynamic_stack_pop(stack), e2);
    CU_ASSERT_EQUAL(dynamic_stack_pop(stack), e1);
    CU_ASSERT_EQUAL(dynamic_stack_pop(stack), e0);
    CU_ASSERT_EQUAL(dynamic_stack_length(stack), 0);

    dynamic_stack_destroy(&stack);
}

void test_dynamic_stack_is_empty_full(void) {
    dynamic_stack_t stack;
    dynamic_stack_element_t e0 = 0, e1 = 10;

    dynamic_stack_init(&stack);

    CU_ASSERT_TRUE(dynamic_stack_is_empty(stack));
    CU_ASSERT_FALSE(dynamic_stack_is_full(stack));

    dynamic_stack_push(stack, e0);

    CU_ASSERT_FALSE(dynamic_stack_is_empty(stack));
    CU_ASSERT_FALSE(dynamic_stack_is_full(stack));

    dynamic_stack_push(stack, e1);

    CU_ASSERT_FALSE(dynamic_stack_is_empty(stack));
    CU_ASSERT_FALSE(dynamic_stack_is_full(stack));

    dynamic_stack_destroy(&stack);
}

void test_dynamic_stack_clear(void) {
    dynamic_stack_t stack;
    dynamic_stack_element_t e0 = 0, e1 = 10;

    dynamic_stack_init(&stack);

    dynamic_stack_push(stack, e0);
    dynamic_stack_push(stack, e1);

    CU_ASSERT_EQUAL(dynamic_stack_length(stack), 2);
    dynamic_stack_clear(stack);
    CU_ASSERT_EQUAL(dynamic_stack_length(stack), 0);

    dynamic_stack_destroy(&stack);
}

int main(void) {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
	return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Dynamic Stack Suite",
			  init_dynamic_stack_suite,
			  clean_dynamic_stack_suite);
    if (NULL == pSuite) {
	CU_cleanup_registry();
	return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if ((NULL == CU_add_test(pSuite, "init-destroy", test_dynamic_stack_init_destroy)) ||
	(NULL == CU_add_test(pSuite, "push-pop-top-length", test_dynamic_stack_push_pop_top)) ||
	(NULL == CU_add_test(pSuite, "is_empty-is_full", test_dynamic_stack_is_empty_full)) ||
	(NULL == CU_add_test(pSuite, "clear", test_dynamic_stack_clear)))
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
