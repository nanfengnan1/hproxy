#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "hxy_hiredis.h"
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libuv.h>
#include <uv.h>

void test_msg_cb(redisAsyncContext *c, void *reply, void *privdata)
{
    redisReply *r = (redisReply *)reply;
    
    if (!r)
        return;

    if (r->type == REDIS_REPLY_ARRAY && r->elements == 3) {
        /*
         * msg type: r->element[0]
         * channel name: r->element[1]
         * msg data: r->element[2]
         */
        fprintf(stdout, "channel: %s, msg: %s\n", r->element[1]->str, r->element[2]->str);
    }   
}

void test_uv_subscribe(redisAsyncContext *context, const char *channel)
{
    if (!channel)
        return;

    redisAsyncCommand(context, test_msg_cb, NULL, "%s %s", "subscribe", channel);
}

void* pthread_start(void *arg)
{
    redisAsyncContext *context;
    uv_loop_t *uv_loop;

    uv_loop = uv_default_loop();
    if (!uv_loop) {
        fprintf(stderr, "Failed to get default UV loop\n");
        return NULL;
    }

    context = hxy_asyn_connect("127.0.0.1", 6379);
    if (context->err) {
        fprintf(stderr, "Redis connection error: %s\n", context->errstr);
        return NULL;
    }   

    if (hxy_uv_attach(context, uv_loop) < 0) {
        fprintf(stderr, "Failed to attach Redis to UV loop\n");
        redisAsyncFree(context);
        return NULL;
    }

#if 0
    test_uv_subscribe(context, "test_hproxy");
#else
	hxy_subscribe_channel(context, "test_hproxy", test_msg_cb);
#endif
    uv_run(uv_loop, UV_RUN_DEFAULT);

    redisAsyncFree(context); // Cleanup Redis context
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tid;

    pthread_create(&tid, NULL, pthread_start, NULL);
    pthread_join(tid, NULL);

    fprintf(stdout, "test uv and hiredis ending...\n");

    return 0;
}
