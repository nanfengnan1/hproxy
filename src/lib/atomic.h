/**
 * @file regex.h
 * @author Alexan <nanfengnan@foxmail.com>
 * @brief hproxy regex express
 *
 * Copyright (c) 2024 Alexan
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef ATOMIC_H
#define ATOMIC_H

#ifndef HAVE_STDATOMIC_H
#error cmake checks for atomic functions were not properly run
#endif

#if defined(HAVE_STDATOMIC_H)
#include <stdatomic.h>

/* These are available in gcc, but not in stdatomic */
#define atomic_add_fetch(PTR, VAL) __atomic_add_fetch ((PTR), (VAL),    \
                                                       __ATOMIC_SEQ_CST)
#define atomic_add_fetch_explicit __atomic_add_fetch

#define atomic_sub_fetch(PTR, VAL) __atomic_sub_fetch ((PTR), (VAL),    \
                                                       __ATOMIC_SEQ_CST)
#define atomic_sub_fetch_explicit __atomic_sub_fetch

#define atomic_and_fetch(PTR, VAL) __atomic_and_fetch ((PTR), (VAL),    \
                                                       __ATOMIC_SEQ_CST)
#define atomic_and_fetch_explicit __atomic_and_fetch

#define atomic_or_fetch(PTR, VAL) __atomic_or_fetch ((PTR), (VAL),    \
                                                       __ATOMIC_SEQ_CST)
#define atomic_or_fetch_explicit __atomic_or_fetch

#define atomic_xor_fetch(PTR, VAL) __atomic_xor_fetch ((PTR), (VAL),    \
                                                       __ATOMIC_SEQ_CST)
#define atomic_xor_fetch_explicit __atomic_xor_fetch
#else /* !HAVE_STDATOMIC_H */
#error no std atomic functions and do nothing wrapper...
#endif

#endif
