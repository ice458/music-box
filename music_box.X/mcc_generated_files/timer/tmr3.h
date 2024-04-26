/**
 * TMR3 Generated Driver API Header File
 *
 * @file tmr3.h
 *
 * @defgroup tmr3 TMR3
 *
 * @brief This file contains the API prototypes and other data types for the TMR3 driver.
 *
 * @version TMR3 Driver Version 3.1.0
*/
/*
? [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef TMR3_H
#define TMR3_H

#include <stdbool.h>
#include <stdint.h>
#include "timer_interface.h"


/**
 * @ingroup tmr3
 * @struct TMR_INTERFACE
 * @brief This is an instance of TMR_INTERFACE for Timer module
 */
extern const struct TMR_INTERFACE EnvTMR;

/**
 * @ingroup tmr3
 * @brief Initializes the timer module.
 *        This routine must be called before any other timer routines.
 * @param None.
 * @return None.
 */
void EnvTMR_Initialize(void);

/**
 * @ingroup tmr3
 * @brief Starts the timer.
 * @pre The timer should be initialized with EnvTMR_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void EnvTMR_Start(void);

/**
 * @ingroup tmr3
 * @brief Stops the timer.
 * @pre The timer should be initialized with EnvTMR_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void EnvTMR_Stop(void);

/**
 * @ingroup tmr3
 * @brief Reads the 16-bit from the TMR3 register.
 *        The Timer should be initialized with EnvTMR_Initialize() before calling this API.
 * @param None.
 * @return uint16_t - 16-bit data from the TMR3 register.
 */
uint16_t EnvTMR_Read(void);

/**
 * @ingroup tmr3
 * @brief Writes the 16-bit value to the TMR3 register.
 * @pre The timer should be initialized with EnvTMR_Initialize() before calling this API.
 * @param size_t timerVal - 16-bit value written to the TMR3 register.
 * @return None.
 */
void EnvTMR_Write(size_t timerVal);

/**
 * @ingroup tmr3
 * @brief Loads the 8-bit value to the TMR3 register.
 * @pre The timer should be initialized with EnvTMR_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void EnvTMR_Reload(void);

/**
 * @ingroup tmr3
 * @brief Loads the 16-bit value to the timer3ReloadVal variable.
 * @param 16-bit value. 
 * @return None.
 */
void EnvTMR_PeriodCountSet(size_t periodVal);

/**
 * @ingroup tmr3
 * @brief Starts the single pulse acquisition in TMR3 gate operation.
 * @pre This function must be used when the TMR3 gate is enabled.
 * @param None.
 * @return None.
 */
void EnvTMR_StartSinglePulseAcquisition(void);

/**
 * @ingroup tmr3
 * @brief Reads the TMR3 gate value and returns it.
 * @pre This function must be used when the TMR3 gate is enabled.
 * @param None.
 * @return uint8_t - Gate value status.
 */
uint8_t EnvTMR_CheckGateValueStatus(void);

/**
 * @ingroup tmr3
 * @brief Timer Interrupt Service Routine (ISR) called by the Interrupt Manager for overflow.
 * @param None.
 * @return None.
 */
void EnvTMR_OverflowISR(void);

/**
 * @ingroup tmr3
 * @brief Setter function for the Timer overflow callback.
 * @param void (* CallbackHandler)(void) - Pointer to the custom callback.
 * @return None.
 */
 void EnvTMR_OverflowCallbackRegister(void (* CallbackHandler)(void));


/**
 * @ingroup tmr3
 * @brief Checks for the timer overflow flag when in Polling mode.
 * @param None.
 * @retval true  - Timer overflow has occured.
 * @retval false - Timer overflow has not occured.
 */
bool EnvTMR_HasOverflowOccured(void);


/**
 * @ingroup tmr3
 * @brief Timer Gate Interrupt Service Routine (ISR) called by the Interrupt Manager.
 * @param None.
 * @return None.
 */
void EnvTMR_GateISR(void);

#endif // TMR3_H