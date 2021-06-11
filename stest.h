/*
 * stest.h
 *
 *
 * version 1.0
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

#include <stddef.h>  //size_t





/*
 * STest uses the stest_printf macro as a function to print,
 * if the macro is not defined, we use the standard clib function from stdio.h.
 * If you are using STest on an embedded system perhaps you have your own
 * function or less resource-intensive one like xprintf (http://elm-chan.org/fsw/strf/xprintf.html)
 * Then uncomment the definition and add your function.
 * The function must have signature like printf and
 * must support printing for formats: %s %d %u
 */

//#define  stest_printf  xprintf

#ifndef stest_printf  //use printf from libc
    #include <stdio.h>
    #define  stest_printf  printf
#endif



#define STEST_CONSOLE_COLOR   1  //1 - on  0 - off; common support color print
#define STEST_PASS_MSG_COLOR  0  //1 - on  0 - off; color print for user message
#define STEST_SKIP_MSG_COLOR  0  //1 - on  0 - off; color print for user message
#define STEST_FAIL_MSG_COLOR  1  //1 - on  0 - off; color print for user message

#define STEST_PASS_MORE_INFO  0  //1 - on  0 - off; show more info (file:line)
#define STEST_SKIP_MORE_INFO  0  //1 - on  0 - off; show more info (file:line)
#define STEST_FAIL_MORE_INFO  1  //1 - on  0 - off; show more info (file:line)



enum test_status_t
{
    TEST_STATUS_PASS,
    TEST_STATUS_SKIP,
    TEST_STATUS_FAIL,

    TEST_STATUS_NUM   //it's not status, used like size of array
};



struct test_info_t
{
    const char *file_name;
    const char *func_name;
    int         line_num;

    int         status;

    const char *msg;
};


struct test_case_t;

typedef  struct test_info_t (*stest_func)      (struct test_case_t *test_case);
typedef  void               (*stest_init_func) (struct test_case_t *test_case);
typedef  void               (*stest_clean_func)(struct test_case_t *test_case);



struct test_case_t
{
    //public
    void             *data;        //user data
    stest_init_func   init;        //user func for init
    stest_clean_func  clean;       //user func for clean

    //private
    const char   *file_name;
    const char   *case_name;
    int           line_num;

    size_t        count_tests;
    stest_func   *tests;

    unsigned int  status_cnt[TEST_STATUS_NUM];
};



#define STEST_SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))


#define TEST_CASE(_name, _tests, _data, _init, _clean) \
    struct test_case_t _name = {                       \
   _data, _init, _clean,                               \
   __FILE__, #_name, __LINE__,                         \
   STEST_SIZE_OF_ARRAY(_tests), _tests,                \
   {0, 0, 0} };



#define TEST(name) static struct test_info_t name(struct test_case_t *test_case)



__attribute__((used))
static inline struct test_info_t get_test_info( const char         *file_name,
                                                const char         *func_name,
                                                int                 line_num,
                                                int                 status,
                                                const char         *msg,
                                                struct test_case_t *test_case)
{
    test_case->status_cnt[status]++;
    struct test_info_t test_info = {file_name, func_name, line_num, status, msg};
    return test_info;
}

#define TEST_PASS(msg)  return get_test_info(__FILE__, __func__, __LINE__, TEST_STATUS_PASS, msg, test_case)
#define TEST_SKIP(msg)  return get_test_info(__FILE__, __func__, __LINE__, TEST_STATUS_SKIP, msg, test_case)
#define TEST_FAIL(msg)  return get_test_info(__FILE__, __func__, __LINE__, TEST_STATUS_FAIL, msg, test_case)



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
    enum {TEST_ASSERT_CONCAT(TEST_ASSERT_CONCAT(level_, __INCLUDE_LEVEL__), \
          TEST_ASSERT_CONCAT(_static_assert_on_line_, __LINE__)) = 1/(int)(!!(expr)) }




#define STEST_COLOR_TEXT_NORMAL "\033[0m"
#define STEST_COLOR_TEXT_RED    "\033[31m"
#define STEST_COLOR_TEXT_GREEN  "\033[32m"
#define STEST_COLOR_TEXT_YELLOW "\033[33m"



static inline void stest_print_title(const char *first, struct test_case_t *test_case, const char *last)
{
    stest_printf("%s", first);

    if(test_case && test_case->case_name)
        stest_printf(" of %s from: %s:%d", test_case->case_name,
                                           test_case->file_name,
                                           test_case->line_num);

    stest_printf("%s", last);
}



static inline void stest_print_header(struct test_case_t *test_case)
{
    stest_print_title("\n\n---------- Start testing", test_case, " ----------");
}



static inline void stest_print_footer(struct test_case_t *test_case)
{
    stest_print_title("========== Finished testing", test_case, " ==========\n\n");
}



