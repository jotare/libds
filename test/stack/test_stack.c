#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "stack/stack.h"

#include "stack/testconf.h"


int
init_stack_suite(void)
{
    return 0;
}

int
cleanup_stack_suite(void)
{
    return 0;
}


static void
test_stack_init_destroy(stack_type_t type)
{
    stack_t stack = NULL;

    stack_init(&stack, 10, type);
    CU_ASSERT_PTR_NOT_NULL(stack);

    stack_destroy(&stack);
    CU_ASSERT_PTR_NULL(stack);
}

static void
test_static_stack_init_destroy(void)
{
    test_stack_init_destroy(STATIC_STACK);
}

static void
test_dynamic_stack_init_destroy(void)
{
    test_stack_init_destroy(DYNAMIC_STACK);
}


static void
test_stack_push_pop_top_length(stack_type_t type)
{
    stack_t stack;
    stack_element_t e0 = 0, e1 = 10, e2 = 20, e3 = 30;

    stack_init(&stack, 5, type);

    CU_ASSERT_EQUAL(stack_length(stack), 0);
    stack_push(stack, e0);
    CU_ASSERT_EQUAL(stack_top(stack), e0);
    stack_push(stack, e1);
    CU_ASSERT_EQUAL(stack_top(stack), e1);
    stack_push(stack, e2);
    CU_ASSERT_EQUAL(stack_top(stack), e2);
    stack_push(stack, e3);
    CU_ASSERT_EQUAL(stack_top(stack), e3);
    CU_ASSERT_EQUAL(stack_length(stack), 4);

    stack_pop(stack);
    CU_ASSERT_EQUAL(stack_top(stack), e2);
    CU_ASSERT_EQUAL(stack_length(stack), 3);

    stack_push(stack, e3);
    CU_ASSERT_EQUAL(stack_top(stack), e3);
    CU_ASSERT_EQUAL(stack_length(stack), 4);

    CU_ASSERT_EQUAL(stack_pop(stack), e3);
    CU_ASSERT_EQUAL(stack_pop(stack), e2);
    CU_ASSERT_EQUAL(stack_pop(stack), e1);
    CU_ASSERT_EQUAL(stack_pop(stack), e0);
    CU_ASSERT_EQUAL(stack_length(stack), 0);

    stack_destroy(&stack);
}

static void
test_static_stack_push_pop_top_length(void)
{
    test_stack_push_pop_top_length(STATIC_STACK);
}

static void
test_dynamic_stack_push_pop_top_length(void)
{
    test_stack_push_pop_top_length(DYNAMIC_STACK);
}


static void
test_stack_is_empty_is_full(stack_type_t type)
{
    stack_t stack;
    stack_element_t e0 = 0, e1 = 10;

    stack_init(&stack, 2, type);

    CU_ASSERT_TRUE(stack_is_empty(stack));
    CU_ASSERT_FALSE(stack_is_full(stack));

    stack_push(stack, e0);

    CU_ASSERT_FALSE(stack_is_empty(stack));
    CU_ASSERT_FALSE(stack_is_full(stack));

    stack_push(stack, e1);

    CU_ASSERT_FALSE(stack_is_empty(stack));
    if (type == STATIC_STACK) {
        CU_ASSERT_TRUE(stack_is_full(stack));
    } else {
        CU_ASSERT_FALSE(stack_is_full(stack));
    }

    stack_destroy(&stack);
}

static void
test_static_stack_is_empty_is_full(void)
{
    test_stack_is_empty_is_full(STATIC_STACK);
}

static void
test_dynamic_stack_is_empty_is_full(void)
{
    test_stack_is_empty_is_full(DYNAMIC_STACK);
}


static void
test_stack_clear(stack_type_t type)
{
    stack_t stack;
    stack_element_t e0 = 0, e1 = 10;

    stack_init(&stack, 2, type);

    stack_push(stack, e0);
    stack_push(stack, e1);

    CU_ASSERT_EQUAL(stack_length(stack), 2);
    stack_clear(stack);
    CU_ASSERT_EQUAL(stack_length(stack), 0);

    stack_destroy(&stack);
}


static void
test_static_stack_clear(void)
{
    test_stack_clear(STATIC_STACK);
}

static void
test_dynamic_stack_clear(void)
{
    test_stack_clear(DYNAMIC_STACK);
}


static CU_TestInfo stack_tests[] = {
    {"static stack: init, destroy", test_static_stack_init_destroy},
    {"static stack: push, pop, top, length",
     test_static_stack_push_pop_top_length},
    {"static stack: is_empty, is_full", test_static_stack_is_empty_is_full},
    {"static stack: clear", test_static_stack_clear},

    {"dynamic stack: init, destroy", test_dynamic_stack_init_destroy},
    {"dynamic stack: push, pop, top, length",
     test_dynamic_stack_push_pop_top_length},
    {"dynamic stack: is_empty, is_full", test_dynamic_stack_is_empty_is_full},
    {"dynamic stack: clear", test_dynamic_stack_clear},

    CU_TEST_INFO_NULL
};

CU_TestInfo *
get_stack_tests(void)
{
    return stack_tests;
}
