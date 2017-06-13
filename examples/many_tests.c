#include "stest.h"




TEST(test_pass)
{
    TEST_PASS(NULL);
}



TEST(test_pass2)
{
    TEST_PASS("a message for pass");
}



TEST(test_skip)
{
    TEST_SKIP(NULL);
}



TEST(test_skip2)
{
    TEST_SKIP("a message for skip");
}



TEST(test_fail)
{
    TEST_FAIL(NULL);
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



MAIN_TESTS(tests)
