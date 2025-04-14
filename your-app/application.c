/**
 * \file application.c
 * \brief Implementation of the Example API
 *
 */
#include <stdbool.h>
#include <stdint.h>
#include <string.h>			/* strcmp */

#include "application.h"

#include "hello_world.h"
#include "cCounter.h"
#include "cEvaluate.h"

#include "util_DevDebug.h"   	/* Debug and diagnostics helper */
#include "util_Types.h"		 	/* target types such as int */
#include "util_Crc32.h"
#include "util_DateTime.h"

/****************************************************************/
/* Private Debug Macros                                         */
/****************************************************************/
/** \def Enable/Disable trace debug in this module */
#define DD_MAIN_EN (0 * DD_TRACE_EN)
#if DD_MAIN_EN
	#if DD_COLOURIT_TRACE
		#define DD_MAIN_COLOUR     DD_COLOUR_CYN
	#else
		#define DD_MAIN_COLOUR
	#endif

    #define DD_MAIN_TRACE(...)     do{if(f_bDebugEn){DD_COL_TRACE(DD_MAIN_COLOUR,__VA_ARGS__);}}while(0)
#else
    #define DD_MAIN_TRACE(...)     ( (void) 0 )
#endif /* DD_MAIN_EN */

/****************************************************************/
/* Private Macros                                               */
/****************************************************************/
/** Eventlog name for this API */
#define API_EVENTLOG_NAME		"Example API"

/****************************************************************/
/* Private Typedefs                                             */
/****************************************************************/


/****************************************************************/
/* Private Variables 						                    */
/****************************************************************/
/** true if this module has been initialised*/
static bool f_bInitialised = false;
/** true if we need to power down this API */
static bool f_bShutdownReq = false;

static uint32_t u32Count;
/****************************************************************/
/* Private Functions 						                    */
/****************************************************************/
/**
 * \brief Private function to initialise this module. Call this first.
 * \return true if there are no errors
 */
static bool application_init(void)
{
	uint8_t u8Value[]={0x5A, 0x5A, 0x5A, 0x5A};
	bool bResult = true;

	DD_MAIN_TRACE("Example API Starting\n");
	DD_MAIN_TRACE("Entry %s()\n", __FUNC__);

	/* initialise our local variables */
	f_bInitialised = false;
	f_bShutdownReq = false;

	cCounter_InitCounter();
	DD_MAIN_TRACE("Counter %s initialised\n", (cCounter_IsCounterInited()?"is":"is NOT"));
	DD_MAIN_TRACE("Platform size of Float = %d\n", cEvaluate_PlatformSizeOfFloat());
	cCounter_IncCounter();
	DD_MAIN_TRACE("Platform size of Double = %d\n", cEvaluate_PlatformSizeOfDouble());
	cCounter_IncCounter();
	DD_MAIN_TRACE("Platform size of Long Double = %d\n", cEvaluate_PlatformSizeOfLongDouble());
	cCounter_IncCounter();
	DD_MAIN_TRACE("Pi 32-bit = %f\n", cEvaluate_GetPi32bit());
	cCounter_IncCounter();
	DD_MAIN_TRACE("Pi 64-bit = %f\n", cEvaluate_GetPi64bit());
	cCounter_IncCounter();
	DD_MAIN_TRACE("20/10 = %d\n", cEvaluate_Division(20,10));
	cCounter_IncCounter();
	DD_MAIN_TRACE("Value at address %p=%s\n", &u8Value[0], cEvaluate_PrintAddrValue(&u8Value[0]));
	DD_MAIN_TRACE("Function calls=%d\n", cCounter_GetCount());
	DD_MAIN_TRACE("CRC-32=%d\n",util_Crc32_Calc(&u8Value[0], sizeof(u8Value)));
	(void)u8Value;
	DD_MAIN_TRACE("2023 %s leap year\n", (util_DateTime_IsLeapYear(2023))?"is":"is not");

    f_bInitialised = true;
	DD_MAIN_TRACE("Exit %s[%d]\n\n", __FUNC__, bResult);
	return bResult;
}

/**
 * \brief Private function to clean up to exit this API. Called by the main loop
 * and triggered by the f_bShutdownReq flag being set. Sends the shutdown request
 * to each of the running threads of this API.
 */
static void application_cleanUp(void)
{
	DD_MAIN_TRACE("Entry %s()\n", __FUNC__);

	f_bInitialised = false;

	DD_MAIN_TRACE("%s() System Shutting down...", __FUNC__ );

	DD_MAIN_TRACE("Exit %s()\n", __FUNC__);
}
/**
 * \brief Private function used to request this API to start shutting down. Flags
 * the main loop to clean up and exit.
 */
static void application_shutdown(void)
{
	f_bShutdownReq = true;
}

/****************************************************************/
/* Exposed Interfaces						                    */
/****************************************************************/
/**
 * \brief main application loop, call this regularly to drive this api
 * \param i_bReset - true to initialise this module,
 */
void application_tick(bool i_bReset)
{
	uint8_t u8MyScreen[15];

	DD_MAIN_TRACE("Entry: %s(%d)\n", __FUNC__, i_bReset);

    if ( true == i_bReset ){
        /* initialise this API */
        bool bResult = application_init();

		if ( false == bResult ){
			application_shutdown();
		}else{
			/* Hello World! */
			bResult = hello_world_api(&u8MyScreen[0], sizeof(u8MyScreen));
			DD_TRACE("\n%s\n", (char*)(&u8MyScreen));
			u32Count=0;
		}
    }

    if (( true == f_bInitialised )&&(true == f_bShutdownReq)){
        application_cleanUp();
    }

    if ( (true == f_bInitialised) && (false == f_bShutdownReq)){
        /* tick -- do something */
        u32Count++;
        if ( (u32Count % 1000) == 0 ){
            DD_TRACE("tick tock\n");
        }
    }
}

uint32_t application_getCount(void)
{
	return u32Count;
}
