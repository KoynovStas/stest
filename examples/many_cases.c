#include "stest.h"




TEST(test_pass)
{
    TEST_PASS();
}



TEST(test_pass2)
{
    TEST_PASS("a message for pass");
}



TEST(test_skip)
{
    TEST_SKIP();
}



TEST(test_skip2)
{
    TEST_SKIP("a message for skip");
}



TEST(test_fail)
{
    TEST_FAIL();
}



TEST(test_fail2)
{
    TEST_FAIL("a message for fail");
}



ptest_func tests[] =
{
    test_pass,
    test_pass2,

    test_skip,
    test_skip2,

    test_fail,
    test_fail2,
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