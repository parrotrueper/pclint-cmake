#include <gtest/gtest.h>

#include "template_example.h"
#include <stdint.h>

using namespace testing;

/*
 * Tests
 */

TEST(testTemplateExample, CanMultiplyPositiveValues)
{
    int32_t result = templateExample_multiply(5, 3);

    EXPECT_TRUE(result == 15);
}
