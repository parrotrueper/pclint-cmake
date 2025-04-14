/**
 * \file cEvaluate.c
 * \brief A counter module to demonstrate test fixtures
 *
 */
#include "cCounter.h"

static bool f_bInitialise = false;
static uint32_t f_u32Counter = 0;


/**
 * \brief Initialise the counter function. Call this first.
 */
void cCounter_InitCounter(void)
{
    f_bInitialise = true;
    f_u32Counter = 0;
}

/**
 * \brief check whether the counter setup
 * \return true if the counter has been initialised
 */
bool cCounter_IsCounterInited(void)
{
    return f_bInitialise;
}

/**
 * \brief get the value of the counter
 * \return current counter value
 */
uint32_t cCounter_GetCount(void)
{
    return f_u32Counter;
}

/**
 * \brief increment the counter
 */
void cCounter_IncCounter(void)
{
    if (f_bInitialise ){
        f_u32Counter++;
    }
}

/**
 * \brief De-Initialise the counter function
 */
void cCounter_DeInitCounter(void)
{
    f_bInitialise = false;
}

/* EOF */
