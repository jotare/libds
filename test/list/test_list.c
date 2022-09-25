#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include <inttypes.h>
#include <stdio.h>

#include "list/list.h"

#include "list/testconf.h"


int
init_list_suite(void)
{
    return 0;
}

int
cleanup_list_suite(void)
{
    return 0;
}


static void
test_list_init_destroy(list_type_t type)
{
    list_t list = NULL;

    list_init(&list, 10, type);
    CU_ASSERT_PTR_NOT_NULL(list);

    list_destroy(&list);
    CU_ASSERT_PTR_NULL(list);
}

static void
test_array_list_init_destroy(void)
{
    test_list_init_destroy(ARRAY_LIST);
}

static void
test_linked_list_init_destroy(void)
{
    test_list_init_destroy(LINKED_LIST);
}

static void
test_doubly_linked_list_init_destroy(void)
{
    test_list_init_destroy(DOUBLY_LINKED_LIST);
}


static void
test_list_get_insert_remove(list_type_t type)
{
    list_t list;
    list_element_t e0 = 0, e1 = 1, e2 = 2, e3 = 3;

    list_init(&list, 5, type);

    // insert elements
    CU_ASSERT_EQUAL(list_length(list), 0);
    list_insert(list, 0, e0);
    list_insert(list, 1, e1);
    list_insert(list, 2, e2);
    list_insert(list, 3, e3);
    CU_ASSERT_EQUAL(list_length(list), 4);

    // get list values
    CU_ASSERT_EQUAL(list_get(list, 0), e0);
    CU_ASSERT_EQUAL(list_get(list, 1), e1);
    CU_ASSERT_EQUAL(list_get(list, 2), e2);
    CU_ASSERT_EQUAL(list_get(list, 3), e3);

    // remove first
    list_remove(list, 0);
    CU_ASSERT_EQUAL(list_length(list), 3);

    // insert in the middle
    list_insert(list, 2, e0);

    // insert in illegal position
    CU_ASSERT_EQUAL(list_insert(list, 8, e0), -1);

    // check list elements
    CU_ASSERT_EQUAL(list_get(list, 0), e1);
    CU_ASSERT_EQUAL(list_get(list, 1), e2);
    CU_ASSERT_EQUAL(list_get(list, 2), e0);
    CU_ASSERT_EQUAL(list_get(list, 3), e3);

    list_destroy(&list);
}

static void
test_array_list_get_insert_remove(void)
{
    test_list_get_insert_remove(ARRAY_LIST);
}

static void
test_linked_list_get_insert_remove(void)
{
    test_list_get_insert_remove(LINKED_LIST);
}

static void
test_doubly_linked_list_get_insert_remove(void)
{
    test_list_get_insert_remove(DOUBLY_LINKED_LIST);
}


static void
test_list_first_last(list_type_t type)
{
    list_t list;
    list_element_t e0 = 0, e1 = 1, e2 = 2;

    list_init(&list, 3, type);

    list_insert(list, 0, e0);
    list_insert(list, 1, e1);
    list_insert(list, 2, e2);

    CU_ASSERT_EQUAL(list_first(list), e0);
    CU_ASSERT_EQUAL(list_last(list), e2);

    list_destroy(&list);
}

static void
test_array_list_first_last(void)
{
    test_list_first_last(ARRAY_LIST);
}

static void
test_linked_list_first_last(void)
{
    test_list_first_last(LINKED_LIST);
}

static void
test_doubly_linked_list_first_last(void)
{
    test_list_first_last(DOUBLY_LINKED_LIST);
}


static void
test_list_append_prepend(list_type_t type)
{
    list_t list;
    list_element_t a = 0, b = 1, c = 2;

    list_init(&list, 5, type);

    list_append(list, a);
    CU_ASSERT_EQUAL(list_get(list, 0), a);
    list_append(list, b);
    CU_ASSERT_EQUAL(list_get(list, 1), b);
    list_prepend(list, c);
    CU_ASSERT_EQUAL(list_get(list, 0), c);

    list_destroy(&list);
}

static void
test_array_list_append_prepend(void)
{
    test_list_append_prepend(ARRAY_LIST);
}

static void
test_linked_list_append_prepend(void)
{
    test_list_append_prepend(LINKED_LIST);
}

static void
test_doubly_linked_list_append_prepend(void)
{
    test_list_append_prepend(DOUBLY_LINKED_LIST);
}


