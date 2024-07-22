/**
 * @file regex.h
 * @author Alexan <nanfengnan@foxmail.com>
 * @brief hproxy hiredis
 *
 * Copyright (c) 2024 Alexan
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef HXY_HIREDIS_H
#define HXY_HIREDIS_H

#include <stdarg.h>

#include <hiredis/adapters/libuv.h>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include <uv.h>

/**
 * @brief Redis subscribe key work
 */
#define hxy_subcribe_str "subscribe"

/**
 * @brief Typedef redisAsyncContext redis_asyn_context
 */
typedef redisAsyncContext redis_asyn_context;

/**
 * @brief Rename hiredis asynchronized connect func
 * @param[in] addr The string format of ipv4 or ipv6 addr
 * @param[in] port The integer format of port
 * @return redis_asyn_context* if success, otherwise NULL
 */
#define hxy_asyn_connect(addr, port) \
	redisAsyncConnect(addr, port)

/**
 * @brief Rename hiredis asynchronized disconnect func
 * @param[in] context Hiredis context
 * @return none
 */
#define hxy_asyn_disconnect(context) \
	redisAsyncDisconnect(context)

/**
 * @brief Rename hiredis asynchronized command func
 * @param[in] context Pointer of redis_asyn_context
 * @param[in] cb Receive redis channel msg callback
 * @param[in] data Private Data for cb
 * @param[in] fmt Format for ...
 * @param[in] ... Variable length parameters
 * @return 0 if success, otherwise -1
 */
#define hxy_asyn_command(context, cb, data, fmt, ...) \
	redisAsyncCommand(context, cb, data, fmt, __VA_ARGS__)

/**
 * @brief Free asynchronized context
 * @param[in] context Pointer of redis_asyn_context
 * @return 0 if success, otherwise -1
 */
#define hxy_asyn_free(context) \
	redisAsyncFree(context)

/**
 * @brief Set asynchronized connect callback for context
 * @return 0 if success, otherwise -1
 */
#define hxy_set_asyn_connect_cb(context, cb) \
	redisAsyncSetConnectCallback(context, cb)

/**
 * @brief Set asynchronized disconnect callback for context
 * @return 0 if success, otherwise -1
 */
#define hxy_set_asyn_disconnect_cb(context, cb) \
	redisAsyncSetDisconnectCallback(context, cb)

/**
 * @brief Typedef redisLibuvEvents hxy_uv_events
 */
typedef redisLibuvEvents hxy_uv_events;

/**
 * @brief Attach uv_loop to context
 * @param[in] context Hiredis asynchronized context
 * @param[in] uv_loop Libuv context for every thread
 * @return 0 if success, otherwise -1
 */
#define hxy_uv_attach(context, uv_loop) \
	redisLibuvAttach(context, uv_loop)

#define hxy_uv_add_read(priv_data) \
	redisLibuvAddRead(priv_data)

#define hxy_uv_del_read(priv_data) \
	redisLibuvDelRead(priv_data)

#define hxy_uv_add_write(priv_data) \
	redisLibuvAddWrite(priv_data)

#define hxy_uv_del_write(priv_data) \
	redisLibuvDelWrite(priv_data)

#define hxy_uv_timer_close(handle) \
	on_timer_close(handle)
	
#define hxy_uv_handle_close(handle) \
	on_handle_close(handle)

#define hxy_uv_timeout(timer, status) \
	redisLibuvTimeout(timer, status)

#define hxy_uv_set_timeout(priv_data, tv) \
	redisLibuvSetTimeout(priv_data, tv)

#define hxy_uv_cleanup(priv_data) \
	redisLibuvCleanup(priv_data)

/**
 * @brief Subscribe redis channel
 * @param[in] context Hiredis asynchronized context
 * @param[in] channel Subscribe channel name or regex string
 * @param[in] cb      Handle asynchronized msg callback
 * @return 0 if success, otherwise -1
 *
 * @note channel and cb are not nullptr
 */
int hxy_subscribe_channel(redis_asyn_context *context,
	const char *channel, void (*cb)(redis_asyn_context* , void *, void *));


#endif
