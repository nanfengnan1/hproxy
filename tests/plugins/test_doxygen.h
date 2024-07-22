/**
 * @file test_doxygen.h
 * @author Alexan <nanfengnan@foxmail.com>
 * @date 2024/21/7
 * @brief test how to use doxyen for C header file
 *
 * @note this file will teach you how to use doxygen annotate
 *       please refer to mannual or offical document for more details
 *
 * Copyright (c) 2024 Alexan
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef TEST_DOXYGEN_H
#define TEST_DOXYGEN_H

/**
 * @defgroup test_doxygen group
 * This is a description of test_doxygen group.
 * More detailed information about the group can be included here.
 */

/*
 * @note common comments and did't genearte into doc file
 */

/**
 * @note genearte comments into doc file
 */

/**
 * @brief test name len
 */
#define TEST_NAME_LEN 64

/**
 * @enum test_enum
 * @brief Types for test_enum
 */
typedef enum test_enum {
	TEST_A, /**< enum A */
	TEST_B, /**< enum B */
	TEST_C  /**< enum C */
} test_enum;

/**
 * @enum test_enum_no_typedef
 * @brief No typedef enum
 */
enum test_enum_no_typedef {
	TEST_A_N, /**< enum A_N */
	TEST_B_N, /**< enum B_N */
	TEST_C_N  /**< enum C_N */
};

/**
 * @struct test_struct
 * @brief Types for test_struct
 * @note
 *     only for test struct
 */
typedef struct test_struct {
	int age;             /**< age */
	/* flags */
	unsigned char flags; /**< age flags */
	char name[];         /**< name zero array */
} test_struct;

/**
 * @struct test_no_struct
 * @brief No typedef struct
 */
struct test_no_struct {
	int age_n;             /**< age n */
	unsigned char flags_n; /**< age flags n */
	char name_n[];           /**< name zero array n */
};

/**
 * @union test_union
 * @brief Types for test_union
 */
typedef union test_union {
	int age;                  /**< age */
	unsigned char sex:1;      /**< bit sex for mal and femal*/
	unsigned char flags:1;    /**< bit flags */
	unsigned char reserved;   /**< bit field reserved 6 bits */
	char name[TEST_NAME_LEN]; /**< name zero array */
} test_union;

/**
 * @union test_no_union
 * @brief No typedef union
 */
union test_no_union {
	int age_n;                  /**< age_n */
    unsigned char sex_n:1;      /**< bit sex_n for mal and femal*/
    unsigned char flags_n:1;    /**< bit flags_n */
    unsigned char reserved_n;   /**< bit field_n reserved 6 bits */
    char name_n[TEST_NAME_LEN]; /**< name_n zero array */
};

/**
 * @fn test_add
 * @brief Test calculate the summary of a and b operand
 * @param[in] a The operand one
 * @param[in] b The operand two
 * @return sum
 */
int test_add(int a, int b);

/**
 * @brief Test calculate the summary of a and b operand
 *             and summary will be stored in sum pointer
 * @param[in] a The operand one
 * @param[in] b The operand two
 * @param[out] sum The sum of a and b
 * @return 0 if success, otherwise -1
 */
int test_add_success(int a, int b, long *sum);

/**
 * @deprecated This function will be deprected in next version
 * @brief Test calculate the summary of a and b operand
 *             and summary will be stored in sum pointer
 * @param[in] a The operand one
 * @param[in] b The operand two
 * @param[out] sum The sum of a and b
 * @return 0 if success, otherwise -1
 */
int test_add_success_deprected(int a, int b, long *sum);

/**
 * @brief Test attention annotate
 * @attention Test attention annotate
 */
void test_attention();

/**
 * @brief Test note annotate
 * @note Test warning annotate
 */
void test_note();

/**
 * @brief Test warning annotate
 * @warning Test warning annotate
 */
void test_warning();

/**
 * @brief Test retval
 * @retval 0 success
 * @retval 1 pending
 * @retval 2 scheduling
 * @retval -1 failure
 */
int test_retval();

int see_var;
/**
 * @brief Test see annotate
 * @see see_var test_enum:A
 * @see test_struct:age
 * @see test_union:name
 */
void test_see();

/**
 * @brief Test see annotate
 * @see test_enum:A
 */
void test_see_enum();

/**
 * @brief Test see annotate
 * @see test_struct:age
 */
void test_see_struct();

/**
 * @brief Test see annotate
 * @see test_union:name
 */
void test_see_union();

/**
 * @brief Test join in test_doxygen group
 * @ingroup test_doxygen
 */
void test_a();

/**
 * @brief Test join in test_doxygen group
 * @ingroup test_doxygen
 */
void test_b();

/**
 * @brief Test join in test_doxygen group
 * @ingroup test_doxygen
 */
void test_c();

/**
 * @brief Test join in test_doxygen group
 * @ingroup test_doxygen
 */
void test_d();

#endif
