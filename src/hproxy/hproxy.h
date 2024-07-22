/**
 * @file hproxy.h
 * @author Alexan <nanfengnan@foxmail.com>
 * @brief hproxy
 *
 * Copyright (c) 2024 Alexan
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef HIREDIS_PROXY_H__
#define HIREDIS_PROXY_H__

#include <stdint.h>
#include <stdbool.h>
#include "lib/zlog.h"
#include "lib/address.h"

#include <hiredis/hiredis.h>
#include <hiredis/async.h>

#include <hiredis/adapters/libuv.h>
#include <uv.h>

/*
 * The following headers are supposed to be included explicitly:
 * - hash_table.h
 * - metadata.h
 * - plugins_types.h
 * - plugins_exts.h
 */

/**
 * @mainpage About
 *
 * libyang is a library implementing processing of the YANG schemas and data modeled by the YANG language. The
 * library is implemented in C for GNU/Linux and provides C API.
 *
 * @section about-features Main Features
 *
 * - Support for pcre2 regex
 * - Support for numa user space memory manage
 * - Support for io multiplexing
 * - Support for coroutine schedule
 * - Support for redis msg distributions
 * - Support for builtin [hiredis](https://redis.io/lp/hiredis/)
 *
 * The current implementation version is v1.0.0
 *
 * @section about-license License
 *
 * Copyright (c) 2024 Alexan
 *
 * (The BSD 3-Clause License)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 */

#define DEFAULT_PORT 9999
#define DEFAULT_IP "127.0.0.1"

typedef struct hiredis_proxy_main {
	uint16_t port;
	char *ip;
	ip46_address_t addr;
	
	bool daemon;

	zlog_main_t zm;
	redisContext          *context;
	redisAsyncContext     *uv_context;
	uv_loop_t             *uv_loop;	
} hiredis_proxy_main_t;

void hiredis_uv_subscribe(const char *channel);
bool hiredis_uv_connect(void);
void hiredis_uv_cb(redisAsyncContext *c, void *reply, void *privdata);
void hiredis_uv_connect_cb(const redisAsyncContext *c, int status);
void hiredis_uv_disconnect_cb(const redisAsyncContext *c, int status);

void hproxy_get_main();
void hproxy_main_init(hiredis_proxy_main_t *hpm);
void hproxy_help_exit(int status);



#endif
