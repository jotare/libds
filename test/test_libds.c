#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "list/testconf.h"
#include "stack/testconf.h"
#include "queue/testconf.h"
#include "set/testconf.h"
#include "map/testconf.h"
#include "graph/testconf.h"


int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_TestInfo
        *list_tests = get_list_tests(),
        *stack_tests = get_stack_tests(),
        *queue_tests = get_queue_tests(),
        *set_tests = get_set_tests(),
        *map_tests = get_map_tests(),
        *priority_queue_tests = get_priority_queue_tests(),
        *graph_tests = get_graph_tests();

    CU_SuiteInfo suites[] = {
        {"list", init_list_suite, cleanup_list_suite, NULL, NULL, list_tests},
        {"stack", init_stack_suite, cleanup_stack_suite, NULL, NULL, stack_tests},
        {"queue", init_queue_suite, cleanup_queue_suite, NULL, NULL, queue_tests},
        {"set", init_set_suite, cleanup_set_suite, NULL, NULL, set_tests},
        {"map", init_map_suite, cleanup_map_suite, NULL, NULL, map_tests},
        {"priority_queue", init_priority_queue_suite, cleanup_priority_queue_suite, NULL, NULL, priority_queue_tests},
        {"graph", init_graph_suite, cleanup_graph_suite, NULL, NULL, graph_tests},
        CU_SUITE_INFO_NULL
    };

    if (CU_register_suites(suites) != CUE_SUCCESS) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
