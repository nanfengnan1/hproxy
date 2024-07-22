
#include "ketopt.h"
#include "utest.h"

static_inline int test_kopt_case(int argc, char **argv);
static_inline void test_kopt();

#define test_cases 10
static int test_argc[] = {2, 2, 2, 2, 3, 3, 3, 3, 2, 2};

static char* test_argv[][test_cases] = {
	{ "utest_kopt", "-d" },
	{ "utest_kopt", "--daemon" },
	{ "utest_kopt", "-h" },
	{ "utest_kopt", "--help" },
	{ "utest_kopt", "-A", "127.0.0.1" },
	{ "utest_kopt", "--proxy_addr", "127.0.0.1" },
	{ "utest_kopt", "-P", "9999" },
	{ "utest_kopt", "--proxy_port", "9999" },
	{ "utest_kopt", "-v" },	
	{ "utest_kopt", "--version" },
	{ NULL }
};

static ko_longopt_t test_longopts[] = {
	{ "daemon", ko_no_argument, 'd' },
	{ "help", ko_no_argument, 'h'}, 	
	{ "proxy_addr", ko_required_argument, 'A' },
	{ "proxy_port", ko_required_argument, 'P' },
	{ "version", ko_no_argument, 'v'},
	{ NULL, 0, 0 }
};

static_inline int test_kopt_case(int argc, char **argv)
{
  	ketopt_t opt = KETOPT_INIT;
  	int c = -1, flags = 0;
	while ((c = ketopt(&opt, argc, argv, 1, "dhA:P:v", test_longopts)) >= 0) {
		switch (c) {
		case 'd':

			flags = 1;
			break;
		case 'h':

			flags = 1;			
			break;
		case 'A':

			assert_string_equal(opt.arg, "127.0.0.1");
			flags = 1;			
			break;
		case 'P':

			assert_string_equal(opt.arg, "9999");
			flags = 1;			
			break;
		case 'v':

			flags = 1;		
			break;
		}
	}

	return flags;
}

static_inline void test_kopt()
{	
	int i;

	for (i = 0; i < test_cases && test_argv[i][0]; ++i) {
		
		assert_int_equal(1, test_kopt_case(test_argc[i], test_argv[i]));
	}
}

int main(int argc, char *argv[])
{
	const struct CMUnitTest tests[] = {
        unit_test(test_kopt),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);	
}

