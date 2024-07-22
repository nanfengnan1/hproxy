#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define HAVE_STDATOMIC_H

#include "atomic.h"
#include "utest.h"

static_inline void test_atomic_store_and_load();
// static_inline void test_atomic_store_and_load_explicit();
static_inline void test_atomic_exchange();
// static_inline void test_atomic_exchange_explicit();
static_inline void test_atomic_cas();
static_inline void test_atomic_fetch_op();
static_inline void test_atomic_op_fetch();
static_inline void* test_pthread_start(void *arg);
static_inline void test_atomic_multip_thread();

static_inline void test_atomic_store_and_load()
{
	atomic_int int_atom = ATOMIC_VAR_INIT(10);

	int old_value = atomic_load(&int_atom);

	assert_int_equal(old_value, 10);

	atomic_store(&int_atom, 12);

	old_value = atomic_load(&int_atom);

	assert_int_equal(old_value, 12);
}

static_inline void test_atomic_exchange()
{
	atomic_int int_atom = ATOMIC_VAR_INIT(0);

	assert_int_equal(atomic_load(&int_atom), 0);

	int old_value = atomic_exchange(&int_atom, 12);

	assert_int_equal(old_value, 0);
	assert_int_equal(atomic_load(&int_atom), 12);
}

static_inline void test_atomic_cas()
{
	atomic_int int_atom = ATOMIC_VAR_INIT(22);

	int expected = atomic_load(&int_atom);

	int equal = atomic_compare_exchange_strong(&int_atom, &expected, 100);

	assert_int_equal(equal, 1);
	assert_int_equal(atomic_load(&int_atom), 100);

	expected = 101;
	equal = atomic_compare_exchange_strong(&int_atom, &expected, 200);;

	assert_int_equal(equal, 0);
	assert_int_equal(expected, 100);
	assert_int_equal(atomic_load(&int_atom), 100);
}

static_inline void test_atomic_fetch_op()
{
	atomic_int int_atom = ATOMIC_VAR_INIT(22);

	int old_value = atomic_fetch_add(&int_atom, 100);
	assert_int_equal(old_value, 22);
	assert_int_equal(atomic_load(&int_atom), 122);

	old_value = atomic_fetch_sub(&int_atom, 22);
	assert_int_equal(old_value, 122);
	assert_int_equal(atomic_load(&int_atom), 100);

	old_value = atomic_fetch_and(&int_atom, 36);
	assert_int_equal(old_value, 100);
	assert_int_equal(atomic_load(&int_atom), 36);

	old_value = atomic_fetch_or(&int_atom, 64);
	assert_int_equal(old_value, 36);
	assert_int_equal(atomic_load(&int_atom), 100);

	old_value = atomic_fetch_xor(&int_atom, 100);
	assert_int_equal(old_value, 100);
	assert_int_equal(atomic_load(&int_atom), 0);

}

static_inline void test_atomic_op_fetch()
{
	atomic_int int_atom = ATOMIC_VAR_INIT(100);

	int new_value = atomic_add_fetch(&int_atom, 100);
	assert_int_equal(new_value, 200);
	assert_int_equal(atomic_load(&int_atom), 200);
	
	new_value = atomic_sub_fetch(&int_atom, 100);
	assert_int_equal(new_value, 100);
	assert_int_equal(atomic_load(&int_atom), 100);

	new_value = atomic_and_fetch(&int_atom, 36);
	assert_int_equal(new_value, 36);
	assert_int_equal(atomic_load(&int_atom), 36);

	new_value = atomic_or_fetch(&int_atom, 64);
	assert_int_equal(new_value, 100);
	assert_int_equal(atomic_load(&int_atom), 100);

	new_value = atomic_xor_fetch(&int_atom, 100);
	assert_int_equal(new_value, 0);
	assert_int_equal(atomic_load(&int_atom), 0);
}

static atomic_int sum_atom;
static int sum;

static_inline void* test_pthread_start(void *arg)
{
	int i;
	for (i = 0; i < 1e4; i++) {
		++sum;
		atomic_add_fetch(&sum_atom, 1);
	}

	return NULL;
}

static_inline void test_atomic_multip_thread()
{
	int i;
#define MAX_PTHREAD 100
	pthread_t tid[MAX_PTHREAD];

	for (i = 0; i < MAX_PTHREAD; ++i) {
		pthread_create(&tid[i], NULL, test_pthread_start, NULL);
	}

	for (i = 0; i < MAX_PTHREAD; ++i) {
		pthread_join(tid[i], NULL);
	}

	assert_int_equal(atomic_load(&sum_atom), 1e6);
	assert_in_range(sum, 0, 1e6);
}

int main(int argc, char *argv[])
{
    const struct CMUnitTest tests[] = {
        UTEST(test_atomic_store_and_load),
		UTEST(test_atomic_exchange),
		UTEST(test_atomic_cas),
		UTEST(test_atomic_fetch_op),
		UTEST(test_atomic_op_fetch),
		UTEST(test_atomic_multip_thread),
    };

	cmocka_set_message_output(CM_OUTPUT_SUBUNIT);

    return cmocka_run_group_tests(tests, NULL, NULL);
}
