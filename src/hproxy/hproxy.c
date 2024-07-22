#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "config.h"
#include "hproxy.h"
#include "lib/ketopt.h"
#include "lib/regex.h"

char progname[256];
const char *ipv4_regex = "\\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b";

hiredis_proxy_main_t h_proxy_main, *hpm = &h_proxy_main;

static const ko_longopt_t longopts[] = {
	{ "daemon", ko_no_argument, 'd' },
	{ "help", ko_no_argument, 'h'}, 	
	{ "proxy_addr", ko_required_argument, 'A' },
	{ "proxy_port", ko_required_argument, 'P' },
	{ "version", ko_no_argument, 'v'},
	{ NULL, 0, 0 }
};

static const char cmd_helpstr[] = {
	"  -h, --help         Display this help and exit\n"
	"  -v, --version      Print program version\n"
	"  -d, --daemon       Runs in daemon mode\n"
	"  -M, --module       Load specified module\n"
	"  -A, --proxy_addr   Load specified module\n"
	"  -P, --proxy_port   Load specified module\n"	
};

#if 0
void hiredis_uv_subscribe(const char *channel)
{
	uint32_t channel_len;
	char *channel_str;

	if (!channel)
		return;

	channel_len = strlen(channel) + strlen("SUBSCRIBE") + 2;
	channel_str = calloc(1, channel_len);
	snprintf(channel_str, channel_len, "%s %s", "SUBSCRIBE", channel);
	
	redisAsyncCommand(hpm->uv_context, hiredis_uv_cb, NULL, channel_str);
}

bool hiredis_uv_connect(void)
{
	hpm->uv_loop = uv_default_loop();

	hpm->uv_context = redisAsyncConnect("localhost", hpm->port);
    if (hpm->uv_context->err) {
		
		zlog_err("asyn connect to redis: %s", hpm->uv_context->errstr);
        return false;
    }

	redisLibuvAttach(hpm->uv_context, hpm->uv_loop);
    redisAsyncSetConnectCallback(hpm->uv_context, hiredis_uv_connect_cb);
    redisAsyncSetDisconnectCallback(hpm->uv_context, hiredis_uv_disconnect_cb);

	// frr_daemon_sub_channel(frr_protoname);

	uv_run(hpm->uv_loop, UV_RUN_DEFAULT);

	return true;
}

void hiredis_uv_cb(redisAsyncContext *c, void *reply, void *privdata)
{
    redisReply *r = reply;
	
    if (!reply) 
		return;

	if (r->type == REDIS_REPLY_ARRAY && r->elements == 3) {

		/*
		 * msg type: r->element[0]
		 * tun name: r->element[1]
		 * msg data: r->element[2]
		 */
		zlog_debug("subscribe channel: %s, msg: %s", r->element[0]->str, r->element[2]->str);

		// event_add_event(master, hiredis_match_event, XSTRDUP(MTYPE_HIREDIS, r->element[2]->str), 0/*default none*/, &hpm->event);
	}
}

void hiredis_uv_connect_cb(const redisAsyncContext *c, int status)
{
    if (status != REDIS_OK) {

		// flog_err(EC_LIB_HIREDIS_INIT, "%s: asyn connect error %s", __func__, c->errstr);
        return;
    }

	zlog_debug("hiredis asynchronized connects to redis");
}

void hiredis_uv_disconnect_cb(const redisAsyncContext *c, int status)
{
    if (status != REDIS_OK) {

		flog_err(EC_LIB_HIREDIS_INIT, "%s: asyn disconnect error %s", __func__, c->errstr);
        return;
    }

	zlog_debug("hiredis asynchronized disconnects to redis");
}
#endif 

void* pthread_start(void *arg)
{
	
	return NULL;
}

void hproxy_main_init(hiredis_proxy_main_t *hpm)
{
	memset(hpm, 0, sizeof(hiredis_proxy_main_t));
	hpm->port = DEFAULT_PORT;
	hpm->ip = DEFAULT_IP;
	hpm->daemon = false;
	zlog_init(&hpm->zm, LOG_DEBUG);	
}

void hproxy_help_exit(int status)
{
	FILE *target = status ? stderr : stdout;

	/* switch-predict */
	if (PREDICT_FALSE(status))
		fprintf(stderr, "Invalid options.\n\n");

	fprintf(target, "Usage: %s [OPTION...]\n\n%s\n", PACKAGE, cmd_helpstr);
	exit(status);
}

void hproxy_name_and_version()
{
	fprintf(stdout, "%s version %s\n", PACKAGE, VERSION);
	exit(0);
}

int main(int argc, char *argv[])
{			
  	ketopt_t opt = KETOPT_INIT;
  	int c = -1;
	while ((c = ketopt(&opt, argc, argv, 1, "dhA:P:v", longopts)) >= 0) {
		switch (c) {
		case 'd':

			printf("test daemon\n");
			break;
		case 'h':

			hproxy_help_exit(0);
			break;
		case 'A':

			/* only support ipv4 regex at current */
			if (!hporxy_regex_match_once(ipv4_regex, opt.arg)) {				
				printf("ipv4: %s format error\n", opt.arg);
				exit(-1);
			}

			break;
		case 'P':
			
			printf("port: %s\n", opt.arg);
			break;
		case 'v':

			hproxy_name_and_version();
			break;
		}
	}	

	hproxy_main_init(hpm);

	return 0;
}
