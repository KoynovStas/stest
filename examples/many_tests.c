#include "stest.h"




TEST(test_1)
{
    TEST_PASS();
}



TEST(test_2)
{
    TEST_SKIP();
}



TEST(test_3)
{
    TEST_FAIL();
}



ptest_func tests[] =
{
    test_1,
    test_2,
    test_3,
};



MAIN_TESTS(tests)
