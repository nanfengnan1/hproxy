#include "zlog.h"

/*
 * did't any libc call, will lead to 
 *		ldd libhiproxy.so
 *      statically linked
 * in fact, it will still use
*/

void zlog_init(zlog_main_t *zm, int level)
{
	zm->level = level;
}
