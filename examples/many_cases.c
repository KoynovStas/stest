#include "stest.h"




TEST(test_pass)
{
    TEST_PASS(NULL);
}



TEST(test_pass2)
{
    TEST_PASS("a message for pass");
}



TEST(test_for_32bit)
{
    if(sizeof(void*) == 4)
        TEST_PASS(NULL);
    else
        TEST_SKIP("Skip, system is not 32-bit");
}


TEST(test_for_64bit)
{
    if(sizeof(void*) == 8)
        TEST_PASS(NULL);
    else
        TEST_SKIP("Skip, system is not 64-bit");
}



TEST(test_skip)
{
    TEST_SKIP("a message for skip");
}



TEST(test_fail)
{
    TEST_FAIL("a message for fail");
}



stest_func tests[] =
{
    test_pass,
    test_pass2,

    test_for_32bit,
    test_for_64bit,

    test_skip,

    test_fail,
};



TEST_CASE(case1, tests, NULL, NULL, NULL)
TEST_CASE(case2, tests, NULL, NULL, NULL)
TEST_CASE(case3, tests, NULL, NULL, NULL)



struct test_case_t *cases[] =
{
    &case1,
    &case2,
    &case3
};



MAIN_CASES(cases)
