
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "hlib.h"
#include "hxy_mem.h"
#include "hxy_hiredis.h"

int hxy_subscribe_channel(redis_asyn_context *context,
	const char *channel, void (*cb)(redis_asyn_context* , void *, void *))
{
	if (PREDICT_TRUE(!channel || !cb))
		return -1;

	return hxy_asyn_command(context, cb, NULL, "%s %s", hxy_subcribe_str, channel);	
}
