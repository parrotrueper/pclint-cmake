/**
 * \file drv_Gpio.h
 * \brief Exposes the GPIO driver functions required by the API
 *
 */
#ifndef DRV_GPIO_H__
#define DRV_GPIO_H__

#include <stdint.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus */

typedef uint32_t        drvgpio_port_t;    /* platform dependent types */
typedef uint16_t        drvgpio_pin_t;     /* platform dependent types */

typedef enum{
   eDrvGpio_Low = 0,
   eDrvGpio_High,
   eDrvGpio_Unknown
   /* add rd pin options here like, hi-z, push-pull, open-collector etc... */
}e_drvgpio_state_t;


typedef struct{
   bool                   bInitialised;
   const drvgpio_port_t *pPort;
   drvgpio_pin_t         tPin;
   e_drvgpio_state_t     eInitState;
}st_drvgpio_instance_t;


/**
 * \brief Initialise a port pin, call this before attempting to use it
 * \param i_pPortPinInstance instance of the port pin that is to be initialised, this must be stored in persistent memory
 * \param i_pPort - address for the port
 * \param i_tPin  - the pin to initialise
 * \param i_eInitState - what state should the pin be set to at initialisation
 **/
void drv_Gpio_Initialise(st_drvgpio_instance_t *i_pPortPinInstance,
                     const drvgpio_port_t *i_pPort,
                     const drvgpio_pin_t i_tPin,
                     const e_drvgpio_state_t i_eInitState);
/**
 * \brief toggle a port pin
 * \param i_pPortPinInstance - the instance for the port pin, this must have been previously initialised
 **/
void drv_Gpio_TogglePin(const st_drvgpio_instance_t *i_pPortPinInstance);

/**
 * \brief Set the output value to a port pin
 * \param i_pPortPinInstance - the instance for the port pin, this must have been previously initialised
 * \param i_eState - the enum value to write to the pin
*/
void drv_Gpio_WritePin(const st_drvgpio_instance_t *i_pPortPinInstance, e_drvgpio_state_t i_eState);

/**
 * \brief Read the state of a port pin
 * \param i_pPortPinInstance - the instance for the port pin, this must have been previously initialised
 * \return the current state of the pin
 */
e_drvgpio_state_t drv_Gpio_ReadPin(const st_drvgpio_instance_t *i_pPortPinInstance);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* DRV_GPIO_H__ */