static inline void stest_print_msg(const char *msg, const char *color)
{
    if(color && STEST_CONSOLE_COLOR)
        stest_printf("%s%s" STEST_COLOR_TEXT_NORMAL, color, msg);
    else
        stest_printf("%s", msg);
}



static void stest_print_info(struct test_info_t *test_info, int more_info, const char *color_msg)
{
    stest_printf("  %s", test_info->func_name);

    if(more_info)
        stest_printf("  in file: %s:%d", test_info->file_name,
                                         test_info->line_num);

    if(test_info->msg)
    {
        stest_printf("  msg: ");
        stest_print_msg(test_info->msg, color_msg);
    }
}



struct print_status_inf
{
    const char *prefix;
    const char *prefix_color;
    const char *msg_color;
    int         more_info;
};



static void stest_print_status(struct test_info_t *test_info)
{
    static const struct print_status_inf data[TEST_STATUS_NUM] = {
        {
            "\nPASS: ",
            STEST_COLOR_TEXT_GREEN,
            STEST_PASS_MSG_COLOR ? STEST_COLOR_TEXT_GREEN : NULL,
            STEST_PASS_MORE_INFO,
        },
        {
            "\nSKIP: ",
            STEST_COLOR_TEXT_YELLOW,
            STEST_SKIP_MSG_COLOR ? STEST_COLOR_TEXT_YELLOW : NULL,
            STEST_SKIP_MORE_INFO,
        },
        {
            "\nFAIL: ",
            STEST_COLOR_TEXT_RED,
            STEST_FAIL_MSG_COLOR ? STEST_COLOR_TEXT_RED : NULL,
            STEST_FAIL_MORE_INFO,
        },
    };

    const struct print_status_inf *inf = &data[test_info->status];

    stest_print_msg(inf->prefix, inf->prefix_color);
    stest_print_info(test_info, inf->more_info, inf->msg_color);
}



static inline void stest_print_counter(const char *text, const char *color, unsigned int counter)
{
    stest_printf("%s", (counter && STEST_CONSOLE_COLOR) ? color : "");
    stest_printf(" %u %s", counter, text);
    stest_printf(STEST_COLOR_TEXT_NORMAL);
}



static void stest_print_totals(unsigned int *status_cnt)
{
    stest_printf("\n\nTotal:");

    stest_print_counter("passed," , STEST_COLOR_TEXT_GREEN , status_cnt[TEST_STATUS_PASS]);
    stest_print_counter("skipped,", STEST_COLOR_TEXT_YELLOW, status_cnt[TEST_STATUS_SKIP]);
    stest_print_counter("failed," , STEST_COLOR_TEXT_RED   , status_cnt[TEST_STATUS_FAIL]);
    stest_print_counter("total\n" , ""                     , status_cnt[TEST_STATUS_PASS]+
                                                             status_cnt[TEST_STATUS_SKIP]+
                                                             status_cnt[TEST_STATUS_FAIL]);
}



static unsigned int run_case(struct test_case_t *test_case)
{
    struct test_info_t test_info;
    size_t i;


    stest_print_header(test_case);


    for(i = 0; i < test_case->count_tests; ++i)
    {
        if( test_case->init )
            test_case->init(test_case);

        test_info = test_case->tests[i](test_case); //run test

        if( test_case->clean )
            test_case->clean(test_case);


        stest_print_status(&test_info);
    }


    stest_print_totals(test_case->status_cnt);
    stest_print_footer(test_case);

    return test_case->status_cnt[TEST_STATUS_FAIL];
}



__attribute__((unused))
static inline unsigned int run_cases(struct test_case_t *test_cases[], size_t count_cases)
{
    size_t i;
    unsigned int total_cnt[TEST_STATUS_NUM] = {0, 0, 0};


    for(i = 0; i < count_cases; ++i)
    {
       total_cnt[TEST_STATUS_FAIL] += run_case(test_cases[i]);

       total_cnt[TEST_STATUS_PASS] += test_cases[i]->status_cnt[TEST_STATUS_PASS];
       total_cnt[TEST_STATUS_SKIP] += test_cases[i]->status_cnt[TEST_STATUS_SKIP];

    }

    if( count_cases > 1 )
    {
        stest_print_totals(total_cnt);
        stest_print_footer(NULL);
    }

    return total_cnt[TEST_STATUS_FAIL];
}



#define MAIN_CASE(test_case)   int main(void) { return (int)run_case(&test_case); }

#define MAIN_CASES(test_cases) int main(void) { return (int)run_cases(test_cases, STEST_SIZE_OF_ARRAY(test_cases)); }

#define MAIN_TESTS(tests)                         \
    TEST_CASE(test_case, tests, NULL, NULL, NULL) \
    MAIN_CASE(test_case)





#endif //STEST_HEADER
