/**
 * TMR4 Generated Driver API Header File
 *
 * @file tmr4.h
 *  
 * @defgroup tmr4 TMR4
 *
 * @brief This file contains the API Prototypes and other data types for the TMR4 driver.
 *
 * @version TMR4 Driver Version 3.0.1
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

#ifndef TMR4_H
#define TMR4_H

#include <stdint.h>
#include <stdbool.h>
#include "timer_interface.h"

/**
 Section: Data Type Definitions
*/
/**
 @ingroup tmr4
 @struct TMR_INTERFACE
 @brief This is an instance of TMR_INTERFACE for TMR4 module.
 */
extern const struct TMR_INTERFACE FsTMR;

/**
 * @ingroup tmr4
 * @enum FsTMR_HLT_EXT_RESET_SOURCE
 * @brief Defines the several modes of operation of the timer with the HLT extension.
 */

typedef enum
{

	/* Roll-over Pulse mode clears the TMRx upon TMRx = PRx, then continue running.
	ON bit must be set and is not affected by Resets
	*/

   /* Roll-over Pulse mode indicates that Timer starts
   immediately upon ON = 1 (Software Control)
   */
   FsTMR_ROP_STARTS_TMRON,

   /* Roll-over Pulse mode indicates that the Timer starts
       when ON = 1 and TMRx_ers = 1. Stops when TMRx_ers = 0
     */
   FsTMR_ROP_STARTS_TMRON_ERSHIGH,

   /* Roll-over Pulse mode indicates that the Timer starts
      when ON = 1 and TMRx_ers = 0. Stops when TMRx_ers = 1
     */
   FsTMR_ROP_STARTS_TMRON_ERSLOW,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon rising or falling edge of TMRx_ers
     */
   FsTMR_ROP_RESETS_ERSBOTHEDGE,

   /* Roll-over Pulse mode indicates that the Timer resets
    upon rising edge of TMRx_ers
     */
   FsTMR_ROP_RESETS_ERSRISINGEDGE,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon falling edge of TMRx_ers
     */
   FsTMR_ROP_RESETS_ERSFALLINGEDGE,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon TMRx_ers = 0
     */
   FsTMR_ROP_RESETS_ERSLOW,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon TMRx_ers = 1
     */
   FsTMR_ROP_RESETS_ERSHIGH,

    /*In all One-Shot mode the timer resets and the ON bit is
	cleared when the timer value matches the PRx period
	value. The ON bit must be set by software to start
	another timer cycle.
	*/

   /* One shot mode indicates that the Timer starts
    immediately upon ON = 1 (Software Control)
     */
   FsTMR_OS_STARTS_TMRON,

   /* One shot mode indicates that the Timer starts
    when a rising edge is detected on the TMRx_ers
     */
   FsTMR_OS_STARTS_ERSRISINGEDGE ,

   /* One shot mode indicates that the Timer starts
    when a falling edge is detected on the TMRx_ers
     */
   FsTMR_OS_STARTS_ERSFALLINGEDGE ,

   /* One shot mode indicates that the Timer starts
    when either a rising or falling edge is detected on TMRx_ers
     */
   FsTMR_OS_STARTS_ERSBOTHEDGE,

   /* One shot mode indicates that the Timer starts
    upon first TMRx_ers rising edge and resets on all
	subsequent TMRx_ers rising edges
     */
   FsTMR_OS_STARTS_ERSFIRSTRISINGEDGE,

   /* One shot mode indicates that the Timer starts
    upon first TMRx_ers falling edge and restarts on all
	subsequent TMRx_ers falling edges
     */
   FsTMR_OS_STARTS_ERSFIRSTFALLINGEDGE,

   /* One shot mode indicates that the Timer starts
    when a rising edge is detected on the TMRx_ers,
	resets upon TMRx_ers = 0
     */
   FsTMR_OS_STARTS_ERSRISINGEDGEDETECT,
     /* One shot mode indicates that the Timer starts
    when a falling edge is detected on the TMRx_ers,
	resets upon TMRx_ers = 1
     */
   FsTMR_OS_STARTS_ERSFALLINGEDGEDETECT,
   
   /* One shot mode indicates that the Timer starts
    when a TMRx_ers = 1,ON =1 and resets upon TMRx_ers =0
    */
   FsTMR_OS_STARTS_TMRON_ERSHIGH = 0x16,
           
   /* One shot mode indicates that the Timer starts
     when a TMRx_ers = 0,ON = 1 and resets upon TMRx_ers =1 
    */
   FsTMR_OS_STARTS_TMRON_ERSLOW = 0x17,
        
   /*In all Mono-Stable mode the ON bit must be initially set,but
     not cleared upon the TMRx = PRx, and the timer will start upon
     an TMRx_ers start event following TMRx = PRx.*/
               
   /* Mono Stable mode indicates that the Timer starts
      when a rising edge is detected on the TMRx_ers and ON = 1
    */
   FsTMR_MS_STARTS_TMRON_ERSRISINGEDGEDETECT = 0x11,
           
   /* Mono Stable mode indicates that the Timer starts
      when a falling edge is detected on the TMRx_ers and ON = 1
    */
   FsTMR_MS_STARTS_TMRON_ERSFALLINGEDGEDETECT = 0x12,
           
   /* Mono Stable mode indicates that the Timer starts
      when  either a rising or falling edge is detected on TMRx_ers 
      and ON = 1
    */
   FsTMR_MS_STARTS_TMRON_ERSBOTHEDGE = 0x13
           
} FsTMR_HLT_MODE;

