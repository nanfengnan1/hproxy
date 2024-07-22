#ifndef UTEST_H
#define UTEST_H

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <cmocka.h>

#define static_inline static inline

/**
 * @brief Generic utest's setup
 */
int utest_setup(void **state)
{
    return 0;
}

/**
 * @brief macro to include generic utest's setup into the test-specific setup.
 *
 * Place at the beginning of the test-specific setup
 */
#define UTEST_SETUP \
    assert_int_equal(0, utest_setup(state))

/**
 * @brief Generic utest's teardown
 */
int utest_teardown(void **state)
{
    *state = NULL;

    return 0;
}

/**
 * @brief macro to include generic utest's teardown into the test-specific teardown.
 *
 * Place at the end of the test-specific teardown
 */
#define UTEST_TEARDOWN \
    assert_int_equal(0, utest_teardown(state))

/**
 * @brief Internal macro for utest setup with test-specific setup and teardown
 */
#define _UTEST_SETUP_TEARDOWN(FUNC, SETUP, TEARDOWN) \
    cmocka_unit_test_setup_teardown(FUNC, SETUP, TEARDOWN)

/**
 * @brief Internal macro for utest setup with test-specific setup and generic teardown
 */
#define _UTEST_SETUP(FUNC, SETUP) \
    cmocka_unit_test_setup_teardown(FUNC, SETUP, utest_teardown)

/**
 * @brief Internal macro for utest setup with generic setup and teardown
 */
#define _UTEST(FUNC) \
    cmocka_unit_test_setup_teardown(FUNC, utest_setup, utest_teardown)

/**
 * @brief Internal helper macro to select _UTEST* macro according to the provided parameters.
 */
#define _GET_UTEST_MACRO(_1, _2, _3, NAME, ...) NAME

/**
 * @brief Macro to specify test function using utest environment. Macro has variadic parameters
 * to provide test-specific setup/teardown functions:
 *
 * UTEST(test_func) - only implicit setup and teardown functions are used
 * UTEST(test_func, setup) - implicit teardown but own setup
 * UTEST(test_func, setup, teardown) - both setup and teardown are test-specific
 */
#define UTEST(...) \
    _GET_UTEST_MACRO(__VA_ARGS__, _UTEST_SETUP_TEARDOWN, _UTEST_SETUP, _UTEST, DUMMY)(__VA_ARGS__)
#endif
