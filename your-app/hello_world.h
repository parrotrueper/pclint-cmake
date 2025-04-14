/**
 * \file hello_world.h
 * \brief Example file
 *
 */
#ifndef HELLO_WORLD_H__
#define HELLO_WORLD_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus */

/**
 * \brief Write Hello world to a buffer of specified length
 * \param i_pDestination - pointer to the destination buffer
 * \param i_u32Length - length of the message in bytes
 * \return true if the entire message was transfered to its destination
 */
bool hello_world_api(uint8_t *i_pDestination, uint32_t i_u32Length);

#ifdef __cplusplus
}
#endif /*__cplusplus */
#endif /* HELLO_WORLD_H__ */
