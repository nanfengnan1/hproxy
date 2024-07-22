/**
 * @file zlog.h
 * @author Alexan <nanfengnan@foxmail.com>
 * @brief hproxy zlog
 *
 * Copyright (c) 2024 Alexan
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef ZLOG_H
#define ZLOG_H

#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

typedef enum {
	LOG_DEBUG = 0,
	LOG_INFO,
	LOG_NOTICE,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL
} zlog_type_t;

typedef struct {
	int level;
} zlog_main_t;

#define zlog_log(lm, level, format, ...) \
do { \
    assert(lm); \
    fprintf(stdout, "[%s:%s:%lu] " format "\n", __FILE__, __FUNCTION__, (unsigned long)__LINE__, ##__VA_ARGS__); \
} while (0)

#if 0
#define zlog_debug(lm, fmt, ...)  zlog_log(lm, LOG_DEBUG, fmt, __VA_ARGS__)
#define zlog_info(lm, fmt, ...)   zlog_log(lm, LOG_INFO, fmt, __VA_ARGS__)
#define zlog_notice(lm, fmt, ...) zlog_log(lm, LOG_NOTICE, fmt, __VA_ARGS__)
#define zlog_warn(lm, fmt, ...)   zlog_log(lm, LOG_WARNING, fmt, __VA_ARGS__)
#define zlog_err(lm, fmt, ...)    zlog_log(lm, LOG_ERROR, fmt, __VA_ARGS__)
#define zlog_fatal(lm, fmt, ...)  zlog_log(lm, LOG_FATAL, fmt, __VA_ARGS__)
#else
#define zlog_debug(lm, fmt, ...)  fprintf(stdout, fmt, ##__VA_ARGS__)
#define zlog_info(lm, fmt, ...)   fprintf(stdout, fmt, ##__VA_ARGS__)
#define zlog_notice(lm, fmt, ...) fprintf(stdout, fmt, ##__VA_ARGS__)
#define zlog_warn(lm, fmt, ...)   fprintf(stdout, fmt, ##__VA_ARGS__)
#define zlog_err(lm, fmt, ...)    fprintf(stdout, fmt, ##__VA_ARGS__)
#define zlog_fatal(lm, fmt, ...)  fprintf(stdout, fmt, ##__VA_ARGS__)
#endif

void zlog_init(zlog_main_t *zm, int level);

#endif
