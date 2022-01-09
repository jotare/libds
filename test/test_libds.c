#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "list/testconf.h"
#include "stack/testconf.h"


int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_TestInfo
        *list_tests = get_list_tests(),
        *stack_tests = get_stack_tests();

    CU_SuiteInfo suites[] = {
        {"list", init_list_suite, cleanup_list_suite, NULL, NULL, list_tests},
        {"stack", init_stack_suite, cleanup_stack_suite, NULL, NULL, stack_tests},
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
