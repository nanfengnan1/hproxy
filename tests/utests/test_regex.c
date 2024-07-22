
#include "regex.h"
#include "utest.h"

static const char *ipv4_regex = "\\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b";

static const char *ipv4_success_cases[] = {
	"0.0.0.0",      // minimum
	"0.0.0.1",
	"0.0.0.255",
	"0.0.1.0",
	"0.1.0.0",
	"255.255.255.255",  // maximum
	"255.0.0.0",    // byte border
	"0.255.0.0",
	"0.0.255.0",
	"0.0.0.255",
	"1.0.0.0",      // single border
	"0.1.0.0",
	"0.0.1.0",
	"0.0.0.1",
	"1.1.1.1",      // fixed border
	"255.255.0.255",
	"192.168.0.1",	
	NULL
};

static const char *ipv4_fail_cases[] = {
	"256.0.0.0",    // overflow
	"0.256.0.0",
	"0.0.256.0",
	"0.0.0.256",
	"192.168.1",    // lack of addr
	"192.168",
	"192",
	"192.168.1.a",  // invalid
	"",             // nullptr
	"192..168.1",   // invalid format
	NULL
};

static_inline void test_regex_match();

static_inline void test_regex_match()
{
	int i;
	pcre2_code *re = NULL;

	re = hproxy_regex_compile(ipv4_regex);
	assert_non_null(re);

	for (i = 0; ipv4_success_cases[i]; ++i) {
		assert_int_equal(hproxy_regex_match(re, ipv4_success_cases[i]), 1);
	}


	for (i = 0; ipv4_fail_cases[i]; ++i) {
		assert_int_equal(hproxy_regex_match(re, ipv4_fail_cases[i]), 0);
	}

	hporxy_regex_release(re);	
}

int main(int argc,  char *argv[])
{
	const struct CMUnitTest tests[] = {
        UTEST(test_regex_match),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
