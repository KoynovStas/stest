/*
 * stest.h
 *
 *
 * version 0.0
 *
 *
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2017, Koynov Stas - skojnov@yandex.ru
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef STEST_HEADER
#define STEST_HEADER





enum test_status_t
{
    STATUS_PASS,
    STATUS_SKIP,
    STATUS_FAIL
};



struct test_info_t
{
    const char *file_name;
    const char *func_name;
    int         line_num;

    int         status;

    const char *msg;
};



#define TEST(name) struct test_info_t name(void *data)



#define TEST_PASS(msg)  return (struct test_info_t) {__FILE__, __func__, __LINE__, STATUS_PASS, msg}
#define TEST_SKIP(msg)  return (struct test_info_t) {__FILE__, __func__, __LINE__, STATUS_SKIP, msg}
#define TEST_FAIL(msg)  return (struct test_info_t) {__FILE__, __func__, __LINE__, STATUS_FAIL, msg}



#define TEST_ASSERT2(expr, msg)  if( !(expr) ) TEST_FAIL(msg)
#define TEST_ASSERT(expr)  TEST_ASSERT2(expr, NULL)


/*
 * For GCC 4.6 or higher, in C++ you can use a standard right static_assert(exp, msg)
 * in *.c and in *.h files.
 * For GCC 4.6 is required to add CFLAGS += -std="c++0x"
 * Simple C (gcc) have not static_assert.
 * A lot of variants, it is the most simple and intuitive
 * It can be used in *.c and in *.h files.
 * (macros that use function style can be used in *.c files only)
 *
 * Disadvantages: you can not be set msg to display the console when compiling
 *
 * Example:
 *
 * TEST_STATIC_ASSERT( sizeof(char) == 1)  //good job
 * TEST_STATIC_ASSERT( sizeof(char) != 1)  //You will get a compilation error
*/
#define TEST_ASSERT_CONCAT_(a, b) a##b
#define TEST_ASSERT_CONCAT(a, b) TEST_ASSERT_CONCAT_(a, b)
#define TEST_STATIC_ASSERT(expr) \
    enum { TEST_ASSERT_CONCAT(assert_line_, __LINE__) = 1/(int)(!!(expr)) }



typedef  struct test_info_t (*ptest_func)(void *data);


struct test_case_t;

typedef  void  (*pinit_func)(struct test_case_t *test_case);
typedef  void  (*pclean_func)(struct test_case_t *test_case);



struct test_case_t
{
    const char *file_name;
    const char *case_name;
    int         line_num;
    size_t      count_tests;

    ptest_func *tests;

    void       *data;

    pinit_func  init;
    pclean_func clean;


    //private
    size_t count_pass;
    size_t count_skip;
    size_t count_fail;
};



#define  SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))


#define TEST_CASE(_name, _tests, _data, _init, _clean) \
    struct test_case_t _name = {                       \
    __FILE__, #_name, __LINE__,                        \
    SIZE_OF_ARRAY(_tests), _tests,                     \
   _data, _init, _clean, 0, 0, 0 };



static void print_header(const char *title)
{
    printf("\n\n---------- Start testing");

    if(title)
        printf(" of %s", title);

    printf(" ----------");
}





#endif //STEST_HEADER
