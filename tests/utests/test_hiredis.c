
#include "hxy_hiredis.h"
#include "utest.h"

#define TEST_IP "127.0.0.1"
#define TEST_PORT 6379
#define CHANNEL "test_hproxy"

void test_hiredis_msg_cb(redis_asyn_context *context , void *reply, void *privdata)
{
	// TODO nothing
}

static_inline void test_hiredis()
{
	redis_asyn_context *context = hxy_asyn_connect(TEST_IP, TEST_PORT);
	assert_non_null(context);

	assert_int_equal(0, hxy_subscribe_channel(context, CHANNEL, test_hiredis_msg_cb));
	hxy_asyn_disconnect(context);

	/* did'nt clear old address */
	assert_non_null(context);
}

int main(int argc,  char *argv[])
{
	const struct CMUnitTest tests[] = {
        UTEST(test_hiredis),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