/**
 * @ingroup tmr4
 * @enum FsTMR_HLT_EXT_RESET_SOURCE
 * @brief Defines the different reset sources of the HLT.
 */
typedef enum
{
    /*
     * T4CKIPPS_PIN as the Timer external reset source
     */
    FsTMR_T4CKIPPS_PIN =  0x0,   
    /*
     * TMR2_POSTSCALED as the Timer external reset source
     */
    FsTMR_TMR2_POSTSCALED =  0x1,   
    /*
     * TMR6_POSTSCALED as the Timer external reset source
     */
    FsTMR_TMR6_POSTSCALED =  0x3,   
    /*
     * CCP1OUT as the Timer external reset source
     */
    FsTMR_CCP1OUT =  0x4,   
    /*
     * CCP2OUT as the Timer external reset source
     */
    FsTMR_CCP2OUT =  0x5,   
    /*
     * CCP3OUT as the Timer external reset source
     */
    FsTMR_CCP3OUT =  0x6,   
    /*
     * PWM1_OUT1 as the Timer external reset source
     */
    FsTMR_PWM1_OUT1 =  0x7,   
    /*
     * PWM1_OUT2 as the Timer external reset source
     */
    FsTMR_PWM1_OUT2 =  0x8,   
    /*
     * PWM2_OUT1 as the Timer external reset source
     */
    FsTMR_PWM2_OUT1 =  0x9,   
    /*
     * PWM2_OUT2 as the Timer external reset source
     */
    FsTMR_PWM2_OUT2 =  0xa,   
    /*
     * PWM3_OUT1 as the Timer external reset source
     */
    FsTMR_PWM3_OUT1 =  0xb,   
    /*
     * PWM3_OUT2 as the Timer external reset source
     */
    FsTMR_PWM3_OUT2 =  0xc,   
    /*
     * CMP1OUT as the Timer external reset source
     */
    FsTMR_CMP1OUT =  0xf,   
    /*
     * CMP2OUT as the Timer external reset source
     */
    FsTMR_CMP2OUT =  0x10,   
    /*
     * ZCDOUT as the Timer external reset source
     */
    FsTMR_ZCDOUT =  0x11,   
    /*
     * CLC1_OUT as the Timer external reset source
     */
    FsTMR_CLC1_OUT =  0x12,   
    /*
     * CLC2_OUT as the Timer external reset source
     */
    FsTMR_CLC2_OUT =  0x13,   
    /*
     * CLC3_OUT as the Timer external reset source
     */
    FsTMR_CLC3_OUT =  0x14,   
    /*
     * CLC4_OUT as the Timer external reset source
     */
    FsTMR_CLC4_OUT =  0x15,   
    /*
     * CLC5_OUT as the Timer external reset source
     */
    FsTMR_CLC5_OUT =  0x16,   
    /*
     * CLC6_OUT as the Timer external reset source
     */
    FsTMR_CLC6_OUT =  0x17,   
    /*
     * CLC7_OUT as the Timer external reset source
     */
    FsTMR_CLC7_OUT =  0x18,   
    /*
     * CLC8_OUT as the Timer external reset source
     */
    FsTMR_CLC8_OUT =  0x19,   
    /*
     * UART1_RX_EDGE as the Timer external reset source
     */
    FsTMR_UART1_RX_EDGE =  0x1a,   
    /*
     * UART1_TX_EDGE as the Timer external reset source
     */
    FsTMR_UART1_TX_EDGE =  0x1b,   
    /*
     * UART2_RX_EDGE as the Timer external reset source
     */
    FsTMR_UART2_RX_EDGE =  0x1c,   
    /*
     * UART2_TX_EDGE as the Timer external reset source
     */
    FsTMR_UART2_TX_EDGE =  0x1d,   
    /*
     * UART3_RX_EDGE as the Timer external reset source
     */
    FsTMR_UART3_RX_EDGE =  0x1e,   
    /*
     * UART3_TX_EDGE as the Timer external reset source
     */
    FsTMR_UART3_TX_EDGE =  0x1f,   
    /*
     * UART4_RX_EDGE as the Timer external reset source
     */
    FsTMR_UART4_RX_EDGE =  0x20,   
    /*
     * UART4_TX_EDGE as the Timer external reset source
     */
    FsTMR_UART4_TX_EDGE =  0x21,   
    /*
     * UART5_RX_EDGE as the Timer external reset source
     */
    FsTMR_UART5_RX_EDGE =  0x22,   
    /*
     * UART5_TX_EDGE as the Timer external reset source
     */
    FsTMR_UART5_TX_EDGE =  0x23   
} FsTMR_HLT_EXT_RESET_SOURCE;

