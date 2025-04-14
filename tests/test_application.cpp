/**
 * \file test_Main.cpp
 * \brief Tester exercising testing of private functions
 *
 */
#include <gtest/gtest.h>
#include "application.h"

struct test_Main : public ::testing::Test {
    virtual void SetUp(){application_tick(true);}
};

TEST_F(test_Main, DoesItRun){
    ASSERT_EQ(1, application_getCount());
    application_tick(false);
    ASSERT_NE(1, application_getCount());
}

