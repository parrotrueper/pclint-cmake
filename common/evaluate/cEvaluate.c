/**
 * \file cEvaluate.c
 * \brief Collection of functions to demonstrate the test framework
 */
#include <stdio.h>
#include <math.h>
#include "cEvaluate.h"

static char ResultStr[5]; /* 0xXX\0*/
/**
 * \brief find the width of float for this platform
 * \returns the number of bits
 */
uint32_t cEvaluate_PlatformSizeOfFloat(void)
{
    return (sizeof(float) * 8);
}

/**
 * \brief find the width of double for this platform
 * \returns the number of bits
 */
uint32_t cEvaluate_PlatformSizeOfDouble(void)
{
    return (sizeof(double) * 8);
}

/**
 * \brief find the width of long double for this platform
 * \returns the number of bits
 */
uint32_t cEvaluate_PlatformSizeOfLongDouble(void)
{
    return (sizeof(long double) * 8);
}

/**
 * \brief get the 32-bit value of Pi
 */
float32_t cEvaluate_GetPi32bit(void)
{
    float32_t f32Pi = (float32_t)(M_PI);
    return f32Pi + (float32_t)(sin(f32Pi));
}

/**
 * \brief get the 64-bit value of Pi
 */
float64_t cEvaluate_GetPi64bit(void)
{
    float64_t f64Pi = 3.14159265358979323846;
    return f64Pi + (float64_t)(sin(f64Pi));
}

/**
 * \brief Divide two integers
 * \param i_u32Numerator
 * \param i_u32Denominator
 * \return i_u32Numerator/i_u32Denominator
 */
uint32_t cEvaluate_Division(uint32_t i_u32Numerator, uint32_t i_u32Denominator)
{
    return i_u32Numerator/i_u32Denominator;
}

/**
 * \brief Print contents of address
 * \param i_pAddress - pointer
 */
char* cEvaluate_PrintAddrValue(uint8_t* i_pAddress)
{
    sprintf((char *)(&ResultStr[0]), "0x%x",*i_pAddress);
    return &ResultStr[0];
}

/* EOF */
