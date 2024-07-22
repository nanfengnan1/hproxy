/* Use the unit test allocators */
#define UNIT_TESTING 1

#include "utest.h"

static int setup(void **state)
{
    int *answer = malloc(sizeof(int));

    assert_non_null(answer);
    *answer = 42;

    *state = answer;

    return 0;
}

static int teardown(void **state) {
    free(*state);

    return 0;
}

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state)
{
    (void) state;
}

/* A test case that does check if an int is equal. */
static void int_test_success(void **state)
{
    int *answer = *state;

    assert_int_equal(*answer, 42);
	print_message("%s", "hello world!\n");
}

int main(int argc, char *argv[])
{
    const struct CMUnitTest tests[] = {
        UTEST(null_test_success),
        UTEST(int_test_success, setup, teardown),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
