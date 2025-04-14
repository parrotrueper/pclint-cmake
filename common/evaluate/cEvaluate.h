/**
 * \file cEvaluate.h
 * \brief Exposes function to be used for unit testing
 *
 */
#ifndef CEVALUATE_H__
#define CEVALUATE_H__

#include "util_Types.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

/**
 * \brief Find the width in bits for a float on this platform
 * \returns the number of bits
 */
uint32_t cEvaluate_PlatformSizeOfFloat(void);

/**
 * \brief find the width of double for this platform
 * \returns the number of bits
 */
uint32_t cEvaluate_PlatformSizeOfDouble(void);

/**
 * \brief find the width of long double for this platform
 * \returns the number of bits
 */
uint32_t cEvaluate_PlatformSizeOfLongDouble(void);

/**
 * \brief get the 32-bit value of Pi
 */
float32_t cEvaluate_GetPi32bit(void);

/**
 * \brief get the 64-bit value of Pi
 */
float64_t cEvaluate_GetPi64bit(void);

/**
 * \brief Divide two integers
 * \param i_u32Numerator
 * \param i_u32Denominator
 * \return i_u32Numerator/i_u32Denominator
 */
uint32_t cEvaluate_Division(uint32_t i_u32Numerator, uint32_t i_u32Denominator);

/**
 * \brief Print contents of address
 * \param i_pAddress - pointer
 */
char* cEvaluate_PrintAddrValue(uint8_t* i_pAddress);


#ifdef __cplusplus
}
#endif /*__cplusplus */
#endif /* CEVALUATE_H__ */
