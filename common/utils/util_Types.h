/**
 * \file util_Types.h
 * \brief processor specific type definitions
 * Also exposes macros to determine maximum size of typed values
*/
#ifndef UTIL_TYPES_H__
#define UTIL_TYPES_H__

#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */


/* make sure we agree on the number or bits for floating point numbers */
typedef float float32_t;
typedef double float64_t;
typedef long double float128_t;

static_assert(((sizeof(float32_t) * 8) == 32), "float 32");
static_assert(((sizeof(float64_t) * 8) == 64), "float 64");

/** \brief  to get around any third party libraries that do not
 * use the stdint library.
 * The main purpose of this is to stop the linter moaning. So use the target
 * size for the following types */
typedef unsigned char util_uchar_t;
typedef int util_target_int_t;
typedef unsigned int util_target_uint_t;
typedef long util_target_long_t;
typedef unsigned long util_target_ulong_t;

/*lint -elibmacro(9026)*/
/*lint ++flb*/

/** determine whether a given type is signed */
#define UTILTYPES_IS_SIGNED(i_SomeType) (((i_SomeType)(-1)) < ((i_SomeType)0))
/** determine the maximum value of an unsigned type */
#define UTILTYPES_UNSIG_MAX(i_SomeType)                                        \
    (((0x1ULL << ((sizeof(i_SomeType) * 8ULL) - 1ULL)) - 1ULL)                 \
     | (0xFULL << ((sizeof(i_SomeType) * 8ULL) - 4ULL)))
/** determine the maximum value of a signed type */
#define UTILTYPES_SIG_MAX(i_SomeType)                                          \
    (((0x1ULL << ((sizeof(i_SomeType) * 8ULL) - 1ULL)) - 1ULL)                 \
     | (0x7ULL << ((sizeof(i_SomeType) * 8ULL) - 4ULL)))

/** determine the maximum value of any type */
#define UTILTYPES_MAX_VAL_OF_TYPE(i_SomeType)                                  \
    ((unsigned long long)(UTILTYPES_IS_SIGNED(i_SomeType)                      \
                              ? UTILTYPES_SIG_MAX(i_SomeType)                  \
                              : UTILTYPES_UNSIG_MAX(i_SomeType)))



/*lint --flb*/
#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* UTIL_TYPES_H__ */
