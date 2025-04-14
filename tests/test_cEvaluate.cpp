/**
 * \file test_cEvaluate.cpp
 * \brief Tester exercising floating point comparisons,
 * bitwise comparisons, disabling tests, skipping tests,
 * death tests
 *
 */
#include <gtest/gtest.h>
#include <iomanip>
#include <bitset>

#include "cEvaluate.h"

static bool bDebugEn = true; /* check prints work */

struct cEvaluate_test:public::testing::Test{
    virtual void SetUp() override {
    }
    virtual void TearDown() override {
    }
};

TEST_F(cEvaluate_test, PlatformSizeOfFloat){
    EXPECT_EQ(32, cEvaluate_PlatformSizeOfFloat());
}

TEST_F(cEvaluate_test, PlatformSizeOfDouble){
    EXPECT_EQ(64, cEvaluate_PlatformSizeOfDouble());
}

TEST_F(cEvaluate_test, PlatformSizeOfLongDouble){
    EXPECT_EQ(128, cEvaluate_PlatformSizeOfLongDouble());
}

/* compare 2 numbers bitwise
==============================================================================*/
TEST_F(cEvaluate_test, DoTheseBitsMatch){
    uint8_t u8Result = 0x55;
    uint8_t u8Expected = 0x5A;

    std::bitset<8> bitResult   = std::bitset<8>(u8Result);
    std::bitset<8> bitExpected = std::bitset<8>(u8Expected);

    EXPECT_NE(bitExpected,bitResult);
}

/* checking floating point numbers
==============================================================================*/
TEST_F(cEvaluate_test, GetPi32bit){
    if ( bDebugEn ){
        std::cout << std::setprecision (31) << cEvaluate_GetPi32bit() << std::endl;
    }
    EXPECT_FLOAT_EQ(cEvaluate_GetPi32bit(), (float32_t)(3.1415926535897966));
}

TEST_F(cEvaluate_test, GetPi64bit){
    if ( bDebugEn ){
        std::cout << std::setprecision (63) << cEvaluate_GetPi64bit() << std::endl;
    }
    EXPECT_DOUBLE_EQ(cEvaluate_GetPi64bit(), 3.14159265358979311599796346854418516);
}
/* check floating point numbers with an acceptable error
==============================================================================*/
TEST_F(cEvaluate_test, Pi32bitErrorTolerancePass){
    if ( bDebugEn ){
        std::cout << std::setprecision (31) << cEvaluate_GetPi32bit() << std::endl;
    }
    EXPECT_NEAR(cEvaluate_GetPi32bit(), 3.1415927410125731, 0.0000000000000001);
}

TEST_F(cEvaluate_test, Pi64bitErrorTolerancePass){
    if ( bDebugEn ){
        std::cout << std::setprecision (63) << cEvaluate_GetPi64bit() << std::endl;
    }
    EXPECT_NEAR(cEvaluate_GetPi64bit(), 3.1415926535897932, 0.0000000000000001);
}

/* Disabling tests that fail while you fix your bug
==============================================================================*/
TEST_F(cEvaluate_test, DISABLED_Pi32bitErrorToleranceFail){ /* to re-enable remove "DISABLED_" */
    if ( bDebugEn ){
        std::cout << std::setprecision (31) << cEvaluate_GetPi32bit() << std::endl;
    }
    EXPECT_NEAR(cEvaluate_GetPi32bit(), 3.1415926535897935, 0.0000000000000001);
}

TEST_F(cEvaluate_test, Pi64bitErrorToleranceFail){
    GTEST_SKIP() << "This is how to SKIP a test, can also be used in a fixture."; /* to re-enable remove this line */
    if ( bDebugEn ){
        std::cout << std::setprecision (63) << cEvaluate_GetPi64bit() << std::endl;
    }
    EXPECT_NEAR(cEvaluate_GetPi64bit(), 3.1415926535897935, 0.0000000000000001);
}

/* Function abuse that will cause a segmentation fault
=============================================================================*/
TEST_F(cEvaluate_test, SegmentationFault){
    uint8_t u8Dummy=0x55;
    EXPECT_EQ("0x55", std::string(reinterpret_cast<const char*>(cEvaluate_PrintAddrValue(&u8Dummy))));
    EXPECT_DEATH(std::string(cEvaluate_PrintAddrValue(0)), "");
}

/* Function abuse that will cause a core dump
=============================================================================*/
TEST_F(cEvaluate_test, CoreDump){
    EXPECT_EQ(2,cEvaluate_Division(2,1));
    EXPECT_DEATH(cEvaluate_Division(1,0), "");
}
