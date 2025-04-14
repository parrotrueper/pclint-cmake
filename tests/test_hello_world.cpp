/**
 * \file test_HelloWorld.cpp
 * \brief Tester exercising API printing to stdout, string checks,
 * and various C array comparisons
 *
 */
#include <gmock/gmock.h>

#include <string.h>

#include "hello_world.h"

using namespace std;
using namespace testing;

struct HelloWorld_test : public ::testing::Test {
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

/* Misc tests
==============================================================================*/
TEST_F(HelloWorld_test, PassNullPointer){

    bool bResult = hello_world_api(0,1);

    EXPECT_EQ(false, bResult);
}

TEST_F(HelloWorld_test, PassZeroLength){

    uint8_t u8VirtualScreen;
    bool bResult = hello_world_api(&u8VirtualScreen,0);

    EXPECT_EQ(false, bResult);
}

TEST_F(HelloWorld_test, ScreenSizeOne){

    uint8_t u8VirtualScreen;
    bool bResult;

    bResult = hello_world_api(&u8VirtualScreen, sizeof(u8VirtualScreen));

    EXPECT_EQ(false, bResult);
    EXPECT_EQ(u8VirtualScreen, 0);
}

TEST_F(HelloWorld_test, ScreenTooSmall){

    uint8_t u8VirtualScreen[6];
    bool bResult;

    bResult = hello_world_api(&u8VirtualScreen[0], sizeof(u8VirtualScreen));

    EXPECT_EQ(false, bResult);
    EXPECT_EQ(string("Hello"), string(reinterpret_cast<const char*>(&u8VirtualScreen[0])) );
}

TEST_F(HelloWorld_test, ScreenEnoughSize){

    uint8_t u8VirtualScreen[13];
    bool bResult;

    bResult = hello_world_api(&u8VirtualScreen[0], sizeof(u8VirtualScreen));

    EXPECT_EQ(true, bResult);
    EXPECT_EQ(string("Hello World!"), string(reinterpret_cast<const char*>(&u8VirtualScreen[0])) );
}

/* Array comparison tests
==============================================================================*/
TEST_F(HelloWorld_test, ScreenNotBlank){
    uint8_t u8VirtualScreen[23];
    uint8_t u8BlankScreen[23]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    bool bResult;

    bResult = hello_world_api(&u8VirtualScreen[0], sizeof(u8VirtualScreen));
    EXPECT_EQ(true, bResult);

    EXPECT_EQ(sizeof(u8VirtualScreen), sizeof(u8BlankScreen));
    for (uint32_t u32Ix = 0; u32Ix < strlen(reinterpret_cast<const char*>(&u8VirtualScreen[0])); u32Ix++ ){
        EXPECT_NE(u8VirtualScreen[u32Ix], u8BlankScreen[u32Ix]) << "Vectors x and y are equal at index " << u32Ix;
    }
}

TEST_F(HelloWorld_test, ScreenMatch){

    uint8_t u8VirtualScreen[23];
    bool bResult;

    bResult = hello_world_api(&u8VirtualScreen[0], sizeof(u8VirtualScreen));

    EXPECT_EQ(true, bResult);
    EXPECT_EQ(string("Hello World!"), string(reinterpret_cast<const char*>(&u8VirtualScreen[0])) );
}

/* array comparison examples */
TEST_F(HelloWorld_test, ArrayCmpEg1){

    uint8_t u8VirtualScreen[23];

    bool bResult;

    bResult = hello_world_api(&u8VirtualScreen[0], sizeof(u8VirtualScreen));
    EXPECT_EQ(true, bResult);

    /* Eg 1 */
    EXPECT_THAT(u8VirtualScreen, ElementsAre('H','e','l','l','o',' ','W','o','r','l','d','!',
    0,0,0,0,0,0,0,0,0,0,0));
}

TEST_F(HelloWorld_test, ArrayCmpEg2){

    uint8_t u8VirtualScreen[23];
    uint8_t u8ReferenceScreen[23]={'H','e','l','l','o',' ','W','o','r','l','d','!',
    0,0,0,0,0,0,0,0,0,0};

    bool bResult;

    bResult = hello_world_api(&u8VirtualScreen[0], sizeof(u8VirtualScreen));
    EXPECT_EQ(true, bResult);
    /* Eg 2 */
    EXPECT_EQ(sizeof(u8VirtualScreen), sizeof(u8ReferenceScreen));
    for (uint32_t u32Ix = 0; u32Ix < sizeof(u8VirtualScreen); u32Ix++ ){
        EXPECT_EQ(u8VirtualScreen[u32Ix], u8ReferenceScreen[u32Ix]) << "Vectors x and y differ at index " << u32Ix;
    }
}

TEST_F(HelloWorld_test, ArrayCmpEg3){

    uint8_t u8VirtualScreen[23];
    uint8_t u8ReferenceScreen[23]={'H','e','l','l','o',' ','W','o','r','l','d','!',
    0,0,0,0,0,0,0,0,0,0};

    bool bResult;

    bResult = hello_world_api(&u8VirtualScreen[0], sizeof(u8VirtualScreen));
    EXPECT_EQ(true, bResult);
    /* Eg 3 */
    EXPECT_TRUE( 0 == memcmp( u8VirtualScreen, u8ReferenceScreen, sizeof( u8ReferenceScreen ) ) );
}


/* The easiest way to compare C arrays
==============================================================================*/
TEST_F(HelloWorld_test, ArrayCmpEg5){

    uint8_t u8VirtualScreen[23];
    uint8_t u8ReferenceScreen[23]={'H','e','l','l','o',' ','W','o','r','l','d','!',
    0,0,0,0,0,0,0,0,0,0};

    bool bResult;

    bResult = hello_world_api(&u8VirtualScreen[0], sizeof(u8VirtualScreen));
    EXPECT_EQ(true, bResult);

    /* Eg 5 */
    ASSERT_THAT(u8VirtualScreen, ContainerEq(u8ReferenceScreen));
}
/* same as above, but designed to fail */
TEST_F(HelloWorld_test, DISABLED_ArrayCmpEg6){

    uint8_t u8VirtualScreen[23];
    uint8_t u8ReferenceScreen[23]={'H','a','l','l','o',' ','W','o','r','l','d','!',
    0,0,0,0,0,0,0,0,0,0};

    bool bResult;

    bResult = hello_world_api(&u8VirtualScreen[0], sizeof(u8VirtualScreen));
    EXPECT_EQ(true, bResult);

    /* Eg 5 */
    ASSERT_THAT(u8VirtualScreen, ContainerEq(u8ReferenceScreen));
}
