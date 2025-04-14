/**
 * \file cCounter.h
 * \brief Exposes counting module to demonstrate test fixtures
 *
 */
#ifndef CCOUNTER_H__
#define CCOUNTER_H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */


/**
 * \brief Initialise the counter function. Call this first.
 */
void cCounter_InitCounter(void);

/**
 * \brief check whether the counter setup
 * \return true if the counter has been initialised
 */
bool cCounter_IsCounterInited(void);

/**
 * \brief get the value of the counter
 * \return current counter value
 */
uint32_t cCounter_GetCount(void);

/**
 * \brief increment the counter
 */
void cCounter_IncCounter(void);

/**
 * \brief De-Initialise the counter function
 */
void cCounter_DeInitCounter(void);

#ifdef __cplusplus
}
#endif /*__cplusplus */
#endif /* CCOUNTER_H__ */
