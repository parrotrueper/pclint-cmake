/**
 * \file test_2_cCounter.cpp
 * \brief Tester exercising suite fixtures
 *
 */
#include <gtest/gtest.h>

#include "cCounter.h"


struct cCounter_test2:public::testing::Test{
/* Suite Fixture for cCounter_IncCounter()
==============================================================================*/
    static void SetUpTestSuite(){
        cCounter_InitCounter();
        cCounter_IncCounter();
        std::cout << "==========Set up done==========" << std::endl;
    }
    static void TearDownTestSuite() {
        cCounter_DeInitCounter();
        std::cout << "==========Tear down done==========" << std::endl;
    }
};


/* Functions that require setup in advance
==============================================================================*/
TEST_F(cCounter_test2, CounterSetUp){
    EXPECT_EQ(true, cCounter_IsCounterInited());
}

TEST_F(cCounter_test2, Count23){
    EXPECT_EQ(1, cCounter_GetCount());
    cCounter_IncCounter();
    EXPECT_EQ(2, cCounter_GetCount());
    cCounter_IncCounter();
    EXPECT_EQ(3, cCounter_GetCount());
}
TEST_F(cCounter_test2, Count4){
    cCounter_IncCounter();
    EXPECT_EQ(4, cCounter_GetCount());
}


