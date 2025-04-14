/**
 * \file hello_world.c
 * \brief Example file
 *
 */
#include <stddef.h>
#include "hello_world.h"
#include "util_DevDebug.h"

/**
 * \brief Write Hello world to a buffer of specified length
 * \param i_pDestination - pointer to the destination buffer
 * \param i_u32Length - length of the message in bytes
 * \return true if the entire message was transferred to its destination
 */
bool hello_world_api(uint8_t *i_pDestination, uint32_t i_u32Length)
{
    bool bResult = true;
    const uint8_t u8Message[]={"Hello World!"};
    uint32_t u32Loop;
    uint32_t u32Limit = (uint32_t)(sizeof(u8Message));

    DD_ASSERT(NULL != i_pDestination);
    DD_ASSERT((uint32_t)(0) != i_u32Length);

    /* sanity check the input parameters */
    if ( ( i_pDestination == NULL ) || ( i_u32Length < (uint32_t)(1) ) ){
        bResult = false;
    }else if ( ( i_pDestination != NULL ) && ( i_u32Length == (uint32_t)(1)) ){
        i_pDestination[0] = 0;
        bResult = false;
    }else{
        /* ensure we do not over run the target buffer */
        if ( u32Limit > i_u32Length ){
            u32Limit = i_u32Length;
            bResult = false;
        }
        /* copy the message to the destination */
        for ( u32Loop = 0; u32Loop < (u32Limit - (uint32_t)(1)); u32Loop++ ){
            i_pDestination[u32Loop] = u8Message[u32Loop];
        }
        /* null terminate the rest of the buffer */
        for ( ; u32Loop < i_u32Length; u32Loop++ ){
            i_pDestination[u32Loop] = 0;
        }
    }

    return bResult;
}
