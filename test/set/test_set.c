#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <inttypes.h>

#include "set/set.h"

#include "set/testconf.h"


int init_set_suite(void) { return 0; }
int cleanup_set_suite(void) { return 0; }


static void test_set_init_destroy(set_type_t type) {
    set_t set = NULL;
    set_init(&set, 10, type);
    CU_ASSERT_NOT_EQUAL(set, NULL);

    set_destroy(&set);
    CU_ASSERT_EQUAL(set, NULL);
}

static void test_bit_vector_set_init_destroy(void) {
    test_set_init_destroy(BIT_VECTOR_SET);
}

static void test_linked_list_set_init_destroy(void) {
    test_set_init_destroy(LINKED_LIST_SET);
}

static void test_set_insert_member_delete_clear(set_type_t type) {
    set_t set;
    set_element_t e0 = 0, e1 = 80, e2 = 23;
    set_init(&set, 200, type);

    CU_ASSERT_FALSE(set_member(set, e0));
    set_insert(set, e0);
    CU_ASSERT_TRUE(set_member(set, e0));

    CU_ASSERT_FALSE(set_member(set, e1));
    set_insert(set, e1);
    CU_ASSERT_TRUE(set_member(set, e1));

    CU_ASSERT_FALSE(set_member(set, e2));
    set_insert(set, e2);
    CU_ASSERT_TRUE(set_member(set, e2));

    // delete smallest element
    set_delete(set, e0);
    CU_ASSERT_FALSE(set_member(set, e0));

    // delete a big non member
    set_element_t not_member = 153;
    CU_ASSERT_EQUAL(set_delete(set, not_member), 0);

    set_insert(set, e0);
    CU_ASSERT_TRUE(set_member(set, e0));

    // delete biggest element
    set_delete(set, e1);
    CU_ASSERT_FALSE(set_member(set, e1));

    set_delete(set, e0);
    set_delete(set, e2);
    set_delete(set, e1);
    set_insert(set, e0);
    set_insert(set, e2);
    set_insert(set, e1);
    CU_ASSERT_TRUE(set_member(set, e0));
    CU_ASSERT_TRUE(set_member(set, e1));
    CU_ASSERT_TRUE(set_member(set, e2));

    set_clear(set);
    CU_ASSERT_FALSE(set_member(set, e0));
    CU_ASSERT_FALSE(set_member(set, e1));
    CU_ASSERT_FALSE(set_member(set, e2));

    set_destroy(&set);
}

static void test_bit_vector_set_insert_member_delete_clear(void) {
    test_set_insert_member_delete_clear(BIT_VECTOR_SET);
}

static void test_linked_list_set_insert_member_delete_clear(void) {
    test_set_insert_member_delete_clear(LINKED_LIST_SET);
}

static void test_set_length_is_empty(set_type_t type) {
    set_t set;
    set_element_t e0 = 12, e1 = 79, e2 = 99;

    set_init(&set, 100, type);
    CU_ASSERT_TRUE(set_is_empty(set));
    CU_ASSERT_EQUAL(set_length(set), 0);

    set_insert(set, e0);
    CU_ASSERT_FALSE(set_is_empty(set));
    CU_ASSERT_EQUAL(set_length(set), 1);

    set_insert(set, e0);
    CU_ASSERT_EQUAL(set_length(set), 1);

    set_delete(set, e0);
    CU_ASSERT_TRUE(set_is_empty(set));
    CU_ASSERT_EQUAL(set_length(set), 0);

    set_insert(set, e1);
    set_insert(set, e2);
    CU_ASSERT_FALSE(set_is_empty(set));
    CU_ASSERT_EQUAL(set_length(set), 2);

    set_clear(set);
    CU_ASSERT_TRUE(set_is_empty(set));
    CU_ASSERT_EQUAL(set_length(set), 0);
}

static void test_bit_vector_set_length_is_empty(void) {
    test_set_length_is_empty(BIT_VECTOR_SET);
}

static void test_linked_list_set_length_is_empty(void) {
    test_set_length_is_empty(LINKED_LIST_SET);
}

static void test_set_union_intersection_difference(set_type_t type) {
    set_t a, b, c;
    set_element_t e0 = 12, e1 = 79, e2 = 99;

    set_init(&a, 100, type);
    set_init(&b, 100, type);
    set_init(&c, 100, type);

    set_insert(a, e0);
    set_insert(a, e1);
    set_insert(b, e1);
    set_insert(b, e2);

    set_union(a, b, &c);
    CU_ASSERT_TRUE(set_member(c, e0));
    CU_ASSERT_TRUE(set_member(c, e1));
    CU_ASSERT_TRUE(set_member(c, e2));

    set_intersection(a, b, &c);
    CU_ASSERT_FALSE(set_member(c, e0));
    CU_ASSERT_TRUE(set_member(c, e1));
    CU_ASSERT_FALSE(set_member(c, e2));

    set_difference(a, b, &c);
    CU_ASSERT_TRUE(set_member(c, e0));
    CU_ASSERT_FALSE(set_member(c, e1));
    CU_ASSERT_FALSE(set_member(c, e2));

    set_destroy(&a);
    set_destroy(&b);
    set_destroy(&c);
}

static void test_bit_vector_set_union_intersection_difference(void) {
    test_set_union_intersection_difference(BIT_VECTOR_SET);
}

static void test_linked_list_set_union_intersection_difference(void) {
    test_set_union_intersection_difference(LINKED_LIST_SET);
}


static CU_TestInfo set_tests[] = {
    {"bit vector set: init, destroy", test_bit_vector_set_init_destroy},
    {"bit vector set: insert, member, delete, clear", test_bit_vector_set_insert_member_delete_clear},
    {"bit vector set: length, is_empty", test_bit_vector_set_length_is_empty},
    {"bit vector set: union, intersection, difference", test_bit_vector_set_union_intersection_difference},

    {"linked list set: init, destroy", test_linked_list_set_init_destroy},
    {"linked list set: insert, member, delete, clear", test_linked_list_set_insert_member_delete_clear},
    {"linked list set: length, is_empty", test_linked_list_set_length_is_empty},
    {"linked list set: union, intersection, difference", test_linked_list_set_union_intersection_difference},

    CU_TEST_INFO_NULL
};

CU_TestInfo *get_set_tests(void) {
    return set_tests;
}
