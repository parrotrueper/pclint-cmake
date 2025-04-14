/**
 * \file test_util_DateTime.cpp
 * \brief Tester exercising parameterised tests
 *
 */
#include <gtest/gtest.h>

#include "util_DateTime.h"

/* Algorithm, testing a variety of parameters
==============================================================================*/

class LeapYearParamTestFixture:public testing::TestWithParam<std::tuple<uint32_t, bool>>{};

TEST_P(LeapYearParamTestFixture, VerifyLeapYears){

    uint32_t u32Year = std::get<0>(GetParam());
    bool bExpected   = std::get<1>(GetParam());
    EXPECT_EQ(util_DateTime_IsLeapYear(u32Year), bExpected);
}

INSTANTIATE_TEST_SUITE_P(
    LeapYearTests,
    LeapYearParamTestFixture,
    ::testing::Values(
        std::make_tuple(1881, false ),
        std::make_tuple( 500, false ),
        std::make_tuple( 711, false ),
        std::make_tuple(1910, false ),
        std::make_tuple(1966, false ),
        std::make_tuple(1989, false ),
        std::make_tuple(2023, false ),
        std::make_tuple(1804, true  ),
        std::make_tuple(1920, true  ),
        std::make_tuple(1968, true  ),
        std::make_tuple(1976, true  ),
        std::make_tuple(2032, true  )
    ));

/* https://www.sandordargo.com/blog/2019/04/24/parameterized-testing-with-gtest */
