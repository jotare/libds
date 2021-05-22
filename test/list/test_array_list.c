#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <inttypes.h>
#include <stdio.h>

#include "list/array_list.h"

int init_array_list_suite(void) { return 0; }
int clean_array_list_suite(void) { return 0; }

void test_array_list_init_destroy(void) {
    array_list_t list = NULL;
    array_list_init(&list, 10);
    CU_ASSERT_NOT_EQUAL(list, NULL);

    array_list_destroy(&list);
    CU_ASSERT_EQUAL(list, NULL);
}

void test_array_list_get_insert_remove(void) {
    array_list_t list;
    array_list_element_t e0 = 0, e1 = 10, e2 = 20, e3 = 30;

    array_list_init(&list, 5);

    // insert elements
    CU_ASSERT_EQUAL(array_list_length(list), 0);
    array_list_insert(list, 0, e0);
    array_list_insert(list, 1, e2);
    array_list_insert(list, 1, e1);
    array_list_insert(list, 3, e3);
    CU_ASSERT_EQUAL(array_list_length(list), 4);

    // get list values
    CU_ASSERT_EQUAL(array_list_get(list, 0), e0);
    CU_ASSERT_EQUAL(array_list_get(list, 1), e1);
    CU_ASSERT_EQUAL(array_list_get(list, 2), e2);
    CU_ASSERT_EQUAL(array_list_get(list, 3), e3);

    // remove first
    array_list_remove(list, 0);
    CU_ASSERT_EQUAL(array_list_length(list), 3);

    // check list elements
    CU_ASSERT_EQUAL(array_list_get(list, 0), e1);
    CU_ASSERT_EQUAL(array_list_get(list, 1), e2);
    CU_ASSERT_EQUAL(array_list_get(list, 2), e3);
}

void test_array_list_first_last(void) {
    array_list_t list;
    array_list_element_t e0 = 0, e1 = 10, e2 = 20;

    array_list_init(&list, 3);

    array_list_insert(list, 0, e0);
    array_list_insert(list, 1, e1);
    array_list_insert(list, 2, e2);

    CU_ASSERT_EQUAL(array_list_first(list), e0);
    CU_ASSERT_EQUAL(array_list_last(list), e2);
}


void test_array_list_is_empty_full(void) {
    array_list_t list;
    array_list_element_t e0 = 0, e1 = 10;

    array_list_init(&list, 2);

    CU_ASSERT_TRUE(array_list_is_empty(list));
    CU_ASSERT_FALSE(array_list_is_full(list));

    array_list_insert(list, 0, e0);

    CU_ASSERT_FALSE(array_list_is_empty(list));
    CU_ASSERT_FALSE(array_list_is_full(list));

    array_list_insert(list, 1, e1);

    CU_ASSERT_FALSE(array_list_is_empty(list));
    CU_ASSERT_TRUE(array_list_is_full(list));
}

void test_array_list_clear(void) {
    array_list_t list;
    array_list_element_t e0 = 0, e1 = 10;

    array_list_init(&list, 2);

    array_list_insert(list, 0, e0);
    array_list_insert(list, 1, e1);

    CU_ASSERT_EQUAL(array_list_length(list), 2);
    array_list_clear(list);
    CU_ASSERT_EQUAL(array_list_length(list), 0);
}

int8_t cmp(array_list_element_t a, array_list_element_t b) {
    if (a < b)
	return -1;
    else if (a == b)
	return 0;
    else
	return 1;
}

void test_array_list_locate(void) {
    array_list_t list;
    array_list_element_t e0 = 0, e1 = 10, e2 = 20;

    array_list_init(&list, 5);
    array_list_insert(list, 0, e0);
    array_list_insert(list, 1, e1);
    array_list_insert(list, 2, e2);
    
    CU_ASSERT_EQUAL(array_list_locate(list, 30, cmp), -1);
    CU_ASSERT_EQUAL(array_list_locate(list, e0, cmp), 0);
    CU_ASSERT_EQUAL(array_list_locate(list, e1, cmp), 1);
}


int main(void) {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
	return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Array List Suite", init_array_list_suite, clean_array_list_suite);
    if (NULL == pSuite) {
	CU_cleanup_registry();
	return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if ((NULL == CU_add_test(pSuite, "init-destroy", test_array_list_init_destroy)) ||
	(NULL == CU_add_test(pSuite, "get-insert-remove-length", test_array_list_get_insert_remove)) ||
	(NULL == CU_add_test(pSuite, "first-last", test_array_list_first_last)) ||
	(NULL == CU_add_test(pSuite, "is_empty-is_full", test_array_list_is_empty_full)) ||
	(NULL == CU_add_test(pSuite, "clear", test_array_list_clear)) ||
	(NULL == CU_add_test(pSuite, "locate", test_array_list_locate)))
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
