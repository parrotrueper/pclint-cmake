/**
 * \file util_DateTime.h
 * \brief Date utilities
 *
 */
#ifndef UTIL_DATETIME_H__
#define UTIL_DATETIME_H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

/**
 * \brief Check if specified year is a leap year
 * \param i_u32Year  Year to check
 * \returns true if it is a leap year
 **/
bool util_DateTime_IsLeapYear(uint32_t i_u32Year);

#ifdef __cplusplus
}
#endif /*__cplusplus */
#endif /* UTIL_DATETIME_H__ */
