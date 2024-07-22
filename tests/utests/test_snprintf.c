
#include <string.h>
#include <stdio.h>

#include "utest.h"

static_inline void test_snprintf();

static_inline void test_snprintf()
{
	char *str = "hello world!";
	
	int len = strlen(str);
	char buf[len + 1];
	buf[len] = 0xff;

	snprintf(buf, len + 1, "%s", str);

	assert_int_not_equal(buf[len], 0xff);
}

int main(int argc,  char *argv[])
{
	const struct CMUnitTest tests[] = {
        UTEST(test_snprintf),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

