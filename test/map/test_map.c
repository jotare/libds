#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "map/map.h"

#include "map/testconf.h"

int
init_map_suite(void)
{
    return 0;
}

int
cleanup_map_suite(void)
{
    return 0;
}

static void
test_map_init_destroy(map_type_t type)
{
    map_t map = NULL;

    map_init(&map, type);
    CU_ASSERT_PTR_NOT_NULL(map);

    map_destroy(&map);
    CU_ASSERT_PTR_NULL(map);
}

static void
test_open_hash_table_init_destroy(void)
{
    test_map_init_destroy(OPEN_HASH_TABLE_MAP);
}

static void
test_map_set_get_contains_delete(map_type_t type)
{
    map_t map = NULL;
    map_key_t k0 = 'A', k1 = 'F', k2 = 'Z';
    map_value_t v0 = 12, v1 = 63, v2 = 5, v3 = 104;
    map_value_t value;

    map_init(&map, type);

    /* Set a key-value pair and check it */

    CU_ASSERT_FALSE(map_contains(map, k0));
    map_set(map, k0, v0);
    CU_ASSERT_TRUE(map_contains(map, k0));

    map_get(map, k0, &value);
    CU_ASSERT_EQUAL(value, v0);

    /* Set multiple KV pairs */

    map_set(map, k0, v0);
    map_set(map, k1, v1);
    map_set(map, k2, v2);

    CU_ASSERT_TRUE(map_contains(map, k0));
    CU_ASSERT_TRUE(map_contains(map, k1));
    CU_ASSERT_TRUE(map_contains(map, k2));

    /* overwrite a value */

    map_set(map, k0, v3);
    map_get(map, k0, &value);
    CU_ASSERT_EQUAL(value, v3);

    /* delete keys */

    map_delete(map, k0);
    CU_ASSERT_FALSE(map_contains(map, k0));

    map_delete(map, k1);
    map_delete(map, k2);
    CU_ASSERT_FALSE(map_contains(map, k1));
    CU_ASSERT_FALSE(map_contains(map, k2));

    /* insert keys again */

    map_set(map, k0, v0);
    CU_ASSERT_TRUE(map_contains(map, k0));

    map_destroy(&map);
}

static void
test_open_hash_table_set_get_contains_delete(void)
{
    test_map_set_get_contains_delete(OPEN_HASH_TABLE_MAP);
}


static CU_TestInfo map_tests[] = {
    {"open hash table: init, destroy", test_open_hash_table_init_destroy},
    {"open hash table: set, get, contains, delete",
     test_open_hash_table_set_get_contains_delete},

    CU_TEST_INFO_NULL
};

CU_TestInfo *
get_map_tests(void)
{
    return map_tests;
}