/**
  Section: Macro Declarations
*/

/**
  Section: TMR4 APIs
*/

/**
 * @ingroup tmr4
 * @brief Initializes the TMR4 module. This routine must be called before any other timer routines.
 * @param None.
 * @return None.
 */
 void FsTMR_Initialize(void);

/**
 * @ingroup tmr4
 * @brief Configures the Hardware Limit Timer (HLT) mode.
 * @pre The TMR4 should be initialized with FsTMR_Initialize after calling this API.
 * @param mode - Value to write into T4HLTbits.MODE bits.
 * @return None.
 */
void FsTMR_ModeSet(FsTMR_HLT_MODE mode);

/**
 * @ingroup tmr4
 * @brief Configures the HLT external reset source.
 * @pre The TMR4 should be initialized with FsTMR_Initialize after calling this API.
 * @param reset - Value to write into T4RSTbits.RSEL bits.
 * @return None.
 */
void FsTMR_ExtResetSourceSet(FsTMR_HLT_EXT_RESET_SOURCE reset);

/**
 * @ingroup tmr4
 * @brief Starts TMR4.
 * @pre The TMR4 should be initialized with FsTMR_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void FsTMR_Start(void);

/**
 * @ingroup tmr4
 * @brief Stops TMR4.
 * @pre The TMR4 should be initialized with FsTMR_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void FsTMR_Stop(void);

/**
 * @ingroup tmr4
 * @brief Reads the 8-bit from the TMR4 register.
 * @pre The TMR4 should be initialized with FsTMR_Initialize() before calling this API.
 * @param None.
 * @return 8-bit data from the TMR4 register.
 */
uint8_t FsTMR_Read(void);

/**
 * @ingroup tmr4
 * @brief Writes the 8-bit value to the TMR4 register.
 * @pre The TMR4 should be initialized with FsTMR_Initialize() before calling this API.
 * @param timerVal - 8-bit value written to the TMR4 register.
 * @return None.
 */
void FsTMR_Write(uint8_t timerVal);

/**
 * @ingroup tmr4
 * @brief Loads the 8-bit value to the PR4 register.
 * @pre The TMR4 should be initialized with FsTMR_Initialize() before calling this API.
 * @param periodVal - 8-bit value written to the PR4 register.
 * @return None.
 */
void FsTMR_PeriodCountSet(size_t periodVal);

/**
 * @ingroup tmr4
 * @brief Interrupt Service Routine (ISR) for TMR4 overflow interrupt.
 * @param None.
 * @return None.
 */
void FsTMR_ISR(void);

/**
 * @ingroup tmr4
 * @brief Setter function for the TMR4 overflow callback.
 * @param CallbackHandler - Pointer to the custom callback.
 * @return None.
 */
void FsTMR_OverflowCallbackRegister(void (* InterruptHandler)(void));


#endif // TMR4_H
/**
 End of File
*/
