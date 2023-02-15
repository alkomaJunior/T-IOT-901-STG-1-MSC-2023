#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

void test_example()
{
    int a = 27;
    TEST_ASSERT_EQUAL(a, 27);
}

int main( int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_example);
    UNITY_END();
}