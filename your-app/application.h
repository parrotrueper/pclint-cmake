/**
 * \file application.h
 * \brief Exposes interfaces to the Main loop of this API
 *
 */

#ifndef APPLICATION_H__
#define APPLICATION_H__


#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus */


void application_tick(bool i_bReset);
uint32_t application_getCount(void);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* APPLICATION_H__ */
