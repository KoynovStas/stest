#include "stest.h"




TEST(test_1)
{
    TEST_PASS(NULL);
}



ptest_func tests[] =
{
    test_1,
};



MAIN_TESTS(tests)
