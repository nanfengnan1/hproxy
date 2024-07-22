/**
 * @file regex.h
 * @author Alexan <nanfengnan@foxmail.com>
 * @brief hproxy memory manage
 *
 * Copyright (c) 2024 Alexan
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef HXY_MEM_H
#define HXY_MEM_H

#include <stdlib.h>

#define hxy_oom() abort()
#define hxy_free(ptr) free(ptr)

#define hxy_malloc(size)     \
do {                         \
	void *p = malloc(size);  \
	if (!p)                  \
		hxy_oom();			 \
	return p;                \
} while (0);

#define hxy_calloc(count, size)    \
do {                               \
	void *p = calloc(count, size); \
	if (!p)                        \
		hxy_oom();                 \
	return p;                      \
} while (0);

#define hxy_recalloc(ptr, size)    \
do {                               \
	void *p = realloc(ptr, size);  \
	if (!p)                        \
		hxy_oom();                 \
	return p;                      \
} while(0);

#endif
