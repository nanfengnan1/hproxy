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


#ifndef REGEX_H
#define REGEX_H

#include <stdbool.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

/**
 * @brief Regex compile for multip string match
 * @param[in] pattern_str Regex pattern string
 * @return NULL if failure, otherwise pcre2_code pointer
 */
pcre2_code* hproxy_regex_compile(const char *pattern_str);

/**
 * @brief Regex through re to match subject_str
 *        never to free re
 * @param[in] re Regex string context
 * @param[in] subject_str Object string to match
 * @return true if success, otherwise false
 */
bool hproxy_regex_match(pcre2_code *re, const char *subject_str);

/**
 * @brief free re context
 * @param[in] re Regex string context
 */
void hporxy_regex_release(pcre2_code *re);

/**
 * @brief regex match for the compile and match of single string
 * @param[in] pattern Regex pattern string
 * @param[in] subject Object match string
 * @return true if success, otherwise false
 */
bool hporxy_regex_match_once(const char *pattern, const char *subject);

#endif
