/**
 * \file drv_Gpio.c
 * \brief GPIO driver functions required by the API
 *
 */
#include "drv_Gpio.h"
#include "stm32f4xx_hal.h"

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
                     const e_drvgpio_state_t i_eInitState){

    if ( i_pPortPinInstance && i_pPort ){
        i_pPortPinInstance->pPort = i_pPort;
        i_pPortPinInstance->tPin = i_tPin;
        i_pPortPinInstance->eInitState = i_eInitState;
        if( i_eInitState == eDrvGpio_Low ){
            HAL_GPIO_WritePin((GPIO_TypeDef *)i_pPortPinInstance->pPort, i_pPortPinInstance->tPin, GPIO_PIN_RESET);
        }else{
            HAL_GPIO_WritePin((GPIO_TypeDef *)i_pPortPinInstance->pPort, i_pPortPinInstance->tPin, GPIO_PIN_SET);
        }
        i_pPortPinInstance->bInitialised = true;
    }
}
/**
 * \brief toggle a port pin
 * \param i_pPortPinInstance - the instance for the port pin, this must have been previously initialised
 **/
void drv_Gpio_TogglePin(const st_drvgpio_instance_t *i_pPortPinInstance)
{
   if ( i_pPortPinInstance ){
      if ( i_pPortPinInstance->bInitialised ){
         HAL_GPIO_TogglePin((GPIO_TypeDef *)i_pPortPinInstance->pPort, i_pPortPinInstance->tPin);
      }
   }
}


/**
 * \brief Set the output value to a port pin
 * \param i_pPortPinInstance - the instance for the port pin, this must have been previously initialised
 * \param i_eState - the enum value to write to the pin
*/
void drv_Gpio_WritePin(const st_drvgpio_instance_t *i_pPortPinInstance, e_drvgpio_state_t i_eState)
{
   if ( i_pPortPinInstance ){
      if ( i_pPortPinInstance->bInitialised ){
         if ( i_eState == eDrvGpio_High ){
            HAL_GPIO_WritePin((GPIO_TypeDef *)i_pPortPinInstance->pPort, i_pPortPinInstance->tPin, GPIO_PIN_SET);
         }else{
            HAL_GPIO_WritePin((GPIO_TypeDef *)i_pPortPinInstance->pPort, i_pPortPinInstance->tPin, GPIO_PIN_RESET);
         }
      }
   }
}

/**
 * \brief Read the state of a port pin
 * \param i_pPortPinInstance - the instance for the port pin, this must have been previously initialised
 * \return the current state of the pin
 */
e_drvgpio_state_t drv_Gpio_ReadPin(const st_drvgpio_instance_t *i_pPortPinInstance)
{
   e_drvgpio_state_t eResult = eDrvGpio_Unknown;

   if ( i_pPortPinInstance ){
      if ( i_pPortPinInstance->bInitialised ){
         if(HAL_GPIO_ReadPin((GPIO_TypeDef *)i_pPortPinInstance->pPort, i_pPortPinInstance->tPin)){
            eResult = eDrvGpio_High;
         }else{
            eResult = eDrvGpio_Low;
         }
      }
   }

   return eResult;
}