static void
test_list_is_empty_is_full(list_type_t type)
{
    list_t list;
    list_element_t e0 = 0, e1 = 1;

    list_init(&list, 2, type);

    CU_ASSERT_TRUE(list_is_empty(list));
    CU_ASSERT_FALSE(list_is_full(list));

    list_insert(list, 0, e0);

    CU_ASSERT_FALSE(list_is_empty(list));
    CU_ASSERT_FALSE(list_is_full(list));

    list_insert(list, 1, e1);

    CU_ASSERT_FALSE(list_is_empty(list));
    if (type == LINKED_LIST || type == DOUBLY_LINKED_LIST) {
        CU_ASSERT_FALSE(list_is_full(list));
    } else {
        CU_ASSERT_TRUE(list_is_full(list));
    }

    list_destroy(&list);
}

static void
test_array_list_is_empty_is_full(void)
{
    test_list_is_empty_is_full(ARRAY_LIST);
}

static void
test_linked_list_is_empty_is_full(void)
{
    test_list_is_empty_is_full(LINKED_LIST);
}

static void
test_doubly_linked_list_is_empty_is_full(void)
{
    test_list_is_empty_is_full(DOUBLY_LINKED_LIST);
}


static void
test_list_clear(list_type_t type)
{
    list_t list;
    list_element_t e0 = 0, e1 = 10;

    list_init(&list, 2, type);

    list_insert(list, 0, e0);
    list_insert(list, 1, e1);

    CU_ASSERT_EQUAL(list_length(list), 2);
    list_clear(list);
    CU_ASSERT_EQUAL(list_length(list), 0);

    list_destroy(&list);
}

static void
test_array_list_clear(void)
{
    test_list_clear(ARRAY_LIST);
}

static void
test_linked_list_clear(void)
{
    test_list_clear(LINKED_LIST);
}

static void
test_doubly_linked_list_clear(void)
{
    test_list_clear(DOUBLY_LINKED_LIST);
}


static int
cmp(list_element_t a, list_element_t b)
{
    if (a < b)
        return -1;
    else if (a == b)
        return 0;
    else
        return 1;
}

void
test_list_locate(list_type_t type)
{
    list_t list;
    list_element_t e0 = 0, e1 = 10, e2 = 20;

    list_init(&list, 5, type);
    list_insert(list, 0, e0);
    list_insert(list, 1, e1);
    list_insert(list, 2, e2);

    CU_ASSERT_EQUAL(list_locate(list, 30, cmp), -1);
    CU_ASSERT_EQUAL(list_locate(list, e0, cmp), 0);
    CU_ASSERT_EQUAL(list_locate(list, e1, cmp), 1);

    list_destroy(&list);
}

static void
test_array_list_locate(void)
{
    test_list_locate(ARRAY_LIST);
}

static void
test_linked_list_locate(void)
{
    test_list_locate(LINKED_LIST);
}

static void
test_doubly_linked_list_locate(void)
{
    test_list_locate(DOUBLY_LINKED_LIST);
}


static CU_TestInfo list_tests[] = {
    {"array list: init, destroy", test_array_list_init_destroy},
    {"array list: get, insert, remove", test_array_list_get_insert_remove},
    {"array list: first, last", test_array_list_first_last},
    {"array list: append, prepend", test_array_list_append_prepend},
    {"array list: is_empty, is_full", test_array_list_is_empty_is_full},
    {"array list: clear", test_array_list_clear},
    {"array list: locate", test_array_list_locate},

    {"linked list: init, destroy", test_linked_list_init_destroy},
    {"linked list: get, insert, remove", test_linked_list_get_insert_remove},
    {"linked list: first, last", test_linked_list_first_last},
    {"linked list: append, prepend", test_linked_list_append_prepend},
    {"linked list: is_empty, is_full", test_linked_list_is_empty_is_full},
    {"linked list: clear", test_linked_list_clear},
    {"linked list: locate", test_linked_list_locate},

    {"doubly linked list: init, destroy",
     test_doubly_linked_list_init_destroy},
    {"doubly linked list: get, insert, remove",
     test_doubly_linked_list_get_insert_remove},
    {"doubly linked list: first, last", test_doubly_linked_list_first_last},
    {"doubly linked list: append, prepend",
     test_doubly_linked_list_append_prepend},
    {"doubly linked list: is_empty, is_full",
     test_doubly_linked_list_is_empty_is_full},
    {"doubly linked list: clear", test_doubly_linked_list_clear},
    {"doubly linked list: locate", test_doubly_linked_list_locate},

    CU_TEST_INFO_NULL
};

CU_TestInfo *
get_list_tests(void)
{
    return list_tests;
}
