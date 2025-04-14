/**
 * \file test_cCounter.cpp
 * \brief Tester exercising test setup and tear down
 *
 */
#include <gtest/gtest.h>

#include "cCounter.h"


struct cCounter_test:public::testing::Test{
/* Fixture for cCounter_IncCounter()
==============================================================================*/
    virtual void SetUp() override {
        cCounter_InitCounter();
        std::cout << "==========Set up done==========" << std::endl;
    }
    virtual void TearDown() override {
        cCounter_DeInitCounter();
        std::cout << "==========Tear down done==========" << std::endl;
    }
};


/* Functions that require setup in advance
==============================================================================*/
TEST_F(cCounter_test, CounterSetUp){
    EXPECT_EQ(true, cCounter_IsCounterInited());
}

TEST_F(cCounter_test, Count123){
    EXPECT_EQ(0, cCounter_GetCount());
    cCounter_IncCounter();
    EXPECT_EQ(1, cCounter_GetCount());
    cCounter_IncCounter();
    EXPECT_EQ(2, cCounter_GetCount());
}

TEST_F(cCounter_test, Count1){
    cCounter_IncCounter();
    EXPECT_EQ(1, cCounter_GetCount());
}


